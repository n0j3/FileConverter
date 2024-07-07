#include "stlWriter.h"
#include <fstream>
#include <iostream>

STL_Writer::STL_Writer() : corrupt(false) {}

bool STL_Writer::write(const Mesh &mesh, const std::string &filePath) {
    if (!isValidSTLFile(filePath)) {
        std::cerr << "Invalid STL file." << std::endl;
        corrupt = true;
        return false;
    }

    // Implementation to write the mesh to an STL file
    corrupt = false; // Set this to true if corruption occurs
    return true;
}

bool STL_Writer::isCorrupt() const {
    return corrupt;
}

bool STL_Writer::isValidSTLFile(const std::string &filePath) {
    return filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".stl";
}
