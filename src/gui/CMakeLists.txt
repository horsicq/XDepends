include(../../dep/build_tools/cmake/cpp_standart_setup.cmake)

add_definitions(-DUSE_DEX)
add_definitions(-DUSE_PDF)
add_definitions(-DUSE_ARCHIVE)
add_definitions(-DUSE_XPROCESS)

include(${CMAKE_CURRENT_LIST_DIR}/../../dep/archive_widget/archive_widget.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/StaticScan/formresult.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/XAboutWidget/xaboutwidget.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/XStyles/xstyles.cmake)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../dep/XProcessWidget)
include(${CMAKE_CURRENT_LIST_DIR}/../../dep/XProcess/xprocess.cmake)

find_package(Threads REQUIRED)

if(UNIX AND NOT APPLE)
    include(GNUInstallDirs)
endif()

set(XDEPENDS_GUI_SOURCES
    ${ARCHIVE_WIDGET_SOURCES}
    ${FORMRESULT_SOURCES}
    ${XABOUTWIDGET_SOURCES}
    ${XSTYLES_SOURCES}
    ${XPROCESS_SOURCES}
    "${CMAKE_CURRENT_LIST_DIR}/../../dep/XProcessWidget/dialogattachprocess.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/../../dep/XProcessWidget/dialogattachprocess.h"
    "${CMAKE_CURRENT_LIST_DIR}/../../dep/XProcessWidget/dialogattachprocess.ui"
    dialogoptions.cpp
    dialogoptions.h
    dialogoptions.ui
    guimainwindow.cpp
    guimainwindow.h
    guimainwindow.ui
    main_gui.cpp
    "${CMAKE_CURRENT_LIST_DIR}/../../res/resources_gui.qrc"
)

if(WIN32 AND EXISTS "${X_WINDOWS_RESOURCE_ICON_RC}")
    list(APPEND XDEPENDS_GUI_SOURCES "${X_WINDOWS_RESOURCE_ICON_RC}")
endif()

if(APPLE AND EXISTS "${X_MACOS_ICON}")
    set_source_files_properties("${X_MACOS_ICON}" PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    list(APPEND XDEPENDS_GUI_SOURCES "${X_MACOS_ICON}")
endif()

add_executable(XDepends WIN32
    ${XDEPENDS_GUI_SOURCES}
)

set_target_properties(XDepends PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE    TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "${MACOSX_BUNDLE_GUI_IDENTIFIER}"
    OUTPUT_NAME xdepends
)

target_include_directories(XDepends PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(XDepends PRIVATE
    bzip2
    lzma
    zlib
    ppmd
    capstone
    xsimd
    Qt${XDEPENDS_QT_MAJOR}::Widgets
    Qt${XDEPENDS_QT_MAJOR}::Concurrent
    Qt${XDEPENDS_QT_MAJOR}::Network
    Qt${XDEPENDS_QT_MAJOR}::PrintSupport
    Qt${XDEPENDS_QT_MAJOR}::Svg
    Threads::Threads
)

if(WIN32)
    target_link_libraries(XDepends PRIVATE Wintrust Crypt32)
endif()

if(TARGET xdepends_translations)
    add_dependencies(XDepends xdepends_translations)
endif()

if(UNIX AND NOT APPLE)
    set(XDEPENDS_RUNTIME_DEST "${CMAKE_INSTALL_BINDIR}")
    set(XDEPENDS_DOC_DEST     "${CMAKE_INSTALL_DOCDIR}/xdepends")

    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/../../res/linux/xdepends.desktop.in"
        "${CMAKE_CURRENT_BINARY_DIR}/xdepends.desktop"
        @ONLY
    )
else()
    set(XDEPENDS_RUNTIME_DEST ".")
    set(XDEPENDS_DOC_DEST     ".")
endif()

install(TARGETS XDepends
    RUNTIME DESTINATION ${XDEPENDS_RUNTIME_DEST}
    BUNDLE  DESTINATION .
)

if(UNIX AND NOT APPLE)
    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../README.md"
        DESTINATION ${XDEPENDS_DOC_DEST}
        OPTIONAL
    )
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/xdepends.desktop"
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications")
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../res/linux/hicolor/"
        DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor")
else()
    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../LICENSE"
        DESTINATION .
        RENAME LICENSE.txt
        OPTIONAL
    )
    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/../../README.md"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../res/license.txt"
        "${CMAKE_CURRENT_SOURCE_DIR}/../../res/readme.txt"
        "${X_WINDOWS_ICON}"
        DESTINATION .
        OPTIONAL
    )
    install(CODE [[file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/portable" "")]])
endif()

if(APPLE)
    include(${CMAKE_CURRENT_LIST_DIR}/../../dep/build_tools/cmake/macdeployqt.cmake)
endif()

if(WIN32)
    include(${CMAKE_CURRENT_LIST_DIR}/../../dep/build_tools/cmake/deploy_qt_windows.cmake)
    include(${CMAKE_CURRENT_LIST_DIR}/../../dep/build_tools/cmake/deploy_msvc.cmake)
endif()
