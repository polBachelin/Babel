cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_COLOR_MAKEFILE ON)
set(NAME Babel_Asio)

project(${NAME}
LANGUAGES CXX
VERSION 0.1
DESCRIPTION "Asio Server Lib")

include_directories(./)
include_directories(./DB)

set(SRCS
    AsioTcpServer.cpp
    AsioTcpConnection.cpp
    ContactManager.cpp
    UserManager.cpp
    ClientManager.cpp
    CommandsManager.cpp
    MessageManager.cpp
    DB/Database.cpp)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_library(${NAME} ${SRCS})

target_link_libraries(${NAME} ${CONAN_LIBS})
target_include_directories(${NAME} PUBLIC CONAN_INCLUDE_DIRS)

if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(WIN32)
        target_compile_options(${NAME} PRIVATE)
else()
        message(STATUS "NOT IN WINDOWS")
        target_compile_options(${NAME} PRIVATE)
endif()