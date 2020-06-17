build:
	gcc -Wall -std=c99 ./src/main.c -I"E:\dev\libsdl\include" -L"E:\dev\libsdl\lib" -lmingw32 -lSDL2main -lSDL2 -o renderer.exe

clean:
	del renderer.exe
