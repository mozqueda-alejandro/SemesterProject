#include <iostream>
#include <fstream>
#include <string>
#include "Wav.h"
#include "UI.h"
#include "FileManager.h"


/**
 * @brief Main method
 * 
 * @return int 
 */
int main() {	
    bool executeProgram = true;
    while (executeProgram) {
        
        UI newUI;
        bool repeatMainMenu = true;
        do { 
            std::string userInput = newUI.startMenu();
            switch (newUI.continueProgram(userInput)) {
                case 0:
                    //return 0;
                    executeProgram = false;
                    repeatMainMenu = false;
                    break;
                case 1:
                    repeatMainMenu = false;
                    break;
                case 2:
                    newUI.printError();
                    break;
                default:
                    std::cout << "ERROR: Main menu switch\n\n";
            }
        } while (repeatMainMenu);

        FileManager newFile;

        bool passProcessor = false;
        if (executeProgram) {
            int count = 0;
            bool isWav;
            do {
                std::string fileInput = newUI.enterFileName();
                try {
                    newFile.checkHeader(fileInput);
                    isWav = true;
                } catch(const std::exception& e) {
                    newUI.printError(e.what());
                    isWav = false;
                    count++;
                }
                if (count == 3) { 
                    passProcessor = true;
                    break; 
                }
            } while(!isWav);
        }
        
        if (executeProgram && !passProcessor) {

            newUI.printMetadata(newFile);
            std::string userInput;
            bool repeatProcessors = true;
            do { 
                userInput = newUI.processorMenu();
                if (newUI.continueProcessor(userInput) == true) {
                    repeatProcessors = false;
                } else {
                    //Clear console?
                    newUI.printError();
                }
            } while (repeatProcessors);    
            
            //Processor* newProcessor = nullptr;
            std::vector<int> echoParamters;
            switch (std::stoi(userInput)) {
                case 0:
                    //return 0;
                    executeProgram = false;
                    break;
                case 1: //NORMALIZATION
                    
                    

                    newUI.delay(3);
                    break;
                case 2: //ECHO
                    echoParamters = newUI.echoOptions(newFile);


                    break;
                case 3: //GAIN ADJUSTMENT
                    
                    
                    break;
                default:
                    newUI.printError();
                    std::cout << "ERROR: Processor menu switch\n\n";
            }
            
        }
        if (!executeProgram) { newUI.exitScreen(); }            
    }
    return 0;
}