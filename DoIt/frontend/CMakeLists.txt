cmake_minimum_required(VERSION 3.14)
project(frontend)

# variables
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# options
option(BUILD_TESTS "Build the unit tests" ON)
option(USE_SANITIZER_FLAGS "Use sanitizer flags" ON)
option(USE_COVERAGE_FLAGS "Use coverage flags" ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Boost COMPONENTS system thread REQUIRED)

set(INCS
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui
        ${CMAKE_CURRENT_SOURCE_DIR}/Managers
        ${CMAKE_CURRENT_SOURCE_DIR}/Data
        ${CMAKE_CURRENT_SOURCE_DIR}/Lib
        )

include_directories(${INCS})

set(SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Managers/main_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Managers/gui_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Managers/net_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Managers/user_manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/mainwindow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/reg_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/auth_window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/board_widget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/column_widget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/card_widget.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/comment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/update.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/menu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/navbar.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/gui_user.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Gui/boardwidgetmanager.cpp
        )

# setup
if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g0 -DNDEBUG")
    set(USE_SANITIZER_FLAGS OFF)
    set(USE_COVERAGE_FLAGS OFF)
endif ()

if (USE_SANITIZER_FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
endif ()

add_executable(${PROJECT_NAME} ${SRCS})

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        ${Boost_LIBRARIES}
        )

# tests
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(Test)
endif ()
