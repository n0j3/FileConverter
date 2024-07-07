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

    Converter converter;
    if (!converter.convert(inputPath, outputPath)) {
        return 1;
    }

    return 0;
}
