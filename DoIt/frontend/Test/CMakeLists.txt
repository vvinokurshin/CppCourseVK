cmake_minimum_required(VERSION 3.14)
project(unit_test)

enable_testing()

# variables
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (USE_SANITIZER_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif ()

if (USE_COVERAGE_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")
endif ()

find_package(GTest REQUIRED)
find_package(Boost COMPONENTS system thread REQUIRED)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
        test_net_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Managers/net_manager.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../Managers
        ${CMAKE_CURRENT_SOURCE_DIR}/../Lib
        )

target_link_libraries(${PROJECT_NAME}
        GTest::gtest_main
        ${Boost_LIBRARIES}
        Qt${QT_VERSION_MAJOR}::Widgets
        )

gtest_discover_tests(${PROJECT_NAME})
