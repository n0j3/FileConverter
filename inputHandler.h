#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string>

class InputHandler {
public:
    InputHandler();

    bool readFromTerminal(std::string &inputDir, std::string &inputFile, 
                          std::string &outputDir, std::string &outputFile, bool &binary, bool &ap214);
    bool simulateInput(std::string &inputDir, std::string &inputFile, 
                       std::string &outputDir, std::string &outputFile, bool &binary, bool &ap214);

private:
    bool printPaths(std::string& inputDir, std::string& inputFile, 
                    std::string& outputDir, std::string& outputFile, bool binary, bool ap214);
    bool processInput(std::string& dir, std::string& file);
};

#endif // INPUTHANDLER_H
