#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include "stepConverter.h"
#include "stepReader.h"
#include "stepWriter.h"
#include "stlConverter.h"
#include "stlReader.h"
#include "stlWriter.h"

class Converter {
public:
    Converter();
    bool convert(const std::string &inputPath, const std::string &outputPath, const bool &binary = true);

private:
    bool hasValidExtension(const std::string &filePath, const std::string &extension) const;
};

#endif // CONVERTER_H
