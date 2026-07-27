if(TARGET Qt6::Core OR TARGET Qt6::Widgets)
    set(XDEPENDS_QT_MAJOR 6)
elseif(TARGET Qt5::Core OR TARGET Qt5::Widgets)
    set(XDEPENDS_QT_MAJOR 5)
else()
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
    set(XDEPENDS_QT_MAJOR ${QT_VERSION_MAJOR})
endif()

set(XDEPENDS_QT_COMPONENTS
    Widgets
    Concurrent
    Network
    PrintSupport
    OpenGL
    Svg
)

if(XDEPENDS_QT_MAJOR EQUAL 5)
    find_package(Qt5 REQUIRED COMPONENTS ${XDEPENDS_QT_COMPONENTS} LinguistTools)
elseif(XDEPENDS_QT_MAJOR GREATER_EQUAL 6)
    find_package(Qt${XDEPENDS_QT_MAJOR} REQUIRED COMPONENTS ${XDEPENDS_QT_COMPONENTS} LinguistTools)

    if(NOT TARGET Qt5::Widgets)
        add_library(Qt5::Widgets INTERFACE IMPORTED)
        set_property(TARGET Qt5::Widgets PROPERTY
            INTERFACE_LINK_LIBRARIES Qt${XDEPENDS_QT_MAJOR}::Widgets)
    endif()
endif()

file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/../release_version.txt" X_PROJECT_VERSION)
project(XDepends VERSION ${X_PROJECT_VERSION} LANGUAGES CXX)

set(X_COMPANYNAME    "ntinfo")
set(X_PROJECTNAME    "XDepends")
set(X_MAINTAINER     "horsicq@gmail.com")
set(X_DESCRIPTION    "XDepends is a dependency viewer")
set(X_HOMEPAGE       "http://ntinfo.biz")
set(X_ORIGINAL_FILENAME "xdepends")

if(NOT DEFINED MACOSX_BUNDLE_GUI_IDENTIFIER OR "${MACOSX_BUNDLE_GUI_IDENTIFIER}" STREQUAL "")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.ntinfo.xdepends")
endif()
set(BUNDLE_ID_OPTION "${MACOSX_BUNDLE_GUI_IDENTIFIER}")

set(X_RESOURCE_DIR               "${CMAKE_CURRENT_LIST_DIR}/../res")
set(X_WINDOWS_ICON               "${X_RESOURCE_DIR}/windows/main.ico")
set(X_WINDOWS_RESOURCE_RC_IN     "${X_RESOURCE_DIR}/windows/resource.rc.in")
set(X_WINDOWS_RESOURCE_ICON_RC_IN "${X_RESOURCE_DIR}/windows/resource_icon.rc.in")
set(X_WINDOWS_RESOURCE_RC        "${X_RESOURCE_DIR}/windows/resource.rc")
set(X_WINDOWS_RESOURCE_ICON_RC   "${X_RESOURCE_DIR}/windows/resource_icon.rc")
set(X_MACOS_ICON                 "${X_RESOURCE_DIR}/macos/main.icns")
set(X_MACOS_INFO_PLIST_IN        "${X_RESOURCE_DIR}/macos/Info.plist.in")
set(X_MACOS_INFO_PLIST           "${X_RESOURCE_DIR}/macos/Info.plist")

set(XDEPENDS_DEPLOY_INIT "${CMAKE_CURRENT_LIST_DIR}/../dep/build_tools/cmake/deploy_init.cmake")
if(EXISTS "${XDEPENDS_DEPLOY_INIT}"
   AND EXISTS "${X_WINDOWS_RESOURCE_RC_IN}"
   AND EXISTS "${X_WINDOWS_RESOURCE_ICON_RC_IN}"
   AND EXISTS "${X_MACOS_ICON}"
   AND EXISTS "${X_MACOS_INFO_PLIST_IN}")
    include("${XDEPENDS_DEPLOY_INIT}")
else()
    message(STATUS "Skipping deploy_init.cmake — packaging templates missing")
endif()

set(XDEPENDS_TRANSLATION_HELPER "${CMAKE_CURRENT_LIST_DIR}/../dep/build_tools/cmake/deploy_translation.cmake")
if(EXISTS "${XDEPENDS_TRANSLATION_HELPER}")
    include("${XDEPENDS_TRANSLATION_HELPER}")

    set(XDEPENDS_TS_FILES
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_ar_AR.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_bn_BN.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_de_DE.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_es_ES.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_fa_FA.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_fr_FR.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_he_IL.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_id_ID.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_it_IT.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_ja_JP.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_ko_KR.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_pl_PL.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_pt_BR.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_pt_PT.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_ru_RU.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_sv_SE.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_tr_TR.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_uk_UA.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_vi_VN.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_zh_CN.ts"
        "${CMAKE_CURRENT_LIST_DIR}/../translations/xdepends_zh_TW.ts"
    )

    deploy_add_translations(
        TARGET_NAME xdepends_translations
        ADD_TO_ALL
        SOURCE_DIRS "${CMAKE_CURRENT_LIST_DIR}"
        TS_FILES ${XDEPENDS_TS_FILES}
        INSTALL_DESTINATION lang
        WINDOWS_APPDATA_SUBDIR "${X_PROJECTNAME}"
    )
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../dep/XCapstone" XCapstone)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../dep/XArchive" XArchive)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../dep/Formats/xsimd" XSIMD)

add_subdirectory(gui)
add_subdirectory(console)
