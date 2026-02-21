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

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fms-extensions")
endif()

# Currently, only x64 architecture is supported
set(TARGET_ARCHITECTURE PHEASANT_ARCHITECTURE_64)

add_subdirectory(Pheasant)
add_subdirectory(Testbed)

target_compile_definitions(Pheasant PUBLIC ${TARGET_ARCHITECTURE})
target_compile_definitions(Testbed  PUBLIC ${TARGET_ARCHITECTURE})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Final" CACHE STRING "" FORCE)

# SIMD instruction set suppport
option(ENABLE_SIMD_SSE2   "Enable SSE2 optimizations"	  OFF)
option(ENABLE_SIMD_SSE3   "Enable SSE3 optimizations"	  OFF)
option(ENABLE_SIMD_SSSE3  "Enable SSSE3 optimizations"	  OFF)
option(ENABLE_SIMD_SSE4_1 "Enable SSE 4.1 optimizations"  OFF)
option(ENABLE_SIMD_SSE4_2 "Enable SSE 4.2 optimizations"  OFF)
option(ENABLE_SIMD_AVX    "Enable AVX optimizations"	  OFF)
option(ENABLE_SIMD_AVX2   "Enable AVX2 optimizations"     OFF)
option(ENABLE_SIMD_AVX512 "Enable AVX2 optimizations"     OFF)
option(FORCE_PURE         "Force 'pure' instructions"	  OFF)

if (FORCE_PURE)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_FORCE_PURE)
	target_compile_definitions(Testbed PUBLIC PHEASANT_FORCE_PURE)

	message(STATUS "SIMD instructions disabled")
elseif (ENABLE_SIMD_SSE2)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_SSE2)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_SSE2)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse2")
	endif()

	message(STATUS "SIMD instructions enabled - SSE2 instruction set")
elseif (ENABLE_SIMD_SSE3)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_SSE3)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_SSE3)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE3")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")
	endif()

	message(STATUS "SIMD instructions enabled - SSE3 instruction set")
elseif (ENABLE_SIMD_SSSE3)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_SSSE3)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_SSSE3)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSSE3")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3")
	endif()

	message(STATUS "SIMD instructions enabled - SSSE3 instruction set")
elseif (ENABLE_SIMD_SSE4_1)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_SSE4_1)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_SSE4_1)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE4.1")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
	endif()

	message(STATUS "SIMD instructions enabled - SSE4.1 instruction set")
elseif (ENABLE_SIMD_SSE4_2)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_SSE4_2)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_SSE4_2)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE4.2")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2")
	endif()

	message(STATUS "SIMD instructions enabled - SSE4.2 instruction set")
elseif (ENABLE_SIMD_AVX)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_AVX)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_AVX)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx")
	endif()

	message(STATUS "SIMD instructions enabled - AVX instruction set")
elseif (ENABLE_SIMD_AVX2)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_AVX2)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_AVX2)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX2")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx2")
	endif()

	message(STATUS "SIMD instructions enabled - AVX2 instruction set")
elseif (ENABLE_SIMD_AVX512)
	target_compile_definitions(Pheasant PUBLIC PHEASANT_SIMD_AVX512)
	target_compile_definitions(Testbed PUBLIC PHEASANT_SIMD_AVX512)

	if (MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX512")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx512")
	endif()

	message(STATUS "SIMD instructions enabled - AVX512 instruction set")
endif()
