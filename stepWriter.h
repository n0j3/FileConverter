#ifndef STEP_WRITER_H
#define STEP_WRITER_H

#include <string>
#include "part.h"

class STEP_Writer {
public:
    STEP_Writer();
    bool writeSTEP(const Part &part, const std::string &filePath, bool &stepType);
    bool isCorrupt() const;

private:
    bool corrupt;

    bool isValidSTEPFile(const std::string &filePath);
};

#endif // STEP_WRITER_H
