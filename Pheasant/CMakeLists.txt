project(Pheasant CXX)

add_library(Pheasant SHARED
	src/*.cpp
	src/*.h
    src/core/*.cpp
    src/core/*.h
)

set(TARGET_ARCHITECTURE x64)

target_compile_definitions(Pheasant
    PUBLIC PHS_BUILD_EXPORT
)

target_compile_definitions(Pheasant PRIVATE
    $<$<CONFIG:Debug>:PHEASANT_DEBUG>
    $<$<CONFIG:Release>:PHEASANT_RELEASE>
    $<$<CONFIG:Dist>:PHEASANT_DIST>
)

add_custom_command(TARGET Pheasant POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Pheasant>
        ${CMAKE_BINARY_DIR}/bin/Testbed/$<CONFIG>/${TARGET_ARCHITECTURE}/
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_PROJECT_NAME}/$<CONFIG>/${TARGET_ARCHITECTURE}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_PROJECT_NAME}/$<CONFIG>/${TARGET_ARCHITECTURE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_PROJECT_NAME}/$<CONFIG>/${TARGET_ARCHITECTURE}/)
