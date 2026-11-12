#pragma once
// File exchange. Internal lengths are cm; files are written in millimetres
// (STEP, IGES, STL, OBJ and 3MF all assume mm unless told otherwise), and
// imported files are converted back. BREP is OCCT's own format, kept in cm.
#include <TopoDS_Shape.hxx>

#include <filesystem>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace tsr::kernel {

enum class FileFormat { Step, Iges, Stl, Obj, ThreeMF, Brep };

struct FormatInfo {
  FileFormat format;
  const char* name;        // "STEP"
  const char* extensions;  // "*.step *.stp"
  bool canImport;
};
const std::vector<FormatInfo>& fileFormats();
std::optional<FileFormat> formatForPath(const std::filesystem::path& path);

using NamedShape = std::pair<std::string, TopoDS_Shape>;

// Writes the bodies to `path`. Meshed formats use `refinement` (0 = coarse,
// 1 = medium, 2 = fine). Throws KernelError.
void exportShapes(const std::filesystem::path& path, const std::vector<NamedShape>& bodies, FileFormat format,
                  int refinement = 1);

// Reads a STEP, IGES, STL or BREP file as one shape (internal units).
TopoDS_Shape importShape(const std::filesystem::path& path);

// BREP text, for storing geometry inside the document.
std::string toBrep(const TopoDS_Shape& shape);
TopoDS_Shape fromBrep(const std::string& text);

} // namespace tsr::kernel
