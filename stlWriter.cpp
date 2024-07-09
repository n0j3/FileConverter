#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstring>
#include "stlWriter.h"

STL_Writer::STL_Writer() {}


// Public methods
bool STL_Writer::isCorrupt() const {
    return corrupt;
}


bool STL_Writer::writeSTL(const Mesh &mesh, const std::string &filePath, const bool &binary) {
    this->binary = binary;

    if (!isValidSTLFilePath(filePath)) {
        std::cerr << "Invalid STL file." << std::endl;
        corrupt = true;
        return false;
    }

    if (this->binary) {
        return writeBinarySTL(filePath, mesh);
    }
    
    else {
        return writeASCIISTL(filePath, mesh);
    }
}


// Private methods
bool STL_Writer::isValidSTLFilePath(const std::string &filePath) {
    return filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".stl";
}


bool STL_Writer::writeASCIISTL(const std::string &filePath, const Mesh &mesh) {
    std::ofstream file(filePath);
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        corrupt = false;
        return false;
    }

    file << "solid ascii_stl" << std::endl;
    for (size_t i = 0; Face face : mesh.faces) {
        file << "  facet normal " << face.facet.x << " " << face.facet.y << " " << face.facet.z << std::endl;
        file << "    outer loop" << std::endl;
        file << "      vertex " << face.vertices[1].x << " " << face.vertices[1].y << " " << face.vertices[1].z << std::endl;
        file << "      vertex " << face.vertices[2].x << " " << face.vertices[2].y << " " << face.vertices[2].z << std::endl;
        file << "      vertex " << face.vertices[3].x << " " << face.vertices[3].y << " " << face.vertices[3].z << std::endl;
        file << "    endloop" << std::endl;
        file << "  endfacet" << std::endl;
    }
    file << "endsolid ascii_stl" << std::endl;

    corrupt = false;
    return true;
}


bool STL_Writer::writeBinarySTL(const std::string &filePath, const Mesh &mesh) {
    std::ofstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        corrupt = false;
        return false;
    }

    char header[80] = {};
    file.write(header, 80);

    uint32_t numTriangles = mesh.getFaces().size();
    file.write(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

    for (size_t i = 0; Face face : mesh.faces) {
        float nx = face.facet.x, ny = face.facet.y, nz = face.facet.z; // Normal vector
        file.write(reinterpret_cast<char*>(&nx), sizeof(float));
        file.write(reinterpret_cast<char*>(&ny), sizeof(float));
        file.write(reinterpret_cast<char*>(&nz), sizeof(float));

        file.write(reinterpret_cast<const char*>(&face.vertices[1]), sizeof(Point));
        file.write(reinterpret_cast<const char*>(&face.vertices[2]), sizeof(Point));
        file.write(reinterpret_cast<const char*>(&face.vertices[3]), sizeof(Point));

        uint16_t attributeByteCount = 0;
        file.write(reinterpret_cast<char*>(&attributeByteCount), sizeof(attributeByteCount));
    }
    
    corrupt = false;
    return true;
}