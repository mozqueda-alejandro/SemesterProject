#ifndef UI_H
#define UI_H

#include <exception>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
//#include <cstdlib>
#include "FileManager.h"

class UI {

public:
    UI();
    std::string startMenu();
    bool continuePrompt();
    int continueProgram(std::string);
    std::string enterFileName();
    void printMetadata(const FileManager&);
    std::string processorMenu();
    bool continueProcessor(std::string);
    std::vector<int> echoOptions(const FileManager&);
    int gainOption(const FileManager&);
    int promptProcessor(const std::string&, const std::string&);
    int promptGain(const std::string&);
    void exitScreen();
    
    void printError();
    void printError(const std::string&, int = 2); //const char*
    void printError(const std::ostringstream&, int = 2);
    void println(const std::string&);
    void delay(int);
    void clearConsole();
};


#endif //UI_H