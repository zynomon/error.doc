cmake_minimum_required(VERSION 3.16)

project(error_doc VERSION 0.1 LANGUAGES CXX)

# Qt setup
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WebEngineWidgets)

add_executable(error_doc
    main.cpp
)

target_link_libraries(error_doc PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::WebEngineWidgets
)

include(GNUInstallDirs)

# Install rules
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

# Packaging
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "error_doc")
set(CPACK_PACKAGE_VENDOR "error.os")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Error Doc is a Qt-based documentation viewer and system manager. \
    It integrates error.os principles of clarity, survivability, and mythic branding. \
    Error Doc provides a clean tabbed interface for CSS/QSS theme editing, \
    restricted web documentation access, manpage placeholders, and bookmarks. \
    Designed for minimal footprint and reproducible builds."
)
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_CONTACT "Zynomon Aelius <zynomon@proton.me>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Zynomon Aelius")

set(CPACK_GENERATOR "DEB;TGZ;ZIP")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6, libqt6core6, libqt6gui6, libqt6widgets6, libqt6webenginewidgets6")

include(CPack)

# Convenience target to run the app
add_custom_target(run
    COMMAND error_doc
    DEPENDS error_doc
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
