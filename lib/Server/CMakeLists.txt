cmake_minimum_required(VERSION 3.17)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_COLOR_MAKEFILE ON)
set(NAME Babel_Asio)

project(${NAME}
LANGUAGES CXX
VERSION 0.1
DESCRIPTION "Asio Server Lib"
)

include_directories(./)

set(SRCS
    AsioTcpConnection.cpp
    AsioTcpServer.cpp
    Commands.cpp)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_library(${NAME} SHARED ${SRCS})

target_link_libraries(${NAME} ${CONAN_LIBS})
target_include_directories(${NAME} PUBLIC CONAN_INCLUDE_DIRS)

if (MVSVC)
    target_compile_options(${NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${NAME} PRIVATE -fPIC -Wall -Wextra -std=c++17)
endif()