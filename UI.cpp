#include "UI.h"


UI::UI() {
    clearConsole();
    displayHeader("WAV File Reader/Processor");
}

void UI::displayHeader(std::string menuHeader) {
    int width = menuHeader.length() + 6;
    std::ostringstream banner;
    banner << "+";
    for(int i = 0; i < width; ++i) {
        banner << "-";
    }
    banner << "+";
    std::cout << banner.str() << "\n";
    std::cout << "|   " + menuHeader + "   |\n";
    std::cout << banner.str() << "\n\n";
}

bool UI::continuePrompt() {
    std::string userInput = "";
    bool continueProgram;
    static bool first = true;
    bool repeat = true;
    do {
        printDelay("Do you want to continue (Y/n)? ");
        //IMPORTANT: FLUSHES INPUT STREAM
        if (!first) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        getline(std::cin, userInput);
        if (userInput == "N" || userInput == "n") {
            continueProgram = false;
            break;
        } else if (userInput == "Y" || userInput == "y" || userInput.empty()) {
            continueProgram = true;
            break;
        } else {
            printError();
        }
    } while (repeat);
    first = false;
    return continueProgram;
}

std::string UI::enterFileName() {
    clearConsole();
    std::cout << "Enter the name of the WAV file you would like to process:\n";
    std::string fileInput;
    std::cin >> fileInput;
    if (fileInput.find(".wav") == std::string::npos) {
        if (fileInput.find(".wave") == std::string::npos) {
            fileInput += ".wav";
        }
    }
    return fileInput;
}

void UI::smartChecker(std::string) {
    
}

bool UI::promptFile() {
    return true;
}

void UI::formatHeader(const FileManager& file) {
    
}

void UI::printMetadata(const FileManager& file) {
    clearConsole();
    formatHeader(file);
    println("METADATA");
    std::cout << "File Name:         " << file.getFileName() << "\n";
    std::cout << "RIFF Header:       " << (file.getRiffHeader()).substr(0, 4) << "\n";
    std::cout << "WAV Size:          " << file.getWavSize() << " bytes\n";
    std::cout << "WAV Header:        " << (file.getWaveHeader()).substr(0, 4) << "\n";
    std::cout << "Format Header:     " << file.getFmtHeader() << "\n";
    std::cout << "Audio Format:      " << file.getAudioFormat() << "\n";
    std::cout << "Mono/Stereo:       " << file.getMonoStereo() << "\n";
    std::cout << "Sample Rate:       " << file.getSampleRate() << " Hz\n";
    std::cout << "Byte Rate:         " << file.getByteRate() << " Bytes per second\n";
    std::cout << "Bit Depth:         " << file.getBitsPerSample() << "-Bit\n";
    std::cout << "Block Align:       " << file.getSampleAlignment() << "\n";
    delay(3);
}

std::string UI::processorMenu() {
    std::cout << "\n";
    println("Please select a processor or press \"0\" to exit:");
    println("(0) EXIT");
    println("(1) Normalization");
    println("(2) Echo");
    println("(3) Gain Adjustment");
    std::string userInput;
    std::cin >> userInput;
    return userInput;
}

bool UI::continueProcessor(std::string userInput) {
    return (userInput.length() == 1 && userInput.find_first_not_of("0123") == std::string::npos);
}

std::vector<int> UI::echoOptions(const FileManager& file) {
    clearConsole();
    std::vector<int> options;
    std::string promptDelay = "How long would you like the delay between echoes to be in seconds?";
    bool isValid = false;
    double timeDelay;
    do {
        timeDelay = promptProcessor(promptDelay, "Delay Time: ");
        if (timeDelay > file.getFileDuration()) {
            std::ostringstream error;
            error << "ERROR: Echo delay should be shorter than " << file.getFileDuration() << " seconds (the duration of the WAV file).";
            printError(error, 5);
        } else {
            isValid = true;
        }
    } while (!isValid);
    options.push_back(timeDelay);

    clearConsole();
    std::string promptDecay = "What loudness percentage of the original audio do you want the echo to be (0 - 100)?";
    isValid = false;
    int decay;
    do {
        decay = promptProcessor(promptDecay, "Decay Factor: ");
        if (decay < 0 || decay > 100) {
            printError("ERROR: Please enter a number between 0 and 100.", 4);
        } else {
            isValid = true;
        }
    } while (!isValid);
    options.push_back(decay);
    return options;
}

int UI::promptProcessor(const std::string& prompt, const std::string& shortPrompt) {
    println(prompt);
    std::string userInput;
    bool isValid = false;
    do {
        std::cout << shortPrompt;
        std::cin >> userInput;
        if (!userInput.empty() && userInput.find_first_not_of("0123456789") == std::string::npos && userInput.length() < 6) {
            isValid = true;
        } else { 
            printError(); 
        }
    } while (!isValid);
    return (std::stoi(userInput));
}

int UI::gainOption(const FileManager&) {
    clearConsole();
    std::string promptScale = "By what percentage do you want to scale your audio (0 - 100)?";
    int gain;
    bool isValid = false;
    do {
        gain = promptProcessor(promptScale, "Gain Adjustment: ");
        if (false) { //if (gain > newProcessor.maxScalabilty)
            printError("WARNING: Audio data will be compressed and may sound distorted.", 4);
        } else {
            isValid = true;
        }
    } while (isValid);
    return gain;
}

void UI::exitScreen() {
    clearConsole();
    std::cout << "Closing application";
    delay(0.45);
    //Closing animation. Remove if desired
    for (int i = 0; i < 3; i++) {
        std::cout << " . ";
        delay(0.2);
    }
    //clearConsole();
}

void UI::printError() {
    println("ERROR: Invalid input. Please try again.");
    delay(2);
    clearConsole();
}

void UI::printError(const char* error, int time) {
    std::cout << error << "\n";
    delay(time);
    clearConsole();
}
void UI::printError(const std::string& error, int time) {
    std::cout << error << "\n";
    delay(time);
    clearConsole();
}
void UI::printError(const std::ostringstream& error, int time) {
    std::cout << error.str() << "\n";
    delay(time);
    clearConsole();
}

void UI::printDelay(std::string line) {
    for (int i = 0; i < line.length(); i++) {
        std::cout << line[i];
        delay(0.025);
    }
}
void UI::println(const std::string& line) {
    std::cout << line << "\n";
}
void UI::delay(double dseconds) {
    std::cout << std::flush;
    int iseconds = static_cast<int>(dseconds * 1000);
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(iseconds));
}
void UI::clearConsole() {
    std::system(CLEAR);
}