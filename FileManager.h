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
    FileManager();
    virtual ~FileManager();
    
    void checkHeader(const std::string&);
    bool writeFile(std::string);
    
    std::string getFileName() const { return fileName; }
    std::string get;
    double getFileDuration() const;
    const std::vector<float>& getSamples() const { return samples; }

    //RIFF Header
    std::string getRiffHeader() const { return header.riff_header; };
    int getWavSize() const { return header.wav_size; }
    std::string getWaveHeader() const { return header.wave_header; }
    
    //fmt Header
    std::string getFmtHeader() const { return header.fmt_header; }
    int getFmtChunkSize() const { return header.fmt_chunk_size; }
    std::string getAudioFormat() const;
    std::string getMonoStereo() const;
        //short getFormat() const { return header.audio_format; }
        //short getNumChannels() const { return header.num_channels; }
    int getSampleRate() const { return header.sample_rate; }
    int getByteRate() const { return header.byte_rate; }
    short getSampleAlignment() const { return header.sample_alignment; }    
    short getBitsPerSample() const { return header.bit_depth; }
    
    //Data
    std::string getDataHeader() const { return header.data_header; }
};

#endif //FILE_MANAGER_H