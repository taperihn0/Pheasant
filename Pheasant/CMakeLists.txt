cmake_minimum_required(VERSION 3.16)

project(Pheasant CXX)

file(GLOB_RECURSE PHEASANT_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
file(GLOB_RECURSE PHEASANT_HEADERS CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(Pheasant SHARED 
	${PHEASANT_SOURCES}
	${PHEASANT_HEADERS}
)

target_compile_definitions(Pheasant PUBLIC 
	$<$<CONFIG:Debug>:PHEASANT_DEBUG>
	$<$<CONFIG:Release>:PHEASANT_RELEASE>
)

# Build it as a library
target_compile_definitions(Pheasant PUBLIC PHEASANT_BUILD_EXPORT)

# Platform detection
if (WIN32)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_PLATFORM_WINDOWS)
elseif (APPLE)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_PLATFORM_MACOS)
elseif (UNIX)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_PLATFORM_LINUX)
else ()
	message(FATAL_ERROR "Platform not recognised.")
endif ()

set_target_properties(Pheasant PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	LIBRARY_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/intermediates/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
)