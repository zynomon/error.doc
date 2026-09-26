cmake_minimum_required(VERSION 3.16)

project(doc VERSION 1.5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)

include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)

include(/usr/lib/cmake/Trig/TrigConfig.cmake)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    TextToSpeech
)

qt_add_resources(DOC_RESOURCES
    rc/r.qrc
)

add_executable(doc
    main.cpp
    ${DOC_RESOURCES}
)

target_link_libraries(doc
    PRIVATE
        Qt6::Core
        Qt6::Widgets
        Qt6::TextToSpeech
        Trig::term
)

install(
    TARGETS doc
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/install/error.doc.desktop.in
    ${CMAKE_CURRENT_BINARY_DIR}/error.doc.desktop
    @ONLY
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/error.doc.desktop
    DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/applications
    COMPONENT desktop
)

install(
    FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/install/error.doc.svg
    DESTINATION
        ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps
    COMPONENT icon
)

set(CPACK_PACKAGE_NAME "doc")
set(CPACK_PACKAGE_VENDOR "error.os")
set(
    CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "doc is a Qt-based documentation viewer check project at github.com/zynomon/error.doc"
)

set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "<zynomon@proton.me>")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Zynomon Aelius")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS OFF)

set(
    CPACK_DEBIAN_PACKAGE_DEPENDS
    "libqt6core6, libqt6gui6, libqt6widgets6, libqt6texttospeech6, libterm"
)

set(
    CPACK_DEBIAN_PACKAGE_RECOMMENDS
    "speech-dispatcher, espeak, espeak-ng, man-db"
)

set(
    CPACK_DEBIAN_PACKAGE_SUGGESTS
    "festival, mbrola"
)

set(CPACK_GENERATOR "DEB;TGZ;ZIP")

include(CPack)
