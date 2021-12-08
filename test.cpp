#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include "WAV_HEADER.h"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
int getFileSize(FILE* inFile);

int main(int argc, char* argv[])
{
    WAV_HEADER wavHeader;
    int headerSize = sizeof(wavHeader), filelength = 0;
    struct dirent* de;  // Pointer for directory entry
    const char* filePath; 
    const char* salida;
    string input, salir;
    bool quedate = true;


    // loop pide path hasta que encuentra un archivo valido
    // Si no existen archivos validos, se sale
        if (argc <= 1)
        {
            //no hay parametros, pide el path y el nombre del archivo
            cout << "Input wave file name: ";


            cin >> input;
            cin.get();
            filePath = input.c_str();
        }
        else
        {
            //'trabaja con el parametro que se le paso desde el principio'
            filePath = argv[1];
            cout << "Input wave file name: " << filePath << endl;
        }
        //abre el archivo recivido por input o parametro, en modo lectura
        FILE* wavFile = fopen(filePath, "r");
        if (wavFile == nullptr)
        {
            //manda mensage si no lo puede abrir
            fprintf(stderr, "Unable to open wave file: %s\n", filePath);
            //List los archivos disponibles


       // open dir() returns a pointer of DIR type. 

            //pregunta si quiere salir
            cout << "Do you want to exit (y/n)";
            cin.get();
            salida = salir.c_str();
            if (salida = "yes")
            {
                quedate = false;
                return 1;
            }
        }

    
    //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    cout << "Header Read " << bytesRead << " bytes." << endl;
    if (bytesRead > 0)
    {
        //Read the data
        uint16_t bytesPerSample = wavHeader.bit_depth / 8;      //Number     of bytes per sample
        uint64_t numSamples = wavHeader.wav_size / bytesPerSample; //How many samples are in the wav file?
        static const uint16_t BUFFER_SIZE = 4096;
        int8_t* buffer = new int8_t[BUFFER_SIZE];
        while ((bytesRead = fread(buffer, sizeof buffer[0], BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0)
        {
            /** DO SOMETHING WITH THE WAVE DATA HERE **/
            cout << "Read " << bytesRead << " bytes." << endl;
        }
        delete[] buffer;
        buffer = nullptr;
    
        filelength = getFileSize(wavFile);

        cout << "File is                    :" << filelength << " bytes." << endl;
        cout << "RIFF header                :" << wavHeader.riff_header[0] << wavHeader.riff_header[1] << wavHeader.riff_header[2] << wavHeader.riff_header[3] << endl;
        cout << "WAVE header                :" << wavHeader.wave_header[0] << wavHeader.wave_header[1] << wavHeader.wave_header[2] << wavHeader.wave_header[3] << endl;
        cout << "FMT                        :" << wavHeader.fmt_header[0] << wavHeader.fmt_header[1] << wavHeader.fmt_header[2] << wavHeader.fmt_header[3] << endl;
        cout << "Data size                  :" << wavHeader.wav_size << endl;

        // Display the sampling Rate from the header
        cout << "Sampling Rate              :" << wavHeader.sample_rate << endl;
        cout << "Number of bits used        :" << wavHeader.bit_depth << endl;
        cout << "Number of channels         :" << wavHeader.num_channels << endl;
        cout << "Number of bytes per second :" << wavHeader.byte_rate << endl;
        cout << "Data length                :" << wavHeader.data_bytes << endl;
        cout << "Audio Format               :" << wavHeader.audio_format << endl;
        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

        cout << "Block align                :" << wavHeader.sample_alignment << endl;
        cout << "Data string                :" << wavHeader.data_header[0] << wavHeader.data_header[1] << wavHeader.data_header[2] << wavHeader.data_header[3] << endl;
    }
    fclose(wavFile);
   
    return 0;

}

// find the file size
int getFileSize(FILE* inFile)
{
    int fileSize = 0;
    
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    
    return fileSize;
}