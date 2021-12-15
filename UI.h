#ifndef UI_H
#define UI_H

//clearConsole()
#if defined(_WIN32) || defined(_WIN64)
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#include <exception>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <limits>
//#include <cstdlib>
#include "FileManager.h"

class UI {
    void displayHeader(std::string menuHeader);
    int promptProcessor(const std::string&, const std::string&);
    int promptGain(const std::string&);
    void formatHeader(const FileManager&);
public:
    UI();
    bool continuePrompt();
    std::string enterFileName();
    void smartChecker(std::string);
    bool promptFile();
    void printMetadata(const FileManager&);
    std::string processorMenu();
    bool continueProcessor(std::string);
    std::vector<int> echoOptions(const FileManager&);
    int gainOption(const FileManager&);
    void exitScreen();
    
    void printError();
    void printError(const char* error, int time);
    void printError(const std::string&, int = 2);
    void printError(const std::ostringstream&, int = 2);
    void printDelay(std::string);
    void println(const std::string&);
    void delay(double);//make private
    void clearConsole();//make private
    void test();
};


#endif //UI_H