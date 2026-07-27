set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(UNIX AND NOT APPLE)
    include(GNUInstallDirs)
endif()

add_executable(xdependsc
    main_console.cpp
)

target_include_directories(xdependsc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(xdependsc PRIVATE
    Qt${XDEPENDS_QT_MAJOR}::Core
)

if(TARGET xdepends_translations)
    add_dependencies(xdependsc xdepends_translations)
endif()

if(UNIX AND NOT APPLE)
    install(TARGETS xdependsc RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
else()
    install(TARGETS xdependsc RUNTIME DESTINATION ".")
endif()
