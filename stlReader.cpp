#include "stlReader.h"

// Public methods
STL_Reader::STL_Reader() : corrupt(true) {}


Part& STL_Reader::getPart() {
    return part;
}


bool STL_Reader::readSTL(const std::string &filePath, Part &part) {
    if (!isValidSTLFilePath(filePath)) {
        std::cerr << "Invalid STL path ." << std::endl;
        corrupt = true;
        return false;
    }

    std::ifstream file(filePath, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open file." << std::endl;
        corrupt = true;
        return false;
    }

    part.clear();       // Clear the Part data before reading new data

    if (isASCIISTL(file)) {
        if (!readASCIISTL(file, part)) {
            std::cerr << "Failed to read ASCII STL." << std::endl;
            corrupt = true;
            return false;
        }
    } else if (isBinarySTL(file)) {
        if (!readBinarySTL(file, part)) {
            std::cerr << "Failed to read Binary STL." << std::endl;
            corrupt = true;
            return false;
        }
    } else {
        std::cerr << "Unknown STL file format." << std::endl;
        corrupt = true;
        return false;
    }

    corrupt = false;
    return true;
}


bool STL_Reader::isCorrupt() const {
    return corrupt;
}


bool STL_Reader::isASCIISTL(std::ifstream &file) {
    file.seekg(0, std::ios::beg); // Move to the beginning of the file
    std::string firstWord;
    file >> firstWord; // Read the first word
    file.clear(); // Clear any error state
    file.seekg(0, std::ios::beg); // Rewind to the beginning again
    return firstWord == "solid";
}


bool STL_Reader::isBinarySTL(std::ifstream &file) {
    file.seekg(0, std::ios::beg); // Move to the beginning of the file
    std::string firstWord;
    file >> firstWord; // Read the first word
    file.clear(); // Clear any error state
    file.seekg(0, std::ios::beg); // Rewind to the beginning again
    return firstWord != "solid";
}


bool STL_Reader::isValidSTLFilePath(const std::string &filePath) {
    return filePath.size() >= 4 && filePath.substr(filePath.size() - 4) == ".stl";
}


bool STL_Reader::readASCIISTL(std::ifstream &file, Part &part) {
    std::string line;
    Face face;
    int vertexCount = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string keyword;

        if (line.find("facet normal") != std::string::npos) {
            iss >> keyword >> keyword >> face.facet.x >> face.facet.y >> face.facet.z;
        } 
        else if (line.find("vertex") != std::string::npos) {
            iss >> keyword >> face.vertices[vertexCount].x >> face.vertices[vertexCount].y >> face.vertices[vertexCount].z;
            vertexCount++;
        } 
        else if (line.find("endfacet") != std::string::npos) {
            part.addFace(face);
            vertexCount = 0;
        } 
        else if (line.find("endsolid") != std::string::npos) {
            break;
        }
    }

    return true;
}


bool STL_Reader::readBinarySTL(std::ifstream &file, Part &part) {
    uint32_t numTriangles;
    file.seekg(80, std::ios::beg); // Skip the 80-byte header
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

    for (uint32_t i = 0; i < numTriangles; ++i) {
        char buffer[50];
        file.read(buffer, 50);
        if (file.gcount() != 50) {
            // Handle error if necessary
            return false; // Return false on failure
        }

        Face face;
        // Reading normal vector
        memcpy(&face.facet.x, &buffer[0], sizeof(float));
        memcpy(&face.facet.y, &buffer[4], sizeof(float));
        memcpy(&face.facet.z, &buffer[8], sizeof(float));

        // Reading vertices
        for (int j = 0; j < 3; ++j) {
            memcpy(&face.vertices[j].x, &buffer[12 + j * 12], sizeof(float));
            memcpy(&face.vertices[j].y, &buffer[16 + j * 12], sizeof(float));
            memcpy(&face.vertices[j].z, &buffer[20 + j * 12], sizeof(float));
        }

        // Reading attribute byte count
        memcpy(&face.attribute, &buffer[48], sizeof(uint16_t));

        part.addFace(face);
    }
    return true;
}


