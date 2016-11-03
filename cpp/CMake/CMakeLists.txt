cmake_minimum_required(VERSION 2.8.0)

project(rand)

message(STATUS "C++XX support has been enabled by default.")

if (NOT WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
	set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
	ADD_DEFINITIONS(-O3 -Wall -g)
else()
	ADD_DEFINITIONS(-DNOMINMAX)
endif()

if (NOT WIN32)
	    find_package(ZLIB REQUIRED)
endif()
#find_package(LIBENCODING PATHS "../platform" REQUIRED)

# Use SSE
if (USE_SSE)
    add_definitions(-DUSE_SSE)
    message(STATUS "Use SSE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.1")
endif()

add_subdirectory("subA" "subA")

INCLUDE_DIRECTORIES("../")

FOREACH(A RANGE 5 15 3)
	message(${A})
ENDFOREACH(A)

set(FOLDERS foldera folderb folderc)# s times message
foreach (folder IN LISTS FOLDERS)
	# add cpp/h
	FILE(GLOB_RECURSE T "${PROJECT_SOURCE_DIR}/${folder}/*.cpp"
		"${PROJECT_SOURCE_DIR}/${folder}/*.h")
	LIST(APPEND CC_FILES ${T})
	message(${CC_FILES})
	# remove unittest cpp/h
	FILE(GLOB_RECURSE T "${PROJECT_SOURCE_DIR}/${folder}/*_unittest.cpp"
		"${PROJECT_SOURCE_DIR}/${folder}/*_unittest.h")
	if (T)
		LIST(REMOVE_ITEM CC_FILES ${T})
	endif()
endforeach(folder)

SET(SRC_LIST rand_test.cpp hello.h)#即SPC_LIST代表hello.h rand_test.cpp

#ADD_EXECUTABLE(可执行文件名 生成该可执行文件的源文件)
ADD_EXECUTABLE("${PROJECT_NAME}_test" ${SRC_LIST})
