#include <iostream>
#include <string>
#include "converter.h"

int main() {
    std::string inputDir;
    std::string outputDir;
    std::string inputFile;
    std::string outputFile;

    std::cout << "Provide input directory: ";
    std::cin >> inputDir;

    std::cout << "Provide input file: ";
    std::cin >> inputFile;

    std::cout << "Provide output directory: ";
    std::cin >> outputDir;

    std::cout << "Provide output file: ";
    std::cin >> outputFile;

    const bool binary = true;

    Converter converter;
    if (!converter.validateInputs(inputFile, outputFile, inputDir, outputDir, binary)) {
        return 1;
    }

    if (!converter.convert()) {
        return 2;
    }

    return 0;
}
