#include "stepReader.h"
#include <fstream>
#include <iostream>


// Constructor
STEP_Reader::STEP_Reader() : corrupt(true) {}


// Public methods
Part& STEP_Reader::getPart() {
    return part;
}


bool STEP_Reader::readSTEP(const std::string &filePath, Part part) {
    if (!isValidSTEPFile(filePath)) {
        std::cerr << "Invalid STEP file." << std::endl;
        corrupt = true;
        return false;
    }

    std::ifstream file(filePath, std::ios::binary);

    if (!file) {
        std::cerr << "Failed to open STEP file for reading." << std::endl;
        corrupt = true;
        return false;
    }

    part.clear();       // Clear the Part data before reading new data

    if (isAP203STEP(file)) {
        if (!readAP203STEP(file, part)) {
            std::cerr << "Failed to read AP203 STEP." << std::endl;
            corrupt = true;
            return false;
        }
    } else if (isAP214STEP(file)) {
        if (!readAP214STEP(file, part)) {
            std::cerr << "Failed to read AP214 STEP." << std::endl;
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


bool STEP_Reader::isCorrupt() const {
    return corrupt;
}


// Private methods
bool STEP_Reader::isAP203STEP(std::ifstream &file) {
    file.seekg(0, std::ios::beg); // Move to the beginning of the file
    std::string firstWord;
    file >> firstWord; // Read the first word
    file.clear(); // Clear any error state
    file.seekg(0, std::ios::beg); // Rewind to the beginning again
    return firstWord == "solid";
}


bool STEP_Reader::isAP214STEP(std::ifstream &file) {
    file.seekg(0, std::ios::beg); // Move to the beginning of the file
    std::string firstWord;
    file >> firstWord; // Read the first word
    file.clear(); // Clear any error state
    file.seekg(0, std::ios::beg); // Rewind to the beginning again
    return firstWord != "solid";
}


bool STEP_Reader::isValidSTEPFile(const std::string &filePath) {
    return filePath.size() >= 5 && (filePath.substr(filePath.size() - 5) == ".step" || filePath.substr(filePath.size() - 4) == ".stp");
}


bool STEP_Reader::readAP203STEP(std::ifstream &file, Part &part) {
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        corrupt = false;
        return false;
    }

    // TODO
    // Read data from .step

    corrupt = false;
    return true;
}

bool STEP_Reader::readAP214STEP(std::ifstream &file, Part &part) {
    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        corrupt = true;
        return false;
    }

    // TODO
    // Read data from .step

    corrupt = false;
    return true;
}
