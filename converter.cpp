#include <filesystem>
#include <iostream>
#include "converter.h"

// Constructor
Converter::Converter() : binary(true) {}

// Public methods
bool Converter::inputs() {
    InputHandler input;
    // input.readFromTerminal(inputDir, inputFile, outputDir, outputFile, binary, ap214);
    input.simulateInput(inputDir, inputFile, outputDir, outputFile, binary, ap214);

    return true;
}


bool Converter::readFile() {
    inputType = defineExtension(inputFile);
    if (inputType == Extension::INVALID) {
        std::cerr << "Invalid input file extension!" << std::endl;
        return false;
    }

    std::string inputPath = inputDir + "/" + inputFile;   // joinPaths(inputDir, inputFile);

    if (inputType == Extension::STEP) {
        STEP_Reader stepReader;
        return stepReader.readSTEP(inputPath, part);
    }

    if (inputType == Extension::STL) {
        STL_Reader stlReader;
        return stlReader.readSTL(inputPath, part);
    } 

    return false;
}


bool Converter::showFile() {
    // Implement logic to show the part
    std::cout << "Displaying part..." << std::endl;
    // Example: part.display();
    return true;
}

bool Converter::writeFile() {
    outputType = defineExtension(outputFile);
    if (outputType == Extension::INVALID) {
        std::cerr << "Invalid output file extension!" << std::endl;
        return false;
    }

    std::string outputPath = outputDir + "//" + outputFile;  // joinPaths(outputDir, outputFile);

    if (outputType == Extension::STEP) {
        STEP_Writer stepWriter;
        return stepWriter.writeSTEP(part, outputPath, ap214);
    }

    else if (outputType == Extension::STL) {
        STL_Writer stlWriter;
        return stlWriter.writeSTL(part, outputPath, binary);
    }

    return false;
}

// Private methods
Extension Converter::defineExtension(const std::string &file) {
    std::string::size_type idx = file.rfind('.');
    if (idx != std::string::npos) {
        std::string extension = file.substr(idx + 1);
        
        if (extension == "step" || extension == "STEP") {
            return Extension::STEP;
        }

        else if (extension == "stp" || extension == "STP") {
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