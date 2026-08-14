@echo off
title BAGHEERA CORE ENGINE - KNOCKSSTUDiOS
color 0A
echo ===================================================
echo     STARTING BAGHEERA CORE ENGINE (KNOCKSSTUDiOS)   
echo ===================================================
echo.

cd /d "C:\Users\gtama\ks_studio\ComfyUI"
call C:\Users\gtama\ks_studio\venv\Scripts\activate

echo Booting engine server...
python main.py --directml

pause