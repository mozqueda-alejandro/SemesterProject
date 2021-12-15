#ifndef WAV_EXCEPTION_H
#define WAV_EXCEPTION_H

#include <iostream>
#include <exception>


class WavException : public std::runtime_error {
    const char* file;
    int line;
    std::string info;
public:
    WavException();
    WavException(std::string newMessage) : std::runtime_error(newMessage) {}
    WavException(std::string newMessage, const char* newFile, int newLine, std::string newInfo = "") : runtime_error(newMessage),
        file (newFile),
        line (newLine),
        info (newInfo) {}
    const char* get_file() const { return file; }
    int get_line() const { return line; }
    std::string get_info() const { return info; }
};

class file_format_error : public WavException {
    
};

class input_error : public std::exception {

};



#endif //WAV_EXCEPTION_H