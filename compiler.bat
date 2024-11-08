@echo off
echo Compilando el programa...

:: Intentar compilar el código
g++ ./src/database.cpp ./src/MessageSender.cpp ./src/Ticket.cpp ./todo/GPT.cpp -o GrafoDijkstra.exe -lstdc++

:: Verificar si la compilación fue exitosa
if %errorlevel% neq 0 (
    echo Error en la compilacion. Por favor, revise el codigo.
    pause
    exit /b %errorlevel%
)

echo Compilacion exitosa.
echo Ejecutando el programa...

:: Ejecutar el programa
GrafoDijkstra.exe

:: Pausa para mantener la ventana abierta
pause