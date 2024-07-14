#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>
#include <cstring>
#include "stlWriter.h"

STL_Writer::STL_Writer() {}


// Public methods
bool STL_Writer::isCorrupt() const {
    return corrupt;
}


bool STL_Writer::writeSTL(const Part &part, const std::string &filePath, const bool &binary) {
    this->binary = binary;

    if (!isValidSTLFilePath(filePath)) {
        std::cerr << "Invalid STL file." << std::endl;
        corrupt = true;
        return false;
    }

    if (binary) {
        return writeBinarySTL(filePath, part);
    }
    
    else {
        return writeASCIISTL(filePath, part);
    }
}


// Private methods
bool STL_Writer::isValidSTLFilePath(const std::string &filePath) {
    return filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".stl";
}


bool STL_Writer::writeASCIISTL(const std::string &filePath, const Part &Part) {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open STL file for writing." << std::endl;
        corrupt = true;
        return false;
    }

    file << "solid ascii" << std::endl;
    for (size_t i = 0; Face face : Part.faces) {
        file << "  facet normal " << std::scientific << std::setprecision(6) << face.facet.x << " " << face.facet.y << " " << face.facet.z << std::endl;
        file << "    outer loop" << std::endl;
        file << "      vertex   " << face.vertices[0].x << " " << face.vertices[0].y << " " << face.vertices[0].z << std::endl;
        file << "      vertex   " << face.vertices[1].x << " " << face.vertices[1].y << " " << face.vertices[1].z << std::endl;
        file << "      vertex   " << face.vertices[2].x << " " << face.vertices[2].y << " " << face.vertices[2].z << std::endl;
        file << "    endloop" << std::endl;
        file << "  endfacet" << std::endl;
    }
    
    file << "endsolid" << std::endl;

    corrupt = false;
    return true;
}


bool STL_Writer::writeBinarySTL(const std::string &filePath, const Part &Part) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open STL file for writing." << std::endl;
        corrupt = true;
        return false;
    }

    char header[80] = {};
    file.write(header, 80);

    uint32_t numTriangles = Part.getFaces().size();
    file.write(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

    for (size_t i = 0; Face face : Part.faces) {
        file.write(reinterpret_cast<char*>(&face.facet), sizeof(Point));

        file.write(reinterpret_cast<const char*>(&face.vertices[1]), sizeof(Point));
        file.write(reinterpret_cast<const char*>(&face.vertices[2]), sizeof(Point));
        file.write(reinterpret_cast<const char*>(&face.vertices[3]), sizeof(Point));

        file.write(reinterpret_cast<char*>(&face.attribute), sizeof(u_int16_t));
    }
    
    corrupt = false;
    return true;
}