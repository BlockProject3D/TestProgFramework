cmake_minimum_required(VERSION 3.10)
project(TestProgFramework)

include("${CMAKE_SOURCE_DIR}/../FrameworkRemake/CMakes/Program.cmake")

configure_file(CMakeLists.in.txt googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if (result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif (result)
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if (result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif (result)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)
				 
include_directories("${gtest_SOURCE_DIR}/include")

set(SOURCES
    src/main.cpp
    src/String.cpp
    src/File.cpp
    src/MemoryMapper.cpp
    src/FileStream.cpp
    src/ByteBuf.cpp
    src/BinaryReadWrite.cpp
    src/MatrixDynamic.cpp
    src/MatrixStatic.cpp
    src/Quaternion.cpp
)

bp_setup()
target_link_libraries(${BP_NAME} PRIVATE debug gtest_main)
