#include "stepReader.h"
#include <fstream>
#include <iostream>

STEP_Reader::STEP_Reader() : corrupt(false) {}

bool STEP_Reader::read(const std::string &filePath) {
    if (!isValidSTEPFile(filePath)) {
        std::cerr << "Invalid STEP file." << std::endl;
        corrupt = true;
        return false;
    }

    // Implementation to read the STEP file and fill pointCloud
    corrupt = false; // Set this to true if corruption is detected
    return true;
}

bool STEP_Reader::isCorrupt() const {
    return corrupt;
}

const std::vector<Point>& STEP_Reader::getPointCloud() const {
    return pointCloud;
}

bool STEP_Reader::isValidSTEPFile(const std::string &filePath) {
    return filePath.size() >= 5 && (filePath.substr(filePath.size() - 5) == ".step" || filePath.substr(filePath.size() - 4) == ".stp");
}
