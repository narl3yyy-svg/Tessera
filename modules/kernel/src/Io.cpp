#include "tsr/kernel/Io.h"
#include "tsr/kernel/Kernel.h"

#include "tsr/core/Zip.h"

#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepTools.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <IGESControl_Reader.hxx>
#include <IGESControl_Writer.hxx>
#include <Interface_Static.hxx>
#include <Poly_Triangulation.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <Standard_Failure.hxx>
#include <StlAPI_Reader.hxx>
#include <StlAPI_Writer.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Shell.hxx>
#include <gp_Trsf.hxx>

#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <sstream>

namespace tsr::kernel {

namespace {

constexpr double kCmToMm = 10.0;

TopoDS_Shape scaled(const TopoDS_Shape& s, double f) {
  gp_Trsf t;
  t.SetScale(gp_Pnt(0, 0, 0), f);
  return BRepBuilderAPI_Transform(s, t, true).Shape();
}

TopoDS_Compound compoundOf(const std::vector<NamedShape>& bodies) {
  TopoDS_Compound c;
  BRep_Builder b;
  b.MakeCompound(c);
  for (const auto& [name, s] : bodies)
    if (!s.IsNull()) b.Add(c, s);
  return c;
}

struct Mesh {
  std::vector<gp_Pnt> nodes;
  std::vector<std::array<int, 3>> triangles;   // 0-based
};

// Triangulates one body in mm.
Mesh meshOf(const TopoDS_Shape& cmShape, int refinement) {
  const TopoDS_Shape s = scaled(cmShape, kCmToMm);
  const BoundingBox bb = boundingBox(s);
  const double diag = std::sqrt(std::pow(bb.max.x - bb.min.x, 2) + std::pow(bb.max.y - bb.min.y, 2) +
                                std::pow(bb.max.z - bb.min.z, 2));
  const double factor[] = {0.004, 0.001, 0.0002};
  const double angle[] = {0.5, 0.3, 0.15};
  const int r = std::clamp(refinement, 0, 2);
  BRepMesh_IncrementalMesh(s, std::max(diag * factor[r], 0.001), false, angle[r], true);
  Mesh m;
  for (TopExp_Explorer it(s, TopAbs_FACE); it.More(); it.Next()) {
    const TopoDS_Face& f = TopoDS::Face(it.Current());
    TopLoc_Location loc;
    const Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(f, loc);
    if (tri.IsNull()) continue;
    const int base = static_cast<int>(m.nodes.size());
    for (int i = 1; i <= tri->NbNodes(); ++i) m.nodes.push_back(tri->Node(i).Transformed(loc));
    const bool reversed = f.Orientation() == TopAbs_REVERSED;
    for (int i = 1; i <= tri->NbTriangles(); ++i) {
      int a, b, c;
      tri->Triangle(i).Get(a, b, c);
      if (reversed) std::swap(b, c);
      m.triangles.push_back({base + a - 1, base + b - 1, base + c - 1});
    }
  }
  return m;
}

std::string fmt(double v) {
  char buf[32];
  std::snprintf(buf, sizeof buf, "%.6g", v);
  return buf;
}

void writeObj(const std::filesystem::path& path, const std::vector<NamedShape>& bodies, int refinement) {
  std::ofstream os(path);
  if (!os) throw KernelError("cannot write " + path.string());
  os << "# Exported by Tessera (units: mm)\n";
  int offset = 1;
  for (const auto& [name, s] : bodies) {
    const Mesh m = meshOf(s, refinement);
    os << "o " << name << "\n";
    for (const auto& p : m.nodes) os << "v " << fmt(p.X()) << ' ' << fmt(p.Y()) << ' ' << fmt(p.Z()) << "\n";
    for (const auto& t : m.triangles) os << "f " << t[0] + offset << ' ' << t[1] + offset << ' ' << t[2] + offset << "\n";
    offset += static_cast<int>(m.nodes.size());
  }
  if (!os) throw KernelError("write failed: " + path.string());
}

std::string xmlEscape(const std::string& s) {
  std::string out;
  for (char c : s) {
    switch (c) {
      case '&': out += "&amp;"; break;
      case '<': out += "&lt;"; break;
      case '>': out += "&gt;"; break;
      case '"': out += "&quot;"; break;
      default: out += c;
    }
  }
  return out;
}

void write3mf(const std::filesystem::path& path, const std::vector<NamedShape>& bodies, int refinement) {
  std::ostringstream model;
  model << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
           "<model unit=\"millimeter\" xml:lang=\"en-US\" "
           "xmlns=\"http://schemas.microsoft.com/3dmanufacturing/core/2015/02\">\n"
           " <metadata name=\"Application\">Tessera</metadata>\n <resources>\n";
  int id = 1;
  for (const auto& [name, s] : bodies) {
    const Mesh m = meshOf(s, refinement);
    model << "  <object id=\"" << id++ << "\" name=\"" << xmlEscape(name) << "\" type=\"model\">\n   <mesh>\n    <vertices>\n";
    for (const auto& p : m.nodes)
      model << "     <vertex x=\"" << fmt(p.X()) << "\" y=\"" << fmt(p.Y()) << "\" z=\"" << fmt(p.Z()) << "\"/>\n";
    model << "    </vertices>\n    <triangles>\n";
    for (const auto& t : m.triangles)
      model << "     <triangle v1=\"" << t[0] << "\" v2=\"" << t[1] << "\" v3=\"" << t[2] << "\"/>\n";
    model << "    </triangles>\n   </mesh>\n  </object>\n";
  }
  model << " </resources>\n <build>\n";
  for (int i = 1; i < id; ++i) model << "  <item objectid=\"" << i << "\"/>\n";
  model << " </build>\n</model>\n";

  std::vector<zip::Entry> entries(3);
  entries[0].name = "[Content_Types].xml";
  entries[0].data =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
      "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
      "<Default Extension=\"model\" ContentType=\"application/vnd.ms-package.3dmanufacturing-3dmodel+xml\"/>"
      "</Types>\n";
  entries[1].name = "_rels/.rels";
  entries[1].data =
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
      "<Relationship Target=\"/3D/3dmodel.model\" Id=\"rel0\" "
      "Type=\"http://schemas.microsoft.com/3dmanufacturing/2013/01/3dmodel\"/></Relationships>\n";
  entries[2].name = "3D/3dmodel.model";
  entries[2].data = model.str();
  zip::write(path, entries);
}

std::string lower(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
  return s;
}

} // namespace

const std::vector<FormatInfo>& fileFormats() {
  static const std::vector<FormatInfo> f = {
      {FileFormat::Step, "STEP", "*.step *.stp", true},
      {FileFormat::Iges, "IGES", "*.iges *.igs", true},
      {FileFormat::Stl, "STL (mesh)", "*.stl", true},
      {FileFormat::ThreeMF, "3MF (3D printing)", "*.3mf", false},
      {FileFormat::Obj, "OBJ (mesh)", "*.obj", false},
      {FileFormat::Brep, "OpenCASCADE BREP", "*.brep", true},
  };
  return f;
}

std::optional<FileFormat> formatForPath(const std::filesystem::path& path) {
  const std::string e = lower(path.extension().string());
  if (e == ".step" || e == ".stp") return FileFormat::Step;
  if (e == ".iges" || e == ".igs") return FileFormat::Iges;
  if (e == ".stl") return FileFormat::Stl;
  if (e == ".obj") return FileFormat::Obj;
  if (e == ".3mf") return FileFormat::ThreeMF;
  if (e == ".brep") return FileFormat::Brep;
  return std::nullopt;
}

void exportShapes(const std::filesystem::path& path, const std::vector<NamedShape>& bodies, FileFormat format,
                  int refinement) {
  if (bodies.empty()) throw KernelError("there is nothing to export");
  try {
    switch (format) {
      case FileFormat::Step: {
        Interface_Static::SetCVal("write.step.unit", "MM");
        STEPControl_Writer w;
        if (w.Transfer(scaled(compoundOf(bodies), kCmToMm), STEPControl_AsIs) != IFSelect_RetDone ||
            w.Write(path.string().c_str()) != IFSelect_RetDone)
          throw KernelError("STEP export failed");
        return;
      }
      case FileFormat::Iges: {
        IGESControl_Writer w("MM", 1);
        w.AddShape(scaled(compoundOf(bodies), kCmToMm));
        w.ComputeModel();
        if (!w.Write(path.string().c_str())) throw KernelError("IGES export failed");
        return;
      }
      case FileFormat::Stl: {
        // Mesh in mm, then write binary STL.
        TopoDS_Compound c;
        BRep_Builder b;
        b.MakeCompound(c);
        for (const auto& [name, s] : bodies) {
          const TopoDS_Shape mm = scaled(s, kCmToMm);
          const BoundingBox bb = boundingBox(mm);
          const double diag = std::sqrt(std::pow(bb.max.x - bb.min.x, 2) + std::pow(bb.max.y - bb.min.y, 2) +
                                        std::pow(bb.max.z - bb.min.z, 2));
          const double factor[] = {0.004, 0.001, 0.0002};
          const double angle[] = {0.5, 0.3, 0.15};
          const int r = std::clamp(refinement, 0, 2);
          BRepMesh_IncrementalMesh(mm, std::max(diag * factor[r], 0.001), false, angle[r], true);
          b.Add(c, mm);
        }
        StlAPI_Writer w;
        w.ASCIIMode() = false;
        if (!w.Write(c, path.string().c_str())) throw KernelError("STL export failed");
        return;
      }
      case FileFormat::Obj: writeObj(path, bodies, refinement); return;
      case FileFormat::ThreeMF: write3mf(path, bodies, refinement); return;
      case FileFormat::Brep:
        if (!BRepTools::Write(compoundOf(bodies), path.string().c_str())) throw KernelError("BREP export failed");
        return;
    }
  } catch (const Standard_Failure& f) {
    throw KernelError(std::string("export: ") + f.GetMessageString());
  }
}

TopoDS_Shape importShape(const std::filesystem::path& path) {
  const auto format = formatForPath(path);
  if (!format) throw KernelError("unsupported file type: " + path.extension().string());
  if (!std::filesystem::exists(path)) throw KernelError("file not found: " + path.string());
  TopoDS_Shape s;
  try {
    switch (*format) {
      case FileFormat::Step: {
        STEPControl_Reader r;
        if (r.ReadFile(path.string().c_str()) != IFSelect_RetDone) throw KernelError("cannot read STEP file");
        r.TransferRoots();
        s = scaled(r.OneShape(), 1.0 / kCmToMm);
        break;
      }
      case FileFormat::Iges: {
        IGESControl_Reader r;
        if (r.ReadFile(path.string().c_str()) != IFSelect_RetDone) throw KernelError("cannot read IGES file");
        r.TransferRoots();
        s = scaled(r.OneShape(), 1.0 / kCmToMm);
        break;
      }
      case FileFormat::Stl: {
        TopoDS_Shape raw;
        StlAPI_Reader r;
        if (!r.Read(raw, path.string().c_str())) throw KernelError("cannot read STL file");
        // Closed meshes become solids so they can take part in booleans.
        BRepBuilderAPI_Sewing sew(1e-6);
        sew.Add(raw);
        sew.Perform();
        TopoDS_Shape sewn = sew.SewedShape();
        TopExp_Explorer shell(sewn, TopAbs_SHELL);
        if (shell.More()) {
          BRepBuilderAPI_MakeSolid mk(TopoDS::Shell(shell.Current()));
          if (mk.IsDone()) sewn = mk.Solid();
        }
        s = scaled(sewn, 1.0 / kCmToMm);
        break;
      }
      case FileFormat::Brep: {
        BRep_Builder b;
        if (!BRepTools::Read(s, path.string().c_str(), b)) throw KernelError("cannot read BREP file");
        break;
      }
      default:
        throw KernelError("this format can be exported but not imported");
    }
  } catch (const Standard_Failure& f) {
    throw KernelError(std::string("import: ") + f.GetMessageString());
  }
  if (s.IsNull()) throw KernelError("the file contains no geometry");
  return s;
}

std::string toBrep(const TopoDS_Shape& shape) {
  std::ostringstream os;
  BRepTools::Write(shape, os);
  return os.str();
}

TopoDS_Shape fromBrep(const std::string& text) {
  std::istringstream is(text);
  TopoDS_Shape s;
  BRep_Builder b;
  BRepTools::Read(s, is, b);
  if (s.IsNull()) throw KernelError("stored geometry could not be read");
  return s;
}

} // namespace tsr::kernel
