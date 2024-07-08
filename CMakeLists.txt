cmake_minimum_required(VERSION 3.10)
project(FileConverter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add the executable and include all necessary source files
add_executable(FileConverter 
    main.cpp 
    converter.cpp 
    stepConverter.cpp 
    stepReader.cpp 
    stepWriter.cpp 
    stlConverter.cpp 
    stlReader.cpp 
    stlWriter.cpp
)
