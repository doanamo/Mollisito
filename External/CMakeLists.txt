cmake_minimum_required(VERSION 3.25)
include(ExternalProject)

#
# fmt
#

ExternalProject_Add(External-fmt
    PREFIX fmt
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/External/fmt/
    BINARY_DIR ${PROJECT_BINARY_DIR}/External/fmt/
    INSTALL_DIR ${PROJECT_BINARY_DIR}/External/fmt/
    CMAKE_ARGS
        -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
        -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        -DFMT_MASTER_PROJECT=OFF -DFMT_INSTALL=ON
    INSTALL_COMMAND ""
)

set_property(TARGET External-fmt PROPERTY FOLDER External)
set_property(TARGET External-fmt PROPERTY PROJECT_LABEL fmt)

add_library(fmt STATIC IMPORTED GLOBAL)
add_dependencies(fmt External-fmt)
set_target_properties(fmt PROPERTIES
    IMPORTED_LOCATION_DEBUG ${PROJECT_BINARY_DIR}/External/fmt/Debug/fmtd.lib
    IMPORTED_LOCATION_RELEASE ${PROJECT_BINARY_DIR}/External/fmt/Release/fmt.lib
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/External/fmt/include/
)

#
# spdlog
#

externalproject_add(External-spdlog
    PREFIX spdlog
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/External/spdlog/
    BINARY_DIR ${PROJECT_BINARY_DIR}/External/spdlog/
    INSTALL_DIR ${PROJECT_BINARY_DIR}/External/spdlog/
    CMAKE_ARGS
        -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
        -DSPDLOG_MASTER_PROJECT=OFF -DSPDLOG_FMT_EXTERNAL=ON
        -Dfmt_DIR=${PROJECT_BINARY_DIR}/External/fmt/
    INSTALL_COMMAND ""
)

set_property(TARGET External-spdlog PROPERTY FOLDER External)
set_property(TARGET External-spdlog PROPERTY PROJECT_LABEL spdlog)

add_library(spdlog STATIC IMPORTED GLOBAL)
add_dependencies(spdlog External-spdlog)
set_target_properties(spdlog PROPERTIES
    IMPORTED_LOCATION_DEBUG ${PROJECT_BINARY_DIR}/External/spdlog/Debug/spdlogd.lib
    IMPORTED_LOCATION_RELEASE ${PROJECT_BINARY_DIR}/External/spdlog/Release/spdlog.lib
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/External/spdlog/include/
    INTERFACE_COMPILE_DEFINITIONS "SPDLOG_FMT_EXTERNAL;SPDLOG_COMPILED_LIB"
)

#
# SDL
#

externalproject_add(External-SDL
    PREFIX SDL
    SOURCE_DIR ${PROJECT_SOURCE_DIR}/External/SDL/
    BINARY_DIR ${PROJECT_BINARY_DIR}/External/SDL/
    INSTALL_DIR ${PROJECT_BINARY_DIR}/External/SDL/
    CMAKE_ARGS
        -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
        -DCMAKE_SHARED_LINKER_FLAGS_RELEASE=${CMAKE_SHARED_LINKER_FLAGS_RELEASE}
        -DSDL_STATIC=OFF -DSDL_TEST=OFF
    INSTALL_COMMAND ""
)

set_property(TARGET External-SDL PROPERTY FOLDER External)
set_property(TARGET External-SDL PROPERTY PROJECT_LABEL SDL)

add_library(SDL2main STATIC IMPORTED GLOBAL)
add_dependencies(SDL2main External-SDL)
set_target_properties(SDL2main PROPERTIES
    IMPORTED_LOCATION_DEBUG ${PROJECT_BINARY_DIR}/External/SDL/Debug/SDL2maind.lib
    IMPORTED_LOCATION_RELEASE ${PROJECT_BINARY_DIR}/External/SDL/Release/SDL2main.lib
    INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/External/SDL/include/
)

add_library(SDL2 SHARED IMPORTED GLOBAL)
add_dependencies(SDL2 External-SDL)
set_target_properties(SDL2 PROPERTIES
    IMPORTED_IMPLIB_DEBUG ${CMAKE_BINARY_DIR}/External/SDL/Debug/SDL2d.lib
    IMPORTED_LOCATION_DEBUG ${CMAKE_BINARY_DIR}/External/SDL/Debug/SDL2d.dll
    IMPORTED_IMPLIB_RELEASE ${CMAKE_BINARY_DIR}/External/SDL/Release/SDL2.lib
    IMPORTED_LOCATION_RELEASE ${CMAKE_BINARY_DIR}/External/SDL/Release/SDL2.dll
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/SDL/include/
)
