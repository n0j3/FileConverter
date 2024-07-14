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
    bool isValidSTEPFile(const std::string &filePath);
    bool writeAP203STEP(const std::string &filePath, const Part &Part);
    bool writeAP214STEP(const std::string &filePath, const Part &Part);

    bool corrupt;
};

#endif // STEP_WRITER_H
