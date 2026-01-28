@echo off
echo Установка необходимых программ...

echo 1. Устанавливаем MSYS2...
powershell -Command "Invoke-WebRequest -Uri 'https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe' -OutFile 'msys2.exe'"
echo Запустите msys2.exe и установите в C:\msys2

echo 2. После установки откройте MSYS2 UCRT64 и выполните:
echo pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-sfml

echo 3. Сборка проекта...
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

echo 4. Копирование DLL...
copy C:\msys2\ucrt64\bin\sfml-*.dll .

echo 5. Запуск программы...
figure_render.exe
pause