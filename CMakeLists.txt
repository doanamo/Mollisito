cmake_minimum_required(VERSION 3.25)

#
# Project
#

project(Game VERSION 0.1)

#
# Configuration
#

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

#
# Targets
#

add_subdirectory(External)
add_subdirectory(Source)
