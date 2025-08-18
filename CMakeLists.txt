cmake_minimum_required(VERSION 3.16)

project(PheasantSolution CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Final" CACHE STRING "" FORCE)

#set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
#    $<$<CONFIG:Debug>:CONFIGURATION_DEBUG>
#    $<$<CONFIG:Release>:CONFIGURATION_RELEASE>
#    $<$<CONFIG:Final>:CONFIGURATION_FINAL>
#)

add_subdirectory(Pheasant)
add_subdirectory(Testbed)