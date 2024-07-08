#include "stlReader.h"

// Public methods
STL_Reader::STL_Reader() : corrupt(false) {}


const std::vector<Point>& STL_Reader::getMesh() const {
    return mesh;
}


const std::vector<Point>& STL_Reader::getPointCloud() const {
    return pointCloud;
}


bool STL_Reader::read(const std::string &filePath) {
    if (!isValidSTLFilePath(filePath)) {
        std::cerr << "Invalid STL file." << std::endl;
        corrupt = true;
        return false;
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file." << std::endl;
        corrupt = true;
        return false;
    }

    pointCloud.clear(); // Clear the point cloud before reading new data
    mesh.clear();       // Clear the mesh data before reading new data

    if (isASCIISTL(file)) {
        if (!readASCIISTL(file)) {
            std::cerr << "Failed to read ASCII STL." << std::endl;
            corrupt = true;
            return false;
        }
    } else if (isBinarySTL(file)) {
        if (!readBinarySTL(file)) {
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


// Private methods
std::vector<Point> STL_Reader::getMeshFromASCIISTL(std::ifstream &file) {
    std::vector<Point> mesh;
    // Implement mesh extraction logic from ASCII STL if needed
    return mesh;
}


std::vector<Point> STL_Reader::getMeshFromBinarySTL(std::ifstream &file) {
    std::vector<Point> mesh;
    // Implement mesh extraction logic from binary STL if needed
    return mesh;
}


std::vector<Point> STL_Reader::getPointCloudFromASCIISTL(std::ifstream &file) {
    std::vector<Point> pc;
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("vertex") != std::string::npos) {
            std::istringstream iss(line);
            std::string keyword;
            float x, y, z;
            iss >> keyword >> x >> y >> z;
            pc.push_back({x, y, z});
        }
        // Process other ASCII STL data as needed
    }
    return pc;
}


std::vector<Point> STL_Reader::getPointCloudFromBinarySTL(std::ifstream &file) {
    std::vector<Point> pc;
    uint32_t numTriangles;
    file.seekg(80, std::ios::beg); // Skip the 80-byte header
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(numTriangles));

    for (uint32_t i = 0; i < numTriangles; ++i) {
        char buffer[50];
        file.read(buffer, 50);
        if (file.gcount() != 50) {
            // Handle error if necessary
            return pc; // Return empty vector on failure
        }
        // Process triangle data and extract points to pc vector
    }
    return pc;
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


bool STL_Reader::readASCIISTL(std::ifstream &file) {
    pointCloud = getPointCloudFromASCIISTL(file);
    mesh = getMeshFromASCIISTL(file);
    return true;
}

bool STL_Reader::readBinarySTL(std::ifstream &file) {
    pointCloud = getPointCloudFromBinarySTL(file);
    mesh = getMeshFromBinarySTL(file);
    return true;
}

