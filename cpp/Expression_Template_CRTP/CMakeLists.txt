cmake_minimum_required(VERSION 3.2.0)


find_program(ccache "/usr/bin/ccache")
if(ccache)
	SET(CMAKE_C_COMPILER "/usr/bin/ccache")
	SET(CMAKE_C_COMPILER_ARG1 "gcc")
	SET(CMAKE_CXX_COMPILER  "/usr/bin/ccache")
	SET(CMAKE_CXX_COMPILER_ARG1 "g++")
endif()

project(op_crtp)

message("${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++11 support has been enabled by default.")

option(build_Library "build Library" ON)

if (NOT WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -lm")
	set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -lm")
else()
	ADD_DEFINITIONS(-DNOMINMAX)
	foreach (warning 4996 4018 4244 4267 4506 4800)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd${warning}")
	endforeach(warning)
	#https://msdn.microsoft.com/en-us/library/mt708818.aspx
	# If you want to set both the source character set and the execution character set to UTF-8,
	# you can use the /utf-8 compiler option as a shortcut. It is equivalent to specifying 
	# /source-charset:utf-8 /execution-charset:utf-8 on the command line.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /utf-8")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#add_subdirectory("../other" "other")# third party

include_directories(
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/include/"
	"${PROJECT_SOURCE_DIR}/test/"
)


# exp_template.cpp Expression template example
add_executable(expression_template expression_guide/exp_template.cpp)
add_executable(naive_overloading expression_guide/naive_overloading.cpp)

#test
FILE(GLOB_RECURSE INCLUDE_FILES "${PROJECT_SOURCE_DIR}/include/*.hpp" )
message("start build test. inlcude file:\n${INCLUDE_FILES}")
FILE(GLOB_RECURSE TEST_FILES "${PROJECT_SOURCE_DIR}/test/*.cpp")

message("test cpp:${TEST_FILES}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/)
foreach (testfile ${TEST_FILES})
	message("${testfile}")
	if(NOT ${testfile} MATCHES "test.*\.cpp") # begin with test
		continue()
	endif()
	# app name
	# remove path,otherwise Error:
	#The target name "XX" is reserved or not valid for certain CMake features
	STRING( REGEX REPLACE "/.*/" "" testexe ${testfile} )
	STRING( REPLACE ".cpp" "" testexe ${testexe} )
	message("test file:${testfile}")
	message("test exe:${testexe}")
	#continue()
	add_executable("${testexe}" ${testfile} ${INCLUDE_FILES})
endforeach(testfile ${TEST_FILES})

