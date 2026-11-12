set(CMAKE_AUTOMOC ON)

add_executable(tessera
  src/main.cpp
  src/MainWindow.cpp
  src/MainWindow.h
  src/MainWindowSketch.cpp
  src/MainWindowTools.cpp
  src/MainWindowArrow.cpp
  src/SketchEditor.cpp
  src/SketchEditor.h
  src/ViewportSketch.cpp
  src/ViewportArrow.cpp
  src/CommandDialog.cpp
  src/CommandDialog.h
  src/ParametersDialog.cpp
  src/ParametersDialog.h
  src/Icons.cpp
  src/Theme.cpp
  src/Theme.h
  src/Icons.h
  src/Viewport.cpp
  src/Viewport.h)
target_link_libraries(tessera PRIVATE tsr::api Qt6::Widgets Qt6::OpenGLWidgets TKV3d TKOpenGl TKService)

include(GNUInstallDirs)
install(TARGETS tessera tessera-cli RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${PROJECT_SOURCE_DIR}/packaging/org.tessera.Tessera.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
install(FILES ${PROJECT_SOURCE_DIR}/packaging/org.tessera.Tessera.svg
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps)
install(FILES ${PROJECT_SOURCE_DIR}/packaging/org.tessera.Tessera.xml
        DESTINATION ${CMAKE_INSTALL_DATADIR}/mime/packages)
