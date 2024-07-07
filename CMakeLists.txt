cmake_minimum_required(VERSION 3.10)
project(FileConverter)

set(CMAKE_CXX_STANDARD 17)

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
