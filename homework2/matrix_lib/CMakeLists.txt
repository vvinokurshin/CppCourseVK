cmake_minimum_required(VERSION 3.0.0)
project(matrix_lib)

if (TEST_MODE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0 -Wall -Werror")
endif()

add_library(${PROJECT_NAME} matrix.cpp vector.cpp)

set(MATRIX_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(MATRIX_LIB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
