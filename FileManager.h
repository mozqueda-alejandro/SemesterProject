#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include "WAV_HEADER.h"


class FileManager {
    WAV_HEADER header;
    std::string fileName;
    std::vector<float> samples;
    char* data;
    void readHeader(std::ifstream&);
    void readData(std::ifstream&);
    void convertRawData();
    float convertToFloat(unsigned char); 
    float convertToFloat(short);
    unsigned char convertTo8B(float);
    short convertTo16B(float);
public:    
    virtual ~FileManager();
    
    void checkHeader(const std::string&);
    bool writeFile(std::string);
    
    std::string getFileName() const { return fileName; }
    std::string getAudioFormat() const;
    std::string getMonoStereo() const;
    int getSampleRate() const { return header.sample_rate; }
    int getByteRate() const { return header.byte_rate; }
    //short getFormat() const { return header.audio_format; }
    //short getNumChannels() const { return header.num_channels; }
    short getBlockAlign() const { return header.sample_alignment; }    
    short getBitsPerSample() const { return header.bit_depth; }
    double getFileDuration() const;
    const std::vector<float>& getSamples() const { return samples; }

};

#endif //FILE_MANAGER_H