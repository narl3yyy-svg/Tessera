# Reference parts ("oracle"): replays SolidCraft's kernel-neutral recipes
# (tests/oracle/cases, MIT OR Apache-2.0, see tests/oracle/NOTICE) through
# Tessera's commands and compares the result with the expected measurements.
#
#   tessera-cli --script tests/oracle/run_oracle.py
#
# Environment: TSR_ORACLE_CASES (folder of cases, default: next to this file),
# TSR_ORACLE_ONLY (comma-separated case ids), TSR_ORACLE_REPORT (markdown
# report path), TSR_ORACLE_REQUIRE (comma-separated ids that must pass; the
# run fails if one of them does not), TSR_ORACLE_REQUIRE_FILE (the same, one
# id per line: tests/oracle/required.txt lists every case that passes today).
import json
import math
import os
import traceback

import tsr

HERE = os.path.dirname(os.path.abspath(__file__)) if "__file__" in globals() else "tests/oracle"
CASES = os.environ.get("TSR_ORACLE_CASES", os.path.join(HERE, "cases"))
MM = 0.1   # recipe millimetres -> Tessera centimetres


class Unsupported(Exception):
    """The recipe uses something Tessera does not have (yet)."""


def cm(v):
    return [x * MM for x in v]


def fmt(v):
    return ",".join("%.9g" % x for x in v)


# ---------------------------------------------------------------------------
# Sketches


class SketchInfo:
    def __init__(self, name, frame):
        self.name = name                 # Tessera sketch name
        self.frame = frame               # (origin, x, y, normal) in mm
        self.points = [[0.0, 0.0]]       # sketch points in mm; 0 is the origin
        self.refs = {}                   # "l1.end" -> point index
        self.entities = []               # Tessera entities
        self.curves = {}                 # recipe id -> polyline (mm) and point indices
        self.loose_points = []           # point entities (hole centres)
        self.ent_index = {}              # recipe curve id -> Tessera entity index
        self.construction = set()        # recipe ids of construction curves


def add_point(sk, spec):
    if isinstance(spec, dict):
        if "ref" in spec and spec["ref"] in sk.refs:
            return sk.refs[spec["ref"]]
        at = spec["at"]
    else:
        at = spec
    sk.points.append([float(at[0]), float(at[1])])
    return len(sk.points) - 1


def arc_poly(c, r, a0, sweep, n=48):
    return [[c[0] + r * math.cos(a0 + sweep * k / n), c[1] + r * math.sin(a0 + sweep * k / n)] for k in range(n + 1)]


def circumcentre(a, b, c):
    d = 2 * (a[0] * (b[1] - c[1]) + b[0] * (c[1] - a[1]) + c[0] * (a[1] - b[1]))
    if abs(d) < 1e-12:
        raise Unsupported("three-point arc through collinear points")
    ux = ((a[0] ** 2 + a[1] ** 2) * (b[1] - c[1]) + (b[0] ** 2 + b[1] ** 2) * (c[1] - a[1]) + (c[0] ** 2 + c[1] ** 2) * (a[1] - b[1])) / d
    uy = ((a[0] ** 2 + a[1] ** 2) * (c[0] - b[0]) + (b[0] ** 2 + b[1] ** 2) * (a[0] - c[0]) + (c[0] ** 2 + c[1] ** 2) * (b[0] - a[0])) / d
    return [ux, uy]


def build_sketch(f, sketches):
    pl = f["plane"]
    frame = (pl["origin"], pl["x_dir"], pl["y_dir"], pl["normal"])
    name = "Sketch%d" % (len([x for x in tsr.features() if x["command"] == "tsr.sketch.create"]) + 1)
    sk = SketchInfo(name, frame)
    for e in f["entities"]:
        t, eid = e["type"], e.get("id")
        if t == "line":
            a, b = add_point(sk, e["start"]), add_point(sk, e["end"])
            sk.entities.append({"type": "line", "p": [a, b]})
            ends = (a, b)
            poly = [sk.points[a], sk.points[b]]
        elif t == "circle":
            c = add_point(sk, e["center"])
            sk.entities.append({"type": "circle", "c": c, "r": e["radius"] * MM})
            ends = None
            poly = arc_poly(sk.points[c], e["radius"], 0, 2 * math.pi, 96)
        elif t in ("arc_three_point", "arc_center_start_sweep"):
            if t == "arc_three_point":
                s = add_point(sk, e["start"])
                m = e["mid"]["at"] if isinstance(e["mid"], dict) else e["mid"]
                en = add_point(sk, e["end"])
                ctr = circumcentre(sk.points[s], m, sk.points[en])
                a0 = math.atan2(sk.points[s][1] - ctr[1], sk.points[s][0] - ctr[0])
                a1 = math.atan2(sk.points[en][1] - ctr[1], sk.points[en][0] - ctr[0])
                am = math.atan2(m[1] - ctr[1], m[0] - ctr[0])
                ccw = (a1 - a0) % (2 * math.pi)
                ccw_through_mid = (am - a0) % (2 * math.pi) < ccw
                sweep = ccw if ccw_through_mid else ccw - 2 * math.pi
                sk.points.append(ctr)
                c = len(sk.points) - 1
            else:
                c = add_point(sk, e["center"])
                s = add_point(sk, e["start"])
                ctr = sk.points[c]
                sweep = math.radians(e["sweep_deg"])
                a0 = math.atan2(sk.points[s][1] - ctr[1], sk.points[s][0] - ctr[0])
                r = math.hypot(sk.points[s][0] - ctr[0], sk.points[s][1] - ctr[1])
                end = [ctr[0] + r * math.cos(a0 + sweep), ctr[1] + r * math.sin(a0 + sweep)]
                if "end" in e:
                    en = add_point(sk, e["end"])
                else:
                    sk.points.append(end)
                    en = len(sk.points) - 1
            r = math.hypot(sk.points[s][0] - ctr[0], sk.points[s][1] - ctr[1])
            # Tessera arcs run anticlockwise from p[0] to p[1].
            sk.entities.append({"type": "arc", "c": c, "p": [s, en] if sweep > 0 else [en, s], "r": r * MM})
            ends = (s, en)
            poly = arc_poly(ctr, r, a0, sweep)
        elif t == "point":
            p = add_point(sk, {"at": e["at"]})
            sk.loose_points.append(sk.points[p])
            ends = (p, p)
            poly = None
        else:
            raise Unsupported("sketch entity '%s'" % t)
        if e.get("construction") and poly is not None:
            sk.entities[-1]["construction"] = True
            sk.construction.add(eid)
        if eid:
            if ends:
                sk.refs[eid + ".start"], sk.refs[eid + ".end"] = ends
            if t in ("circle",) or t.startswith("arc"):
                sk.refs[eid + ".center"] = sk.entities[-1]["c"]
            if poly is not None:
                sk.ent_index[eid] = len(sk.entities) - 1
    constraints = sketch_constraints(sk, f.get("constraints", []), f.get("dimensions", []))
    pts = [[x * MM, y * MM] for x, y in sk.points]
    data = {"points": pts, "entities": sk.entities, "constraints": constraints}
    o, x, _, n = frame
    spec = "custom:" + fmt(cm(o) + list(n) + list(x))
    tsr.run_command("tsr.sketch.create", plane=spec, data=json.dumps(data))
    # The solved sketch: profiles are found on it, not on the recipe's rough positions.
    solved = json.loads([x for x in tsr.features() if x["command"] == "tsr.sketch.create"][-1]["inputs"]["data"])
    sk.points = [[px / MM, py / MM] for px, py in solved["points"]]
    for eid, i in sk.ent_index.items():
        e = solved["entities"][i]
        P = sk.points
        if e["type"] == "line":
            sk.curves[eid] = [P[e["p"][0]], P[e["p"][1]]]
        elif e["type"] == "circle":
            sk.curves[eid] = arc_poly(P[e["c"]], e["r"] / MM, 0, 2 * math.pi, 96)
        elif e["type"] == "arc":
            c, a0p, a1p = P[e["c"]], P[e["p"][0]], P[e["p"][1]]
            a0 = math.atan2(a0p[1] - c[1], a0p[0] - c[0])
            sweep = (math.atan2(a1p[1] - c[1], a1p[0] - c[0]) - a0) % (2 * math.pi)
            sk.curves[eid] = arc_poly(c, math.hypot(a0p[0] - c[0], a0p[1] - c[1]), a0, sweep)
    sketches[f["name"]] = sk


def sketch_constraints(sk, cons, dims):
    """The recipe's constraints and dimensions in Tessera's sketch format."""
    def point(ref):
        if ref == "origin":
            return 0
        if ref in sk.refs:
            return sk.refs[ref]
        if ref in sk.ent_index and "c" in sk.entities[sk.ent_index[ref]]:
            return sk.entities[sk.ent_index[ref]]["c"]   # a circle stands for its centre
        raise Unsupported("sketch reference '%s'" % ref)

    def is_point(ref):
        return ref == "origin" or ref in sk.refs

    def ent(ref):
        if ref not in sk.ent_index:
            raise Unsupported("sketch reference '%s'" % ref)
        return sk.ent_index[ref]

    def xy(i):
        return sk.points[i]

    def line_dir(i):
        a, b = sk.entities[i]["p"]
        return [xy(b)[0] - xy(a)[0], xy(b)[1] - xy(a)[1]]

    out = []
    for c in cons:
        t, r = c["type"], c["refs"]
        if t == "coincident":
            if is_point(r[0]) and is_point(r[1]):
                out.append({"type": "coincident", "p": [point(r[0]), point(r[1])]})
            else:
                pt, en = (r[0], r[1]) if is_point(r[0]) else (r[1], r[0])
                out.append({"type": "pointOnEntity", "p": [point(pt)], "e": [ent(en)]})
        elif t in ("horizontal", "vertical"):
            if len(r) == 1:
                out.append({"type": t, "e": [ent(r[0])]})
            else:
                out.append({"type": t, "p": [point(r[0]), point(r[1])]})
        elif t in ("horizontal_points", "vertical_points"):
            out.append({"type": t.split("_")[0], "p": [point(r[0]), point(r[1])]})
        elif t in ("tangent", "equal", "concentric", "parallel", "perpendicular", "collinear"):
            out.append({"type": t, "e": [ent(r[0]), ent(r[1])]})
        elif t == "midpoint":
            pt, en = (r[0], r[1]) if is_point(r[0]) else (r[1], r[0])
            out.append({"type": "midpoint", "p": [point(pt)], "e": [ent(en)]})
        elif t == "symmetric":
            out.append({"type": "symmetry", "p": [point(r[0]), point(r[1])], "e": [ent(r[2])]})
            # Two circles or arcs mirrored about a line are also the same size.
            if not is_point(r[0]) and not is_point(r[1]) and "c" in sk.entities[ent(r[0])] and "c" in sk.entities[ent(r[1])]:
                out.append({"type": "equal", "e": [ent(r[0]), ent(r[1])]})
        else:
            raise Unsupported("sketch constraint '%s'" % t)
    for d in dims:
        t, r, v = d["type"], d["refs"], d["value"]
        if isinstance(v, str):
            raise Unsupported("dimension driven by a parameter")
        if t in ("distance", "offset"):
            pts = [x for x in r if is_point(x)]
            ents = [x for x in r if not is_point(x)]
            if len(pts) == 2:
                a, b = point(pts[0]), point(pts[1])
                o = d.get("orientation")
                if o in ("horizontal", "vertical"):
                    k = 0 if o == "horizontal" else 1
                    if xy(b)[k] < xy(a)[k]:
                        a, b = b, a
                    out.append({"type": o + "Distance", "p": [a, b], "v": v * MM})
                else:
                    out.append({"type": "distance", "p": [a, b], "v": v * MM})
            elif len(pts) == 1 and len(ents) == 1:
                out.append({"type": "distance", "p": [point(pts[0])], "e": [ent(ents[0])], "v": v * MM})
            elif len(ents) == 1 and not pts:
                out.append({"type": "distance", "e": [ent(ents[0])], "v": v * MM})
            else:
                raise Unsupported("distance between %s" % r)
        elif t in ("radius", "diameter"):
            out.append({"type": t, "e": [ent(r[0])], "v": v * MM})
        elif t == "angle":
            d1, d2 = line_dir(ent(r[0])), line_dir(ent(r[1]))
            signed = math.atan2(d1[0] * d2[1] - d1[1] * d2[0], d1[0] * d2[0] + d1[1] * d2[1])
            val = math.radians(v)
            # Keep the turn the drawing has (sign) and the size closest to it.
            cands = [val, -val, math.pi - val, val - math.pi]
            best = min(cands, key=lambda a: abs((a - signed + math.pi) % (2 * math.pi) - math.pi))
            out.append({"type": "angle", "e": [ent(r[0]), ent(r[1])], "v": best})
        else:
            raise Unsupported("dimension '%s'" % t)
    return out


# ---------------------------------------------------------------------------
# Profiles: a point inside the recipe's region, in sketch coordinates.


def chain(polys):
    """Join curve polylines into one closed polygon."""
    polys = [list(p) for p in polys if p]
    if len(polys) == 1:
        return polys[0]
    out = polys.pop(0)
    while polys:
        tail = out[-1]
        best, rev, bi = None, False, -1
        for i, p in enumerate(polys):
            for r, q in ((False, p[0]), (True, p[-1])):
                d = math.hypot(q[0] - tail[0], q[1] - tail[1])
                if best is None or d < best:
                    best, rev, bi = d, r, i
        p = polys.pop(bi)
        out += list(reversed(p)) if rev else p
    return out


def inside(pt, poly):
    x, y = pt
    c = False
    n = len(poly)
    for i in range(n):
        x1, y1 = poly[i]
        x2, y2 = poly[(i + 1) % n]
        if (y1 > y) != (y2 > y) and x < x1 + (y - y1) * (x2 - x1) / (y2 - y1):
            c = not c
    return c


def edge_distance(pt, poly):
    best = float("inf")
    n = len(poly)
    for i in range(n):
        ax, ay = poly[i]
        bx, by = poly[(i + 1) % n]
        dx, dy = bx - ax, by - ay
        l2 = dx * dx + dy * dy
        t = 0 if l2 == 0 else max(0, min(1, ((pt[0] - ax) * dx + (pt[1] - ay) * dy) / l2))
        best = min(best, math.hypot(pt[0] - ax - t * dx, pt[1] - ay - t * dy))
    return best


def region_point(outer, holes):
    xs, ys = [p[0] for p in outer], [p[1] for p in outer]
    best, bp = -1, None
    for i in range(1, 60):
        for j in range(1, 60):
            pt = [min(xs) + (max(xs) - min(xs)) * i / 60, min(ys) + (max(ys) - min(ys)) * j / 60]
            if not inside(pt, outer) or any(inside(pt, h) for h in holes):
                continue
            d = min([edge_distance(pt, outer)] + [edge_distance(pt, h) for h in holes])
            if d > best:
                best, bp = d, pt
    if bp is None:
        raise Unsupported("no point found inside a profile")
    return bp


def profile_points(sk, loops):
    """Points (cm, sketch coordinates) picking the region the loops describe.
    Closed loops of the sketch lying inside the outer loop but not listed as
    holes are part of the region: they get a point of their own."""
    outer = [l for l in loops if l.get("outer", True)]
    if len(outer) != 1:
        raise Unsupported("profile with %d outer loops" % len(outer))
    outer_poly = chain([sk.curves[c] for c in outer[0]["curves"]])
    listed_holes = [chain([sk.curves[c] for c in l["curves"]]) for l in loops if not l.get("outer", True)]
    used = set(c for l in loops for c in l["curves"])
    others = []
    for cid, poly in sk.curves.items():   # other closed curves (circles) inside the outer loop
        if cid in used or cid in sk.construction or not poly or len(poly) < 4:
            continue
        if math.hypot(poly[0][0] - poly[-1][0], poly[0][1] - poly[-1][1]) < 1e-9 and inside(poly[0], outer_poly):
            others.append(poly)
    pts = [region_point(outer_poly, listed_holes + others)]
    for o in others:
        if not any(inside(o[0], h) for h in listed_holes):
            pts.append(region_point(o, []))
    return pts


def profiles_arg(sketches, profiles):
    names = set(p["sketch"] for p in profiles)
    if len(names) != 1:
        raise Unsupported("profiles from %d sketches in one feature" % len(names))
    sk = sketches[names.pop()]
    pts = []
    for p in profiles:
        pts += profile_points(sk, p["loops"])
    return sk, ";".join("%.9g,%.9g" % (x * MM, y * MM) for x, y in pts)


# ---------------------------------------------------------------------------
# Bodies and features: recipe names -> Tessera names.


class State:
    def __init__(self):
        self.sketches = {}
        self.bodies = {}     # recipe body name -> Tessera body name
        self.features = {}   # recipe feature name -> Tessera feature name
        self.planes = {}


def body_list():
    import adsk.core
    import adsk.fusion
    root = adsk.fusion.Design.cast(adsk.core.Application.get().activeProduct).rootComponent
    return [root.bRepBodies.item(i).name for i in range(root.bRepBodies.count)]


def do(state, recipe_name, cmd, **kw):
    before_b, before_f = body_list(), [x["name"] for x in tsr.features()]
    tsr.run_command(cmd, **kw)
    after_f = [x for x in tsr.features() if x["name"] not in before_f]
    if after_f:
        state.features[recipe_name] = after_f[-1]["name"]
    return [b for b in body_list() if b not in before_b]


def name_results(state, f, new):
    for rname, tname in zip(f.get("result_bodies", []), new):
        state.bodies[rname] = tname


def target_of(state, f):
    for r in f.get("result_bodies", []):
        if r in state.bodies:
            return state.bodies[r]
    return ""


OPS = {"new": "New Body", "join": "Join", "cut": "Cut", "intersect": "Intersect"}


def body_at(pt_cm):
    """The body whose bounding box holds this point (first match)."""
    for b in body_list():
        (x0, y0, z0), (x1, y1, z1) = tsr.bounding_box(b)
        e = 1e-6
        if x0 - e <= pt_cm[0] <= x1 + e and y0 - e <= pt_cm[1] <= y1 + e and z0 - e <= pt_cm[2] <= z1 + e:
            return b
    return ""


def picks(items):
    return ";".join(fmt(cm(i["point"])) for i in items)


def world_axis(axis):
    o, d = axis["origin"], axis["dir"]
    if any(abs(v) > 1e-9 for v in o):
        raise Unsupported("axis not through the origin")
    for name, v in (("X", (1, 0, 0)), ("Y", (0, 1, 0)), ("Z", (0, 0, 1))):
        if abs(abs(sum(a * b for a, b in zip(d, v))) - 1) < 1e-9:
            return name, sum(a * b for a, b in zip(d, v)) < 0
    raise Unsupported("axis not along X, Y or Z")


def op_extrude(state, f):
    if f.get("thin") or "profiles" not in f:
        raise Unsupported("thin extrude")
    sk, prof = profiles_arg(state.sketches, f["profiles"])
    ext = f["extent"]
    kw = dict(sketch=sk.name, profiles=prof, operation=OPS[f.get("operation", "new")])
    t = ext["type"]
    if t == "distance":
        kw.update(extent="Distance", distance=ext["distance"] * MM * (-1 if ext.get("direction") == "negative" else 1))
        if ext.get("taper_deg"):
            kw["taper"] = math.radians(ext["taper_deg"])
    elif t == "through_all":
        kw.update(extent="All", distance=-1.0 if ext.get("direction") == "negative" else 1.0)
        if ext.get("direction") == "both":
            kw.update(direction="Symmetric")
    elif t == "symmetric":
        d = ext["distance"] * MM
        kw.update(extent="Distance", direction="Symmetric", distance=d / 2 if ext.get("is_full_length") else d)
    elif t == "two_sides":
        kw.update(extent="Distance", direction="Two Sides", distance=ext["side1"] * MM, distance2=ext["side2_opposite"] * MM)
    else:
        raise Unsupported("extrude extent '%s'" % t)
    if f.get("thin"):
        raise Unsupported("thin extrude")
    if kw["operation"] != "New Body":
        kw["target"] = target_of(state, f)
    name_results(state, f, do(state, f["name"], "tsr.feature.extrude", **kw))


def op_revolve(state, f):
    sk, prof = profiles_arg(state.sketches, [f["profile"]])
    axis, flipped = world_axis(f["axis"])
    angle = math.radians(f["angle"]) * (-1 if flipped else 1)
    kw = dict(sketch=sk.name, profiles=prof, axis=axis, angle=angle, operation=OPS[f.get("operation", "new")])
    if kw["operation"] != "New Body":
        kw["target"] = target_of(state, f)
    name_results(state, f, do(state, f["name"], "tsr.feature.revolve", **kw))


def op_fillet(state, f):
    if f.get("type", "constant_radius") != "constant_radius":
        raise Unsupported("fillet type '%s'" % f.get("type"))
    body = body_at(cm(f["edges"][0]["point"]))
    do(state, f["name"], "tsr.feature.fillet", body=body, edges=picks(f["edges"]), radius=f["radius"] * MM)


def op_chamfer(state, f):
    types = {"equal_distance": "Equal Distance"}
    if f.get("type", "equal_distance") not in types:
        raise Unsupported("chamfer type '%s'" % f.get("type"))
    body = body_at(cm(f["edges"][0]["point"]))
    do(state, f["name"], "tsr.feature.chamfer", body=body, edges=picks(f["edges"]), distance=f["distance"] * MM)


def op_shell(state, f):
    inner, outer = f.get("inside_thickness", 0), f.get("outside_thickness", 0)
    if inner and outer:
        raise Unsupported("shell with both inside and outside thickness")
    faces = f.get("faces_removed", [])
    body = body_at(cm(faces[0]["point"])) if faces else (body_list() or [""])[-1]
    do(state, f["name"], "tsr.feature.shell", body=body, faces=picks(faces), thickness=(inner or outer) * MM,
        direction="Inside" if inner else "Outside")


def pattern_features(state, f):
    if f.get("pattern_of") != "features":
        raise Unsupported("pattern of %s" % f.get("pattern_of"))
    names = []
    for n in f["features"]:
        # "HoleA (1)" names the first instance of the feature HoleA.
        base = n[:-4] if n.endswith(" (1)") and n not in state.features else n
        names.append(state.features[base])
    return ";".join(names)


def op_rectangular_pattern(state, f):
    kw = dict(patternType="Features", features=pattern_features(state, f), distanceType="Spacing")
    for k, key in ((1, "direction1"), (2, "direction2")):
        d = f.get(key)
        if not d:
            kw["quantity%d" % k] = 1
            continue
        axis, flipped = world_axis({"origin": [0, 0, 0], "dir": d["axis"]})
        kw["direction%d" % k] = axis
        kw["quantity%d" % k] = d["count"]
        kw["distance%d" % k] = d["spacing"] * MM * (-1 if flipped else 1)
    do(state, f["name"], "tsr.feature.rectangularPattern", **kw)


def op_circular_pattern(state, f):
    axis, flipped = world_axis(f["axis"])
    if f.get("symmetric"):
        raise Unsupported("symmetric circular pattern")
    do(state, f["name"], "tsr.feature.circularPattern", patternType="Features", features=pattern_features(state, f),
        axis=axis, quantity=f["count"], angle=math.radians(f["total_angle"]) * (-1 if flipped else 1))


def op_combine(state, f):
    do(state, f["name"], "tsr.feature.combine", target=state.bodies[f["target_body"]],
        tools=";".join(state.bodies[b] for b in f["tool_bodies"]), operation=OPS[f["operation"]],
        keep=bool(f.get("keep_tools")))


def op_construction_plane(state, f):
    if f.get("method") != "offset" or f.get("base") not in ("XY", "XZ", "YZ"):
        raise Unsupported("construction plane '%s'" % f.get("method"))
    do(state, f["name"], "tsr.construct.offsetPlane", name=f["name"], plane=f["base"], distance=f["offset"] * MM)
    state.planes[f["name"]] = f["name"]


def op_loft(state, f):
    if f.get("rails"):
        raise Unsupported("loft rails")
    names = []
    for s in f["sections"]:
        names.append(state.sketches[s["sketch"]].name)
    kw = dict(sections=";".join(names), operation=OPS[f.get("operation", "new")])
    name_results(state, f, do(state, f["name"], "tsr.feature.loft", **kw))


def op_sweep(state, f):
    sk, prof = profiles_arg(state.sketches, [f["profile"]])
    path = state.sketches[f["path"]["sketch"]]
    kw = dict(sketch=sk.name, profiles=prof, path=path.name, operation=OPS[f.get("operation", "new")])
    name_results(state, f, do(state, f["name"], "tsr.feature.sweep", **kw))


def hole_kw(f):
    types = {"simple": "Simple", "counterbore": "Counterbore", "countersink": "Countersink"}
    kw = dict(holeType=types[f.get("hole_type", "simple")], diameter=f["diameter"] * MM)
    if f.get("extent") == "through_all":
        kw["extent"] = "All"
    else:
        kw.update(extent="Distance", depth=f["depth"] * MM)
    if f.get("tip_angle") and f.get("extent") != "through_all":
        raise Unsupported("drill-point tip on a blind hole")
    if kw["holeType"] == "Counterbore":
        kw.update(cboreDiameter=f["counterbore_diameter"] * MM, cboreDepth=f["counterbore_depth"] * MM)
    if kw["holeType"] == "Countersink":
        kw.update(csinkDiameter=f["countersink_diameter"] * MM, csinkAngle=math.radians(f.get("countersink_angle", 90)))
    return kw


def op_hole(state, f):
    src = f.get("positions_from", "")
    if src.startswith("sketch "):
        # Holes at the points of a sketch: Tessera's Hole works this way.
        sk = state.sketches[src.split()[1]]
        do(state, f["name"], "tsr.feature.hole", sketch=sk.name, **hole_kw(f))
        return
    face = f["face"]
    if face.get("type") != "plane":
        raise Unsupported("hole on a %s face" % face.get("type"))
    n = face["plane_normal_outward"]
    p = face["point"]
    pos = f.get("position")
    if not isinstance(pos, list) or len(pos) != 3:
        raise Unsupported("hole positions given as '%s'" % f.get("positions_from", "?"))
    # A sketch on the face holding the hole centre.
    x = [1.0, 0.0, 0.0] if abs(n[0]) < 0.9 else [0.0, 1.0, 0.0]
    dot = sum(a * b for a, b in zip(x, n))
    x = [a - dot * b for a, b in zip(x, n)]
    l = math.sqrt(sum(a * a for a in x))
    x = [a / l for a in x]
    y = [n[1] * x[2] - n[2] * x[1], n[2] * x[0] - n[0] * x[2], n[0] * x[1] - n[1] * x[0]]
    rel = [a - b for a, b in zip(pos, p)]
    u, v = sum(a * b for a, b in zip(rel, x)), sum(a * b for a, b in zip(rel, y))
    data = {"points": [[0, 0], [u * MM, v * MM]], "entities": []}
    tsr.run_command("tsr.sketch.create", plane="custom:" + fmt(cm(p) + list(n) + x), data=json.dumps(data))
    sketch = [s for s in tsr.features() if s["command"] == "tsr.sketch.create"][-1]["name"]
    types = {"simple": "Simple", "counterbore": "Counterbore", "countersink": "Countersink"}
    kw = dict(sketch=sketch, holeType=types[f.get("hole_type", "simple")], diameter=f["diameter"] * MM,
              target=body_at(cm(p)))
    if f.get("extent") == "through_all":
        kw["extent"] = "All"
    else:
        kw.update(extent="Distance", depth=f["depth"] * MM)
    if f.get("tip_angle") and f.get("extent") != "through_all":
        raise Unsupported("drill-point tip on a blind hole")
    if kw["holeType"] == "Counterbore":
        kw.update(cboreDiameter=f["counterbore_diameter"] * MM, cboreDepth=f["counterbore_depth"] * MM)
    if kw["holeType"] == "Countersink":
        kw.update(csinkDiameter=f["countersink_diameter"] * MM, csinkAngle=math.radians(f.get("countersink_angle", 90)))
    do(state, f["name"], "tsr.feature.hole", **kw)


HANDLERS = {
    "extrude": op_extrude, "revolve": op_revolve, "fillet": op_fillet, "chamfer": op_chamfer, "shell": op_shell,
    "rectangular_pattern": op_rectangular_pattern, "circular_pattern": op_circular_pattern, "combine": op_combine,
    "construction_plane": op_construction_plane, "loft": op_loft, "sweep": op_sweep, "hole": op_hole,
}


# ---------------------------------------------------------------------------
# Measuring and comparing.


def measure():
    bodies = body_list()
    vol = area = 0.0
    com = [0.0, 0.0, 0.0]
    faces = 0
    lo, hi = [float("inf")] * 3, [float("-inf")] * 3
    for b in bodies:
        mp = tsr.mass_properties(b)
        vol += mp["volume"]
        area += mp["area"]
        faces += mp["patches"]   # the reference counts maximal smooth patches
        for k in range(3):
            com[k] += mp["center"][k] * mp["volume"]
        (x0, y0, z0), (x1, y1, z1) = tsr.bounding_box(b)
        lo = [min(a, b) for a, b in zip(lo, (x0, y0, z0))]
        hi = [max(a, b) for a, b in zip(hi, (x1, y1, z1))]
    com = [c / vol * 10 for c in com] if vol else com
    return {"body_count": len(bodies), "volume_mm3": vol * 1000, "area_mm2": area * 100, "center_of_mass": com,
            "bbox": {"min": [v * 10 for v in lo], "max": [v * 10 for v in hi]}, "faces": faces}


def compare(got, exp):
    tol = exp.get("tolerance", {})
    rel = tol.get("rel", 1e-3)
    bb = exp.get("bbox")
    diag = math.dist(bb["min"], bb["max"]) if bb else 100.0
    abs_mm = tol.get("abs_mm", 1e-3 * diag)
    keys = exp.get("compare") or ["body_count", "volume_mm3", "area_mm2", "center_of_mass", "bbox", "faces"]
    bad = []
    for k in keys:
        if k not in exp:
            continue
        e, g = exp[k], got[k]
        if k in ("volume_mm3", "area_mm2"):
            ok = abs(g - e) <= rel * max(abs(e), 1e-9)
        elif k == "center_of_mass":
            ok = math.dist(g, e) <= abs_mm
        elif k == "bbox":
            ok = math.dist(g["min"], e["min"]) <= abs_mm and math.dist(g["max"], e["max"]) <= abs_mm
        else:
            ok = g == e
        if not ok:
            bad.append("%s: got %s, expected %s" % (k, short(g), short(e)))
    return bad


def short(v):
    if isinstance(v, float):
        return "%.4g" % v
    if isinstance(v, list):
        return "[" + ", ".join(short(x) for x in v) + "]"
    if isinstance(v, dict):
        return "{" + ", ".join("%s: %s" % (k, short(x)) for k, x in v.items()) + "}"
    return str(v)


def run_case(path):
    recipe = json.load(open(os.path.join(path, "recipe.json"), encoding="utf-8"))
    expected = json.load(open(os.path.join(path, "expected.json"), encoding="utf-8"))
    tsr.new_document()
    state = State()
    if recipe.get("parameters"):
        raise Unsupported("recipe parameters")
    for f in recipe["features"]:
        op = f["op"]
        if op == "sketch":
            build_sketch(f, state.sketches)
        elif op in HANDLERS:
            HANDLERS[op](state, f)
        else:
            raise Unsupported("operation '%s'" % op)
    errors = [x for x in tsr.features() if x["error"]]
    if errors:
        return "fail", ["%s: %s" % (x["name"], x["error"]) for x in errors]
    bad = compare(measure(), expected)
    return ("pass" if not bad else "fail"), bad


def main():
    only = [s for s in os.environ.get("TSR_ORACLE_ONLY", "").split(",") if s]
    required = [s for s in os.environ.get("TSR_ORACLE_REQUIRE", "").split(",") if s]
    req_file = os.environ.get("TSR_ORACLE_REQUIRE_FILE")
    if req_file:
        required += [l.strip() for l in open(req_file, encoding="utf-8") if l.strip() and not l.startswith("#")]
    rows, counts = [], {"pass": 0, "fail": 0, "unsupported": 0, "error": 0}
    for case in sorted(os.listdir(CASES)):
        path = os.path.join(CASES, case)
        if not os.path.isfile(os.path.join(path, "recipe.json")) or (only and case not in only):
            continue
        try:
            status, notes = run_case(path)
        except Unsupported as e:
            status, notes = "unsupported", [str(e)]
        except Exception as e:   # a command refused the input, or a bug in this runner
            status, notes = "error", [str(e).splitlines()[0] if str(e) else type(e).__name__]
            if os.environ.get("TSR_ORACLE_TRACE"):
                traceback.print_exc()
        counts[status] += 1
        rows.append((case, status, notes))
        print("%-40s %-11s %s" % (case, status, "; ".join(notes)[:300]), flush=True)
    total = sum(counts.values())
    print("oracle: %d pass, %d fail, %d error, %d unsupported of %d" %
          (counts["pass"], counts["fail"], counts["error"], counts["unsupported"], total))
    report = os.environ.get("TSR_ORACLE_REPORT")
    if report:
        with open(report, "w", encoding="utf-8") as out:
            out.write("# Reference parts\n\n%d pass, %d fail, %d error, %d unsupported of %d.\n\n" %
                      (counts["pass"], counts["fail"], counts["error"], counts["unsupported"], total))
            out.write("| Case | Result | Notes |\n|---|---|---|\n")
            for case, status, notes in rows:
                out.write("| %s | %s | %s |\n" % (case, status, "; ".join(notes).replace("|", "/")))
    missing = [c for c in required if not any(r[0] == c and r[1] == "pass" for r in rows)]
    if missing:
        raise SystemExit("oracle: required cases did not pass: " + ", ".join(missing))


main()
