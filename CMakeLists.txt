cmake_minimum_required(VERSION 3.17)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(NAME Babel)
set(NAME_CLI Babel_cli)

project(${NAME}
LANGUAGES CXX
VERSION 0.1
DESCRIPTION "The new skype"
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(SRCS_SERV
    src/server/main.cpp
    src/server/TcpConnection.cpp
    src/server/TcpServer.cpp
    src/server/Commands.cpp)

set(SRCS_CLI
    src/client/main.cpp)

add_executable(${NAME} ${SRCS_SERV})
target_link_libraries(${NAME} PUBLIC ${CONAN_LIBS})
target_include_directories(${NAME} PUBLIC CONAN_INCLUDE_DIRS)
target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes)
target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes/server)

add_executable(${NAME_CLI} ${SRCS_CLI})
target_link_libraries(${NAME_CLI} PUBLIC ${CONAN_LIBS})
target_include_directories(${NAME_CLI} PUBLIC CONAN_INCLUDE_DIRS)
target_include_directories(${NAME_CLI} PUBLIC ${PROJECT_SOURCE_DIR}/includes)
target_include_directories(${NAME_CLI} PUBLIC ${PROJECT_SOURCE_DIR}/includes/server)

# if (MVSVC)
#         target_compile_options(${NAME} PRIVATE /W4 /WX)
# else ()
#         target_compile_options(${NAME} PRIVATE -Wall -Wextra -std=c++11)
# endif()
