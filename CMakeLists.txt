cmake_minimum_required(VERSION 3.16)

project(PheasantSolution CXX)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug
		CACHE STRING "Choose one of build types: Debug, Release."
		FORCE)
	message(STATUS "CMAKE_BUILD_TYPE not specified. Defaulting to Debug.")
else ()
	message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif ()

message(${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Final" CACHE STRING "" FORCE)

# Currently, only x64 architecture is supported
set(TARGET_ARCHITECTURE x64)

add_subdirectory(Pheasant)
add_subdirectory(Testbed)

target_compile_definitions(Pheasant PUBLIC ARCHITECTURE_64)
target_compile_definitions(Testbed  PUBLIC ARCHITECTURE_64)

