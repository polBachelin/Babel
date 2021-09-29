cmake_minimum_required(VERSION 3.17)

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(NAME babel)
set(NAME_CLIENT babel_client)

project(${NAME}
LANGUAGES CXX
VERSION 0.1
DESCRIPTION "The new skype"
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


#Client

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)
file(GLOB_RECURSE SRCS_CLIENT ${PROJECT_SOURCE_DIR}/client/src/*)
file(GLOB_RECURSE SRCS_SERVER ${PROJECT_SOURCE_DIR}/server/src/*)


#QT lib

#Include Client
add_executable(${NAME_CLIENT} ${SRCS_CLIENT})
include_directories(${CMAKE_INCLUDE_PATH})
target_include_directories(${NAME_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/client/include)
target_include_directories(${NAME_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/client/include/GUI/pages)
target_include_directories(${NAME_CLIENT} PUBLIC ${PROJECT_SOURCE_DIR}/client/include/GUI/)
target_link_libraries(${NAME_CLIENT} ${CONAN_LIBS} Qt5::Network Qt5::Widgets)

#Include Server
add_executable(${NAME} ${SRCS_SERV})
target_link_libraries(${NAME} PUBLIC ${CONAN_LIBS})
target_include_directories(${NAME} PUBLIC CONAN_INCLUDE_DIRS)
target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes)
target_include_directories(${NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes/server)


if (MVSVC)
        target_compile_options(${NAME_CLIENT} PRIVATE /W4 /WX)
        target_compile_options(${NAME} PRIVATE /W4 /WX)
else ()
        target_compile_options(${NAME_CLIENT} PRIVATE -Wall -Wextra -std=c++17)
        target_compile_options(${NAME} PRIVATE -Wall -Wextra -std=c++17)

endif()
