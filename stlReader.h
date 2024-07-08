#ifndef STL_READER_H
#define STL_READER_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstring>
#include "mesh.h"

class STL_Reader {
public:
    STL_Reader();

    bool read(const std::string &filePath);
    bool isCorrupt() const;
    
    const std::vector<Point>& getPointCloud() const;
    const std::vector<Point>& getMesh() const;

private:
    bool readBinarySTL(std::ifstream &file);
    bool readASCIISTL(std::ifstream &file);
    bool isValidSTLFilePath(const std::string &filePath);
    bool isASCIISTL(std::ifstream &file);
    bool isBinarySTL(std::ifstream &file);

    std::vector<Point> getPointCloudFromASCIISTL(std::ifstream &file);
    std::vector<Point> getMeshFromASCIISTL(std::ifstream &file);
    std::vector<Point> getPointCloudFromBinarySTL(std::ifstream &file);
    std::vector<Point> getMeshFromBinarySTL(std::ifstream &file);

    std::vector<Point> pointCloud;
    std::vector<Point> mesh;

    bool corrupt;
};

#endif // STL_READER_H
