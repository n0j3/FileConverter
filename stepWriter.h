#ifndef STEP_WRITER_H
#define STEP_WRITER_H

#include <string>
#include "mesh.h"

class STEP_Writer {
public:
    STEP_Writer();
    bool writeSTEP(const Mesh &mesh, const std::string &filePath);
    bool isCorrupt() const;

private:
    bool corrupt;

    bool isValidSTEPFile(const std::string &filePath);
};

#endif // STEP_WRITER_H
