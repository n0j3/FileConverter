#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include "extension.h"
#include "inputHandler.h"
#include "part.h"
#include "stepReader.h"
#include "stepWriter.h"
#include "stlReader.h"
#include "stlWriter.h"


class Converter {
public:
    Converter();
    bool inputs();
    bool readFile();
    bool showFile();
    bool writeFile();

private:
    Extension defineExtension(const std::string &file);
    std::string joinPaths(const std::string& dir, const std::string& file);

    Part part;
    Extension inputType;
    Extension outputType;

    std::string inputDir;
    std::string inputFile;
    std::string outputDir;
    std::string outputFile;

    bool ap214;
    bool binary;
};

#endif // CONVERTER_H
