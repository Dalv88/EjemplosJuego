@echo off
echo Cerrando procesos anteriores del juego...
taskkill /F /IM JuegoProyecto.exe 2>nul

echo Compilando el juego...
g++ src/JuegoProyecto.cpp -o bin/JuegoProyecto.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude

if %ERRORLEVEL% EQU 0 (
    echo Compilacion exitosa!
    echo Ejecutando el juego...
    bin\JuegoProyecto.exe
) else (
    echo Error en la compilacion.
    pause
)
