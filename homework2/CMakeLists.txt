cmake_minimum_required(VERSION 3.0.0)
project(homework2)

OPTION(TEST "Run test" OFF)

add_subdirectory(matrix_lib)

add_executable(${PROJECT_NAME} main.cpp)

if (TEST_MODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MATRIX_LIB_LIBRARIES})

enable_testing()
add_subdirectory(tests)