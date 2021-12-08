

**Start Menu**

The base start should allow the user to enter the name of a wav file or exit the application.

**File Metadata**
The data to be displayed in step (1):
*   filename
*   sample rate
*   bits per sample 
*   stereo or mono

### Required Processors
The following are the processes to be implemented
*   normalization
    
    *   Algorithm: The largest sample value in the data is found, and then the data is scaled so that that value is the maximum possible value. This maximizes the amplitude of the final waveform.
        
    *   Example for floating-point data
        
        *   Original data: n = {0,0.2,0.4,0,-0.3}
            
        *   Largest absolute value: 0.4, so scaling value s = 1/0.4 = 2.5
            
        *   Scaled result: n\_scaled = {0, 0.5,1,0,-0.75}
            
*   echo
    
    *   Algorithm: Samples are copied, scaled, and added to later locations in the sample buffer to create an echo effect.
        
*   gain adjustment
    
    *   Algorithm: Samples are multiplied by a scaling factor that raises or lowers the overall amplitude of the wave file

The system design is to be modular to facilitate dividing up the development work, and more importantly, to aid in testing and expansion of the application's capabilities. The required modules are

*   File management: manages reading and writing of files in the required formats
    
*   User interaction: manages the console user interaction. In the case of the challenge version using Qt, the module should provide a single point of entry to the processors, etc.
    
*   Processing: management of sample buffers, application of processors, etc. Each module will consist of one or more classes that are access through one or more interfaces.

### Documentation

All header files and functions must be documented using the Doxygen Javadoc format. The README page should include

*   A line saying whether this is a basic or challenge level project
*   The full names of each team member
*   The contribution of each team member
*   A UML diagram showing the basic design
*   A section detailing issues, including any functionality that is missing
*   A section detailing the challenges that you encountered in the project
*   Instructions for building the application if anything is required beyond _make_

The Doxygen files should be generated into a folder called _docs._