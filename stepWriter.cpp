#include "stepWriter.h"
#include <ctime>
#include <fstream>
#include <iostream>

STEP_Writer::STEP_Writer() : corrupt(false) {}

bool STEP_Writer::writeSTEP(const Part &part, const std::string &filePath, bool &ap214) {
    if (!isValidSTEPFile(filePath)) {
        std::cerr << "Invalid STEP file." << std::endl;
        corrupt = true;
        return false;
    }

    if (ap214) {
        return writeAP214STEP(filePath, part);
    }
    
    else {
        return writeAP203STEP(filePath, part);
    }
}

bool STEP_Writer::isCorrupt() const {
    return corrupt;
}


bool STEP_Writer::isValidSTEPFile(const std::string &filePath) {
    return filePath.size() >= 5 && (filePath.substr(filePath.size() - 5) == ".step" || filePath.substr(filePath.size() - 4) == ".stp");
}


bool STEP_Writer::writeAP203STEP(const std::string &filePath, const Part &Part) {
    std::ofstream file(filePath);

    if (!file) {
        std::cerr << "Failed to open STEP file for writing." << std::endl;
        corrupt = true;
        return false;
    }

    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);
    char time_stamp[20];
    std::strftime(time_stamp, sizeof(time_stamp), "%Y-%m-%dT %H:%M:%S", now_tm);

    file << "ISO-10303-21;" << std::endl;
    file << "HEADER; << std::endl;" << std::endl;
    file << "FILE_DESCRIPTION((''),'2;1');" << std::endl;
    file << "FILE_NAME('','" << time_stamp << "',(''),(''),'','','');" << std::endl;
    file << "FILE_SCHEMA(('CONFIG_CONTROL_DESIGN'));" << std::endl;
    file << "ENDSEC;" << std::endl;
    file << "DATA;" << std::endl;

    //TODO
    //Fill data in .step
    
    file << "ENDSEC;" << std::endl;
    file << "DATA;" << std::endl;

    corrupt = false;
    return true;
}

bool STEP_Writer::writeAP214STEP(const std::string &filePath, const Part &Part) {
    std::ofstream file(filePath);

    if (!file) {
        std::cerr << "Failed to open file for writing." << std::endl;
        corrupt = true;
        return false;
    }

    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);
    char time_stamp[20];
    std::strftime(time_stamp, sizeof(time_stamp), "%Y-%m-%dT %H:%M:%S", now_tm);

    file << "ISO-10303-21;" << std::endl;
    file << "HEADER; << std::endl;" << std::endl;
    file << "FILE_DESCRIPTION((''),'2;1');" << std::endl;
    file << "FILE_NAME('','" << time_stamp << "',(''),(''),'','','');" << std::endl;
    file << "FILE_SCHEMA(('AUTOMOTIVE_DESIGN { 1 0 10303 214 1 1 1 1 }'));" << std::endl;
    file << "ENDSEC;" << std::endl;
    file << "DATA;" << std::endl;

    //TODO
    //Fill data in .step
    
    file << "ENDSEC;" << std::endl;
    file << "DATA;" << std::endl;

    corrupt = false;
    return true;
}
