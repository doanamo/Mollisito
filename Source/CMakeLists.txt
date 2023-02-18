cmake_minimum_required(VERSION 3.25)

#
# Sources
#

set(SOURCE_FILES
    "Common/Compiler.hpp"
    "Common/NonCopyable.hpp"
    "Common/ScopeGuard.hpp"
    "Common/Logger.hpp"
    "Common/Logger.cpp"
    "Common/Common.hpp"
    "Main.cpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

#
# Configuration
#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#
# Target
#

add_executable(Game ${SOURCE_FILES})
target_include_directories(Game PRIVATE "Source")

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Game)

#
# External
#

# fmt
add_dependencies(Game External-fmt)
target_link_libraries(Game PRIVATE fmt)

# spdlog
add_dependencies(Game External-spdlog)
target_link_libraries(Game PRIVATE spdlog)

# SDL
add_dependencies(Game External-SDL)
target_link_libraries(Game PRIVATE SDL2main SDL2)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:Game>
)
