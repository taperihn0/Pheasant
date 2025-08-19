cmake_minimum_required(VERSION 3.16)

project(Testbed CXX)

add_executable(Testbed
    src/testbed.cpp
)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

target_include_directories(Testbed PUBLIC
	${CMAKE_SOURCE_DIR}/Pheasant/src/
)

target_link_libraries(Testbed PRIVATE Pheasant)

# Just leave it for now
add_custom_command(TARGET Testbed POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    	${CMAKE_SOURCE_DIR}/bin/Pheasant/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}/*.so
        ${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}/
)

set_target_properties(Testbed PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	LIBRARY_OUTPUT_DIRECTORY
	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
	ARCHIVE_OUTPUT_DIRECTORY 
	"${CMAKE_SOURCE_DIR}/bin/intermediates/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}/${TARGET_ARCHITECTURE}"
)
