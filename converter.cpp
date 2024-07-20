#include <filesystem>
#include <iostream>
#include "converter.h"

// Constructor
Converter::Converter() : binary(true), ap214(true) {}

// Public methods
bool Converter::inputs() {
    InputHandler input;
    // input.readFromTerminal(inputDir, inputFile, outputDir, outputFile, binary, ap214);
    input.simulateInput(inputDir, inputFile, outputDir, outputFile, binary, ap214);

    return true;
}


bool Converter::readFile() {
    std::string inputPath = joinPaths(inputDir, inputFile);
    bool success = false;

    switch (defineExtension(inputFile)) {
    case Extension::INVALID:
        std::cerr << "Invalid input file extension: " << inputFile << std::endl;
        success = false;
        break;

    case Extension::STEP: {
        STEP_Reader stepReader;
        success = stepReader.readSTEP(inputPath, part);
        break;
    }

    case Extension::STL: {
        STL_Reader stlReader;
        success = stlReader.readSTL(inputPath, part);
        break;
    }

    default:
        std::cerr << "Unsupported input file extension: " << inputFile << std::endl;
        success = false;
        break;
    }

    return success;
}


bool Converter::showFile() {
    
    std::cout << "Displaying part..." << std::endl;

    return true;
}


bool Converter::writeFile() {
    std::string outputPath = joinPaths(outputDir, outputFile);
    bool success = false;

    switch (defineExtension(outputFile)) {
    case Extension::INVALID:
        std::cerr << "Invalid output file extension: " << outputFile << std::endl;
        success = false;
        break;

    case Extension::STEP: {
        STEP_Writer stepWriter;
        success = stepWriter.writeSTEP(part, outputPath, ap214);
        break;
    }

    case Extension::STL: {
        STL_Writer stlWriter;
        success = stlWriter.writeSTL(part, outputPath, binary);
        break;
    }

    default:
        std::cerr << "Unsupported output file extension: " << outputFile << std::endl;
        success = false;
        break;
    }

    return success;
}

// Private methods
Extension Converter::defineExtension(const std::string &file) {
    std::string::size_type idx = file.rfind('.');
    if (idx != std::string::npos) {
        std::string extension = file.substr(idx + 1);

        if (extension == "step" || extension == "STEP" || extension == "stp" || extension == "STP") {
            return Extension::STEP;
        }
        
        else if (extension == "stl" || extension == "STL") {
            return Extension::STL;
        }
    }

    return Extension::INVALID;
}

std::string Converter::joinPaths(const std::string& dir, const std::string& file) {
    std::filesystem::path dirPath(dir);
    std::filesystem::path filename(file);
    std::filesystem::path filePath = dirPath / filename;

    return filePath.string();
}
