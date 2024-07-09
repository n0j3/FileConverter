#include "converter.h"
#include <iostream>

Converter::Converter() {}

// Public methods
bool Converter::convert() {
    if (hasValidExtension(input) == Extension::STL && hasValidExtension(output) == Extension::STEP) {
        STL_Reader stlReader;
        if (!stlReader.read(input) || stlReader.isCorrupt()) {
            std::cerr << "Failed to read STL file or the file is corrupt." << std::endl;
            return false;
        }

        STEP_Writer stepWriter;
        if (!stepWriter.writeSTEP(stlReader.getMesh(), output) || stepWriter.isCorrupt()) {
            std::cerr << "Failed to write STEP file or the file is corrupt." << std::endl;
            return false;
        }

        std::cout << "STL to STEP conversion successful!" << std::endl;
    } else if (hasValidExtension(input) == Extension::STEP && hasValidExtension(output) == Extension::STL) {
        STEP_Reader stepReader;
        if (!stepReader.read(input) || stepReader.isCorrupt()) {
            std::cerr << "Failed to read STEP file or the file is corrupt." << std::endl;
            return false;
        }

        STL_Writer stlWriter;
        if (!stlWriter.writeSTL(stepReader.getMesh(), output, binary) || stlWriter.isCorrupt()) {
            std::cerr << "Failed to write STL file or the file is corrupt." << std::endl;
            return false;
        }

        std::cout << "STEP to STL conversion successful!" << std::endl;
    } else {
        std::cerr << "Invalid file extensions. Provide .stl to .step or .step to .stl conversion paths." << std::endl;
        return false;
    }

    return true;
}

bool Converter::validateInputs(const std::string &inputFile, const std::string &outputFile, const std::string &inputDir, const std::string &outputDir, bool binary) {
    this->binary = binary;

    if (!mergePath(input, inputDir, true)) {
        std::cerr << "Unable to validate input path." << std::endl;
        return false;
    }

    if (!mergePath(output, outputDir, false)) {
        std::cerr << "Unable to validate output path." << std::endl;
        return false;
    }

    return true;
}

// Private methods
Extension Converter::hasValidExtension(const std::string &file) {
    for (const auto& [extension, extensionStr] : extensionToStringMap) {
        if (file.size() >= extensionStr.size() &&
            file.compare(file.size() - extensionStr.size(), extensionStr.size(), extensionStr) == 0) {
            return extension;
        }
    }
    return Extension::INVALID; // Default return value for unsupported extension, adjust as needed
}

bool Converter::mergePath(std::string &file, const std::string &dir, bool input) {
    Extension ext = hasValidExtension(file);
    if (ext == Extension::INVALID) {

        return false;
    }

    if (input) {
        this->inputType = ext;
        this->input = dir + "/" + file;
    } else {
        this->outputType = ext;
        this->output = dir + "/" + file;
    }

    return true;
}
