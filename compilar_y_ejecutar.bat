@echo off
echo Cerrando procesos anteriores del juego...
taskkill /F /IM 09_GalagaInvertido.exe 2>nul

echo Compilando el juego...
g++ src/09_GalagaInvertido.cpp -o bin/09_GalagaInvertido.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d -Iinclude

if %ERRORLEVEL% EQU 0 (
    echo Compilacion exitosa!
    echo Ejecutando el juego...
    bin\09_GalagaInvertido.exe
) else (
    echo Error en la compilacion.
    pause
)
