#include <stdio.h>
#include <string.h>
#include <chrono>
#include <thread>
#include "FileManager.h"
#include "WAV_HEADER.h"
    /*
    std::cout << std::endl;
    std::cout << header.riff_header << "\n";
    std::cout << header.wav_size << "\n";
    std::cout << header.wave_header << "\n";
    std::cout << header.fmt_header << "\n";
    std::cout << header.fmt_chunk_size << "\n";
    std::cout << header.audio_format << "\n";
    std::cout << header.num_channels << "\n";
    std::cout << header.sample_rate << "\n";
    std::cout << header.data_header << "\n";
    std::cout << std::flush;
    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(4));
    */


FileManager::FileManager() : data(nullptr) {}
FileManager::~FileManager() {
    delete[] data;
}

/**
 * @brief Attempts to open file, read file header into WAV_HEADER struct, and then read data into char[]
 * 
 * @param inFile: Preformatted with either .wav or .wave file extension
 */
void FileManager::checkHeader(const std::string& inFile) {
    std::ifstream ifs;
    ifs.open(inFile, std::ios::binary | std::ios::in);
    if (ifs.is_open()) {
        fileName = inFile;
        readHeader(ifs);
        if (strncmp(header.riff_header, "RIFF", 4) == 0) {
            if(strncmp(header.wave_header, "WAVE", 4) == 0) {
                if (strncmp(header.fmt_header, "fmt ", 4) == 0) {
                    readData(ifs);
                    //convertRawData();
                } else {
                    throw std::runtime_error("File does not have proper format.");
                }
            } else {
                throw std::runtime_error("RIFF file is not a WAVE file.");
            }
        } else {
            throw std::runtime_error("File is not a RIFF file.");
        }
        ifs.close();
    } else {
        throw std::runtime_error(inFile + " could not be opened.");
    }
}

/**
 * @brief 
 * 
 * @param ifs 
 */
void FileManager::readHeader(std::ifstream& ifs) {
    ifs.read((char*) &header.riff_header, sizeof(header.riff_header));
    //ifs.get();
    ifs.read((char*) &header.wav_size, sizeof(header.wav_size));
    ifs.read((char*) &header.wave_header, sizeof(header.wave_header));
    //
    ifs.read((char*) &header.fmt_header, sizeof(header.fmt_header));
    ifs.read((char*) &header.fmt_chunk_size, sizeof(header.fmt_chunk_size));
    ifs.read((char*) &header.audio_format, sizeof(header.audio_format));
    ifs.read((char*) &header.num_channels, sizeof(header.num_channels));
    ifs.read((char*) &header.sample_rate, sizeof(header.sample_rate));
    ifs.read((char*) &header.byte_rate, sizeof(header.byte_rate));
    ifs.read((char*) &header.sample_alignment, sizeof(header.sample_alignment));
    ifs.read((char*) &header.bit_depth, sizeof(header.bit_depth));
    //
    ifs.read((char*) &header.data_header, sizeof(header.data_header));
    ifs.read((char*) &header.data_bytes, sizeof(header.data_bytes));


}
void FileManager::readData(std::ifstream& ifs) {
    data = new char[header.data_bytes];
    ifs.read((char*)data, header.data_bytes);
}

bool FileManager::writeFile(std::string newFileName) {
    std::ofstream file(newFileName, std::ios::binary);
    bool fileWritten = false;
    if (file.is_open()) {
        file.write((char*) &header, sizeof(header));
        if (header.bit_depth == 8) {
            for (size_t i = 0; i < header.data_bytes; i++) {
                data[i] = convertTo8B(samples[i]);
            }
            fileWritten = true;
        } else if (header.bit_depth == 16) {
            int num = 0;
            for(size_t i = 0; i < header.data_bytes; i += 2) {
                short temp = convertTo16B(samples[num]);
                unsigned char lsb = *(reinterpret_cast<unsigned char*>(&temp));
                unsigned char msb = *(reinterpret_cast<unsigned char*>(&temp) + 1);
                data[i] = lsb;
                data[i + 1] = msb;
                num++;
            }
            fileWritten = true;
        }
        file.write(data, header.data_bytes);
        file.close();
    }
    return fileWritten;
}

void FileManager::convertRawData() {    
    if(header.bit_depth == 8) { 
        for(size_t i = 0; i < header.data_bytes; i++) {    
            samples.push_back(convertToFloat(*(reinterpret_cast<unsigned char*>(&data[i]))));
        }
    } else if (header.bit_depth == 16) {
        for(size_t i = 0; i < header.data_bytes; i += 2) {
            short shortSample = 0;
            *(reinterpret_cast<char*>(&shortSample)) = data[i];
            *(reinterpret_cast<char*>(&shortSample) + 1) = data[i + 1];
            samples.push_back(convertToFloat(shortSample));
        }
    } else {
        std::cout << "ERROR: convertRawData() bit depth\n\n";
    }
    // Check samples
    // for (int i = 0; i < 20; i++) {
    //     std::cout << samples[i] << " ";
    // }
}

std::string FileManager::getAudioFormat() const {
    std::string audioFormat;
    switch (header.audio_format) {
    case 0:
        audioFormat = "Unknown";
        break;
    case 1:
        audioFormat = "1 (PCM)";
        break;
    case 3:
        audioFormat = "3 (IEEE Floating-Point)";
        break;
    default:
        audioFormat = "Other Compressed fmt";
        break;
    }
    return audioFormat;
}

std::string FileManager::getMonoStereo() const {
    std::string numChannels = "Not Mono/Stereo";
    if (header.num_channels == 1) { numChannels = "Mono"; }
    else if (header.num_channels == 2) { numChannels = "Stereo"; }
    return numChannels;
}

double FileManager::getFileDuration() const {
    return (double)header.data_bytes / (((double)header.sample_rate) * ((double)header.num_channels) * ((double)header.bit_depth) / 8);
}

float FileManager::convertToFloat(unsigned char data) {
    return -1.0f + (2.0f / 255.0f) * static_cast<float>(*(reinterpret_cast<unsigned char*>(&data)));
}
float FileManager::convertToFloat(short data) {
    return 0.0f + (1.0f / 32768.0f) * static_cast<float>(data);
}

unsigned char FileManager::convertTo8B(float sample) {
    return (sample + 1.0f) / (2.0f / 255.0f);
}
short FileManager::convertTo16B(float sample) {
    return sample / (1.0f / 32768.0f);
}