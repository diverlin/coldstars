all:	
	g++ -c -g main.cpp 
	g++ -Wall -o main main.o -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -lGLEW
	rm main.o
