cmake_minimum_required(VERSION 3.16)

project(Pheasant CXX)

file(GLOB_RECURSE PHEASANT_SOURCES CONFIGURE_DEPENDS
	"*.h"
)
file(GLOB_RECURSE PHEASANT_HEADERS CONFIGURE_DEPENDS
	"*.cpp"
)

add_library(Pheasant SHARED 
	${PHEASANT_SOURCES}
	${PHEASANT_HEADERS}
)

add_subdirectory(vendor/glfw)

target_link_libraries(Pheasant PUBLIC glfw)

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

target_include_directories(Pheasant PUBLIC
	${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src/
	${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src/core
	${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/vendor/GLAD/include/
)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

set_target_properties(Pheasant PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	LIBRARY_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/intermediates/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
)

# Copy library file into executable directory
add_custom_command(TARGET Pheasant POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    	${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}/${PROJECT_NAME}.dll
        ${CMAKE_SOURCE_DIR}/bin/Testbed/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}/
)

