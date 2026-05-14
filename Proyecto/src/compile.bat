@echo off
chcp 65001 > nul
cls
echo ========================================
echo   COMPILANDO PROYECTO AEROPUERTO
echo ========================================
echo.

g++ main.cpp controllers/PilotoController.cpp -o proyecto -std=c++17 -lstdc++fs

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo   COMPILACION EXITOSA
    echo ========================================
    echo.
    echo Ejecutando proyecto.exe...
    echo.
    proyecto
) else (
    echo.
    echo ========================================
    echo   ERROR DE COMPILACION
    echo ========================================
    echo.
    echo Revisa los errores arriba.
    pause
)
