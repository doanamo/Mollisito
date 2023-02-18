cmake_minimum_required(VERSION 3.25)
include(ExternalProject)

#
# Checksums
#

add_custom_target(Checksums
    COMMAND python ${CMAKE_CURRENT_LIST_DIR}/Checksums.py
        ${CMAKE_BINARY_DIR}/External/Checksums/
)

set_property(TARGET Checksums PROPERTY FOLDER External)

#
# fmt
#

externalproject_add(External-fmt
    PREFIX fmt
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/fmt/
    BINARY_DIR fmt/src/build/
    CMAKE_ARGS -DFMT_MASTER_PROJECT=OFF
    DEPENDS Checksums
    INSTALL_COMMAND ""
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
# SDL
#

externalproject_add(External-SDL
    PREFIX SDL
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/SDL/
    BINARY_DIR SDL/src/build/
    CMAKE_ARGS -DSDL_STATIC=OFF -DSDL_TEST=OFF
    DEPENDS Checksums
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
