@echo off
echo Compilando el programa...

:: Intentar compilar el código
g++ ./src/Ticket.cpp ./src/MessageSender.cpp ./src/database.cpp main.cpp  -o TicketingSystem.exe -lstdc++

:: Verificar si la compilación fue exitosa
if %errorlevel% neq 0 (
    echo Error en la compilacion. Por favor, revise el codigo.
    pause
    exit /b %errorlevel%
)

echo Compilacion exitosa.
echo Ejecutando el programa...

:: Ejecutar el programa
TicketingSystem.exe

:: Pausa para mantener la ventana abierta
pause