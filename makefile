all:
	gcc main.c -o main.exe -lGL -lglut -lGLU -lm
	./main.exe