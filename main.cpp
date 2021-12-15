#include <iostream>
#include <fstream>
#include <string>
#include "UI.h"
#include "FileManager.h"
#include "WavException.h"


/**
 * @brief Main method
 * 
 * @return int 
 */
int main() {	
    bool executeProgram = true;
    do {
        
        UI newUI;        
        if (!newUI.continuePrompt()) {
            executeProgram = false;
        }

        FileManager newFile;
        
        bool passProcessor = false;
        if (executeProgram) {
            int count = 0;
            std::string fileInput = "";
            bool isWav;
            do {
                //Skips processor menu and repeats program if file is not WAV
                //(SEM Project) Set to 1 to only prompt for file once
                if (count >= 3) { 
                    passProcessor = true;
                    isWav = true; 
                }
                fileInput = newUI.enterFileName();
                //Ignore: For testing purposes only
                if (fileInput == "q.wav") {
                    passProcessor = true;
                    break;
                }
                try {
                    newFile.checkHeader(fileInput);
                    isWav = true;
                } catch(const std::runtime_error& e) {
                    newUI.printError(e.what(), 1.5);
                    isWav = false;
                    count++;
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
                    
                    

                    //newUI.delay(3);
                    break;
                case 2: //ECHO
                    echoParamters = newUI.echoOptions(newFile);


                    break;
                case 3: //GAIN ADJUSTMENT
                    
                    
                    break;
                default: newUI.printError("PROGRAM ERROR: Processor menu switch");
            }
                        
        } //Prints Metadata/processor
        if (!executeProgram) { 
            newUI.exitScreen();
        }        
    } while (executeProgram);
    return 0;
}