@echo off
g++ -c src/main.cpp src/Planet.cpp src/Button.cpp src/Rocket.cpp src/UFO.cpp -Iinclude -I"C:\SFML\include"
g++ main.o Planet.o Button.o Rocket.o UFO.o -o bin/proiect_poo.exe -L"C:\SFML\lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
del *.o