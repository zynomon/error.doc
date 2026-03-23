cmake_minimum_required(VERSION 3.16)
project(error_doc  VERSION 1.2 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets TextToSpeech)
qt_add_resources(DOC err/err.qrc)
add_executable(error_doc main.cpp
    ${DOC})
target_link_libraries(error_doc Qt6::Core Qt6::Widgets Qt6::TextToSpeech)

# install and other stuffs

install(TARGETS error_doc
RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

configure_file(
${CMAKE_CURRENT_SOURCE_DIR}/install/error.doc.desktop.in
${CMAKE_CURRENT_BINARY_DIR}/error.doc.desktop
@ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/error.doc.desktop
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications
    COMPONENT desktop)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/install/error.doc.svg
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps
    COMPONENT icon)

set(CPACK_PACKAGE_NAME "error_doc")
set(CPACK_PACKAGE_VENDOR "error.os")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Error Doc is a Qt-based documentation viewer check project at github.com/zynomon/error.doc"
)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT "Zynomon Aelius <zynomon@proton.me>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Zynomon Aelius")

set(CPACK_GENERATOR "DEB;TGZ;ZIP")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libqt6core6, libqt6gui6, libqt6widgets6, libqt6webenginewidgets6")

include(CPack)
