#ifndef STL_READER_H
#define STL_READER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstring>
#include "part.h"

class STL_Reader {
public:
    STL_Reader();

    Part& getPart();

    bool isCorrupt() const;
    bool readSTL(const std::string &filePath, Part &part);

private:
    bool isASCIISTL(std::ifstream &file);
    bool isBinarySTL(std::ifstream &file);
    bool isValidSTLFilePath(const std::string &filePath);
    bool readBinarySTL(std::ifstream &file, Part &part);
    bool readASCIISTL(std::ifstream &file, Part &part);

    Part part;

    bool corrupt;
};

#endif // STL_READER_H
