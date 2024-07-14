#include "stepWriter.h"
#include <fstream>
#include <iostream>

STEP_Writer::STEP_Writer() : corrupt(false) {}

bool STEP_Writer::writeSTEP(const Part &part, const std::string &filePath, bool &stepType) {
    if (!isValidSTEPFile(filePath)) {
        std::cerr << "Invalid STEP file." << std::endl;
        corrupt = true;
        return false;
    }

    // Implementation to write the Part to a STEP file
    corrupt = false; // Set this to true if corruption occurs
    return true;
}

bool STEP_Writer::isCorrupt() const {
    return corrupt;
}

bool STEP_Writer::isValidSTEPFile(const std::string &filePath) {
    return filePath.size() >= 5 && (filePath.substr(filePath.size() - 5) == ".step" || filePath.substr(filePath.size() - 4) == ".stp");
}
