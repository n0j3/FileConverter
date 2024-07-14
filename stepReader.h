#ifndef STEP_READER_H
#define STEP_READER_H

#include <string>
#include <vector>
#include "part.h"

class STEP_Reader {
public:
    STEP_Reader();

    Part& getPart();

    bool isCorrupt() const;
    bool readSTEP(const std::string &filePath, Part part);

private:
    bool isAP203STEP(std::ifstream &file);
    bool isAP214STEP(std::ifstream &file);
    bool isValidSTEPFile(const std::string &filePath);
    bool readAP203STEP(std::ifstream &file, Part &part);
    bool readAP214STEP(std::ifstream &file, Part &part);

    Part part;

    bool corrupt;
};

#endif // STEP_READER_H
