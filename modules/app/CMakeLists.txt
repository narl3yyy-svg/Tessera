set(CMAKE_AUTOMOC ON)

add_executable(tessera
  src/main.cpp
  src/MainWindow.cpp
  src/MainWindow.h
  src/CommandDialog.cpp
  src/CommandDialog.h)
target_link_libraries(tessera PRIVATE tsr::api Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS tessera tessera-cli RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES ${PROJECT_SOURCE_DIR}/packaging/org.tessera.Tessera.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)
