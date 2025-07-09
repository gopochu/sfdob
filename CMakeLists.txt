cmake_minimum_required(VERSION 3.20)

project(sfdob LANGUAGES CXX)

set(CMAKE_CXX_STANDART 20)

include_directories(include external)

add_executable(${PROJECT_NAME}
    main.cpp

    external/stb_image_write.h
    external/stb_image.h
    
    include/image.hpp
    src/image.cpp
    include/image_io.hpp
    src/image_io.cpp

    include/preprocessor.hpp
    src/preprocessor.cpp
)