#include "UI.h"


UI::UI() {
    clearConsole();
    println("Welcome to the start menu");
}

std::string UI::startMenu() {
    println("Do you wish to continue (Y/n)");
    std::string userInput;
    std::cin >> userInput;
    return userInput;
}

int UI::continueProgram(std::string userInput) {
    if (userInput == "N" || userInput == "n") {
        return 0;
    } else if (userInput == "Y" || userInput == "y") {
        return 1;
    } else {
        return 2;
    }
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

void UI::printMetadata(const FileManager& file) {
    clearConsole();
    println("METADATA");
    std::cout << "File Name:       " << file.getFileName() << "\n";
    std::cout << "Audio Format:    " << file.getAudioFormat() << "\n";
    std::cout << "Mono/Stereo:     " << file.getMonoStereo() << "\n";
    std::cout << "Sample Rate:     " << file.getSampleRate() << "\n";
    std::cout << "Byte Rate:       " << file.getByteRate() << "\n";
    std::cout << "Bitdepth:        " << file.getBitsPerSample() << "\n";
    std::cout << "Block Align:     " << file.getBlockAlign() << "\n";
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
    std::string promptDecay = "By what percentage do you want the echo to decrease by (0 - 100)?";
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
        if (!userInput.empty() && userInput.find_first_not_of("0123456789") == std::string::npos) {
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
    println("Closing application");
    delay(1);
    clearConsole();
}

void UI::printError() {
    println("ERROR: Invalid input. Please try again.");
    delay(2);
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

void UI::println(const std::string& line) {
    std::cout << line << "\n";
}
void UI::delay(int time) {
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(time));
}
void UI::clearConsole() {
    std::system("clear");
}