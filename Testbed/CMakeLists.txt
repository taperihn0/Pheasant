cmake_minimum_required(VERSION 3.16)

project(Testbed CXX)

add_executable(Testbed
    src/testbed.cpp
)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

target_link_libraries(Testbed PRIVATE Pheasant)

set_target_properties(Testbed PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	LIBRARY_OUTPUT_DIRECTORY
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	ARCHIVE_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/intermediates/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
)
