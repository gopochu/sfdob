cmake_minimum_required(VERSION 3.20)

project(sfdob LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/core 
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/steps
    # ${CMAKE_CURRENT_SOURCE_DIR}/src
# )

# include_directories(external src src/utils src/core src/steps include)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/steps
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*/*.cpp")

# add_definitions(-DCOLOR_MODE=1)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_definitions(${PROJECT_NAME} PRIVATE COLOR_MODE=1)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)