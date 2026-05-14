@echo off
chcp 65001 > nul
cls
echo ========================================
echo   COMPILANDO PROYECTO AEROPUERTO
echo ========================================
echo.

g++ main.cpp Menu.cpp -o aeropuerto -std=c++17 -lstdc++fs

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo   COMPILACION EXITOSA
    echo ========================================
    echo.
    echo Ejecutando aeropuerto.exe...
    echo.
    aeropuerto
) else (
    echo.
    echo ========================================
    echo   ERROR DE COMPILACION
    echo ========================================
    echo.
    echo Revisa los errores arriba.
    pause
)
