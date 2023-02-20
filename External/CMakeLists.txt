cmake_minimum_required(VERSION 3.25)
include(ExternalProject)

#
# Checksums
#

add_custom_target(External-Checksums
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/Checksums.py
        ${CMAKE_BINARY_DIR}/External/Checksums/
)

set_property(TARGET External-Checksums PROPERTY FOLDER External)
set_property(TARGET External-Checksums PROPERTY PROJECT_LABEL Checksums)

#
# fmt
#

externalproject_add(External-fmt
    PREFIX fmt
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/fmt/
    BINARY_DIR fmt/src/build/
    INSTALL_DIR fmt/src/install/
    CMAKE_ARGS
        -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
        -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
        -DFMT_MASTER_PROJECT=OFF -DFMT_INSTALL=ON
    DEPENDS External-Checksums
)

externalproject_add_step(External-fmt checksum
    DEPENDS ${CMAKE_BINARY_DIR}/External/Checksums/fmt.txt
    DEPENDERS configure
)

set_property(TARGET External-fmt PROPERTY FOLDER External)
set_property(TARGET External-fmt PROPERTY PROJECT_LABEL fmt)

add_library(fmt STATIC IMPORTED GLOBAL)
set_target_properties(fmt PROPERTIES
    IMPORTED_LOCATION_DEBUG ${CMAKE_BINARY_DIR}/External/fmt/src/build/Debug/fmtd.lib
    IMPORTED_LOCATION_RELEASE ${CMAKE_BINARY_DIR}/External/fmt/src/build/Release/fmt.lib
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/fmt/include/
)

#
# spdlog
#

externalproject_add(External-spdlog
    PREFIX spdlog
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/spdlog/
    BINARY_DIR spdlog/src/build/
    CMAKE_ARGS
        -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
        -DSPDLOG_MASTER_PROJECT=OFF -DSPDLOG_FMT_EXTERNAL=ON
        -Dfmt_DIR=${CMAKE_BINARY_DIR}/External/fmt/src/install/lib/cmake/fmt/
    DEPENDS External-Checksums External-fmt
    INSTALL_COMMAND ""
)

externalproject_add_step(External-spdlog checksum
    DEPENDS ${CMAKE_BINARY_DIR}/External/Checksums/spdlog.txt
    DEPENDERS configure
)

set_property(TARGET External-spdlog PROPERTY FOLDER External)
set_property(TARGET External-spdlog PROPERTY PROJECT_LABEL spdlog)

add_library(spdlog STATIC IMPORTED GLOBAL)
set_target_properties(spdlog PROPERTIES
    IMPORTED_LOCATION_DEBUG ${CMAKE_BINARY_DIR}/External/spdlog/src/build/Debug/spdlogd.lib
    IMPORTED_LOCATION_RELEASE ${CMAKE_BINARY_DIR}/External/spdlog/src/build/Release/spdlog.lib
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/spdlog/include/
    INTERFACE_COMPILE_DEFINITIONS "SPDLOG_FMT_EXTERNAL;SPDLOG_COMPILED_LIB"
)

#
# SDL
#

externalproject_add(External-SDL
    PREFIX SDL
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/SDL/
    BINARY_DIR SDL/src/build/
    CMAKE_ARGS
        -DCMAKE_C_FLAGS_RELEASE=${CMAKE_C_FLAGS_RELEASE}
        -DSDL_STATIC=OFF -DSDL_TEST=OFF
    DEPENDS External-Checksums
    INSTALL_COMMAND ""
)

externalproject_add_step(External-SDL checksum
    DEPENDS ${CMAKE_BINARY_DIR}/External/Checksums/SDL.txt
    DEPENDERS configure
)

set_property(TARGET External-SDL PROPERTY FOLDER External)
set_property(TARGET External-SDL PROPERTY PROJECT_LABEL SDL)

add_library(SDL2main STATIC IMPORTED GLOBAL)
set_target_properties(SDL2main PROPERTIES
    IMPORTED_LOCATION_DEBUG ${CMAKE_BINARY_DIR}/External/SDL/src/build/Debug/SDL2maind.lib
    IMPORTED_LOCATION_RELEASE ${CMAKE_BINARY_DIR}/External/SDL/src/build/Release/SDL2main.lib
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/SDL/include/
)

add_library(SDL2 SHARED IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
    IMPORTED_IMPLIB_DEBUG ${CMAKE_BINARY_DIR}/External/SDL/src/build/Debug/SDL2d.lib
    IMPORTED_LOCATION_DEBUG ${CMAKE_BINARY_DIR}/External/SDL/src/build/Debug/SDL2d.dll
    IMPORTED_IMPLIB_RELEASE ${CMAKE_BINARY_DIR}/External/SDL/src/build/Release/SDL2.lib
    IMPORTED_LOCATION_RELEASE ${CMAKE_BINARY_DIR}/External/SDL/src/build/Release/SDL2.dll
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/SDL/include/
)
