project(Testbed CXX)

add_executable(Testbed
    src/*.cpp
	src/*.h
)

set(TARGET_ARCHITECTURE x64)

target_include_directories(Testbed
    PUBLIC
		${CMAKE_SOURCE_DIR}/Pheasant/src/
)

target_link_libraries(Testbed PRIVATE Pheasant)

target_compile_definitions(Testbed PRIVATE
    $<$<CONFIG:Debug>:PHEASANT_DEBUG>
    $<$<CONFIG:Release>:PHEASANT_RELEASE>
    $<$<CONFIG:Dist>:PHEASANT_DIST>
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_PROJECT_NAME}/$<CONFIG>/${TARGET_ARCHITECTURE}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_PROJECT_NAME}/$<CONFIG>/${TARGET_ARCHITECTURE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_PROJECT_NAME}/$<CONFIG>/${TARGET_ARCHITECTURE}/)
