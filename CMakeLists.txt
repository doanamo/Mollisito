cmake_minimum_required(VERSION 3.25)

#
# Project
#

project(Game VERSION 0.1)

#
# Configuration
#

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

# Enable debug symbols for release configuration
if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
endif()

# Enable folders in Visual Studio solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

#
# Targets
#

add_subdirectory(External)
add_subdirectory(Source)
