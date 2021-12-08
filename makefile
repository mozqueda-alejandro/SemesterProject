wav: main.o UI.o FileManager.o
	g++ -o wav main.o UI.o FileManager.o

main.o: main.cpp UI.h FileManager.h
	g++ -c main.cpp

UI.o: UI.cpp UI.h
	g++ -c UI.cpp

FileManager.o: FileManager.cpp FileManager.h
	g++ -c FileManager.cpp

clean:
	rm *.o wav