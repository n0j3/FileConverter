#include "stlReader.h"
#include <fstream>
#include <iostream>

STL_Reader::STL_Reader() : corrupt(false) {}

bool STL_Reader::read(const std::string &filePath) {
    if (!isValidSTLFile(filePath)) {
        std::cerr << "Invalid STL file." << std::endl;
        corrupt = true;
        return false;
    }

    // Implementation to read the STL file and fill pointCloud
    corrupt = false; // Set this to true if corruption is detected
    return true;
}

bool STL_Reader::isCorrupt() const {
    return corrupt;
}

const std::vector<Point>& STL_Reader::getPointCloud() const {
    return pointCloud;
}

bool STL_Reader::isValidSTLFile(const std::string &filePath) {
    return filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".stl";
}
