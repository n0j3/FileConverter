#include "converter.h"
#include <iostream>

Converter::Converter() {}

bool Converter::hasValidExtension(const std::string &filePath, const std::string &extension) const {
    return filePath.size() >= extension.size() &&
           filePath.substr(filePath.size() - extension.size()) == extension;
}

bool Converter::convert(const std::string &inputPath, const std::string &outputPath) {
    if (hasValidExtension(inputPath, ".stl") && hasValidExtension(outputPath, ".step")) {
        STL_Reader stlReader;
        if (!stlReader.read(inputPath) || stlReader.isCorrupt()) {
            std::cerr << "Failed to read STL file or the file is corrupt." << std::endl;
            return false;
        }

        STL_Converter stlConverter;
        Mesh mesh = stlConverter.convertToMesh(stlReader.getPointCloud());

        STEP_Writer stepWriter;
        if (!stepWriter.write(mesh, outputPath) || stepWriter.isCorrupt()) {
            std::cerr << "Failed to write STEP file or the file is corrupt." << std::endl;
            return false;
        }

        std::cout << "STL to STEP conversion successful!" << std::endl;
    } else if (hasValidExtension(inputPath, ".step") && hasValidExtension(outputPath, ".stl")) {
        STEP_Reader stepReader;
        if (!stepReader.read(inputPath) || stepReader.isCorrupt()) {
            std::cerr << "Failed to read STEP file or the file is corrupt." << std::endl;
            return false;
        }

        STEP_Converter stepConverter;
        Mesh mesh = stepConverter.convertToMesh(stepReader.getPointCloud());

        STL_Writer stlWriter;
        if (!stlWriter.write(mesh, outputPath) || stlWriter.isCorrupt()) {
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
