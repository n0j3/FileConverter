#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include "stepReader.h"
#include "stepWriter.h"
#include "stlReader.h"
#include "stlWriter.h"
#include "extension.h"

class Converter {
public:
    Converter();
    bool convert();
    bool validateInputs(const std::string &inputFile, const std::string &outputFile, const std::string &inputDir, const std::string &outputDir, bool binary = true);

private:
    Extension hasValidExtension(const std::string &file);
    bool mergePath(std::string &file, const std::string &dir, bool input);

    std::string input;
    std::string output;
    Extension inputType;
    Extension outputType;
    bool binary;
};

#endif // CONVERTER_H
