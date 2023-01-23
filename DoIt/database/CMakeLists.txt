cmake_minimum_required(VERSION 3.0.0)
project(database)

if (TEST_MODE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_library(${PROJECT_NAME} PostgreDataBase.cpp UserDataBase.cpp BoardDataBase.cpp CardDataBase.cpp)
target_link_libraries(${PROJECT_NAME} ${PQXX_LIB} ${PQ_LIB})

set(DATABASE_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(DATABASE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
