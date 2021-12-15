wav: main.o UI.o FileManager.o WavException.o
	g++ -o wav main.o UI.o FileManager.o WavException.o

main.o: main.cpp UI.h FileManager.h WavException.h
	g++ -c main.cpp

UI.o: UI.cpp UI.h
	g++ -c UI.cpp

FileManager.o: FileManager.cpp FileManager.h
	g++ -c FileManager.cpp

WavException.o: WavException.cpp WavException.h
	g++ -c WavException.cpp

clean:
	rm *.o wav