cmake_minimum_required(VERSION 3.0.0)
project(homework5)

OPTION(TEST "Run test" OFF)

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

if (TEST_MODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -Wall -Werror -Wpedantic -include set_lib/set.hpp" )
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${SET_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SET_LIB_LIBRARIES})

enable_testing()
add_subdirectory(tests)
