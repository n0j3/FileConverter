#include <iostream>
#include "inputHandler.h"

// Public methods
InputHandler::InputHandler() {}

bool InputHandler::readFromTerminal(std::string &inputDir, std::string &inputFile, 
                                    std::string &outputDir, std::string &outputFile, bool &binary, bool &ap214) {
    std::cout << "Provide input file: ";
    std::cin >> inputFile;
    processInput(inputDir, inputFile);

    if (inputDir.empty()) {
        std::cout << "Provide input directory: ";
        std::cin >> inputDir;
    }

    char specifyOutput;
    std::cout << "Want to specify output? (Y/N): ";
    std::cin >> specifyOutput;

    if (specifyOutput == 'Y' || specifyOutput == 'y') {
        std::cout << "Provide output file: ";
        std::cin >> outputFile;
        processInput(outputDir, outputFile);

        if (outputDir.empty()) {
            std::cout << "Provide output directory: ";
            std::cin >> outputDir;
        }
    } else {
        outputDir = inputDir;
        outputFile = "output_" + inputFile;
    }

    std::cout << "Want to save STEP as AP203 or AP214 (recommended binary): ";
    std::string format;
    std::cin >> format;
    if (format == "ap203" || format == "AP203" || format == "203" || format == "03") {
        ap214 = false;
    } else {
        ap214 = true;
    }

    std::cout << "Want to save STL as ASCII or binary (recommended binary): ";
    std::cin >> format;
    if (format == "ascii" || format == "ASCII" || format == "a" || format == "A") {
        binary = false;
    } else {
        binary = true;
    }

    return true; // Assuming the function completes successfully
}


bool InputHandler::simulateInput(std::string &inputDir, std::string &inputFile, 
                                 std::string &outputDir, std::string &outputFile, bool &binary, bool &ap214) {
    inputDir = "/home/n0j3/OneDrive/Dokumente/03_Projekte/FileConverter";
    inputFile = "stlASCII.stl";
    outputDir = "/home/n0j3/OneDrive/Dokumente/03_Projekte/FileConverter";
    outputFile = "output_stlASCII.stl";
    binary = true;
    ap214 = true;

    printPaths(inputDir, inputFile, outputDir, outputFile, binary, ap214);

    return true;
}


// Private methods
bool InputHandler::printPaths(std::string& inputDir, std::string& inputFile, 
                              std::string& outputDir, std::string& outputFile, bool binary, bool ap214) {
    std::cout << "Input Directory:     " << inputDir << "\n";
    std::cout << "Input File:          " << inputFile << "\n";
    std::cout << "Output Directory:    " << outputDir << "\n";
    std::cout << "Output File:         " << outputFile << "\n";
    std::cout << "Output as Binary:    " << std::boolalpha << binary << "\n";
    std::cout << "Output as AP214:     " << std::boolalpha << ap214 << "\n";
    return true; // Assuming printing always succeeds
}


bool InputHandler::processInput(std::string& dir, std::string& file) {
    size_t pos = file.find_last_of("/\\");
    if (pos != std::string::npos) {
        dir = file.substr(0, pos);
        file = file.substr(pos + 1);
    }
    return true; // Assuming processing always succeeds
}
