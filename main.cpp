#include <iostream>
#include <string>
#include "converter.h"

int main() {
    std::string inputPath;
    std::string outputPath;

    std::cout << "Provide input path: ";
    std::cin >> inputPath;

    std::cout << "Provide output path: ";
    std::cin >> outputPath;

    const bool binary = true;

    Converter converter;
    if (!converter.convert(inputPath, outputPath, binary)) {
        return 1;
    }

    return 0;
}
