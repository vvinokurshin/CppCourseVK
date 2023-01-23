cmake_minimum_required(VERSION 3.14)
project(DoIt)

OPTION(TEST "Run test" OFF)
add_subdirectory(database)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost COMPONENTS system thread REQUIRED)

add_executable(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/server_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/database_interaction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/backend/database_connector.cpp
    )

if (TEST_MODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif()

if (MEM_MODE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined -g -OX")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC 
${DATABASE_INCLUDE_DIRS}
${Boost_INCLUDE_DIRS}
${CMAKE_CURRENT_SOURCE_DIR}/backend
${CMAKE_CURRENT_SOURCE_DIR}/database
)
target_link_libraries(${PROJECT_NAME} PRIVATE 
${DATABASE_LIBRARIES}
${Boost_LIBRARIES}
)

# tests
enable_testing()
add_subdirectory(tests)
