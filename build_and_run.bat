@echo off
echo Installing required programs...

echo 1. Installing MSYS2...
powershell -Command "Invoke-WebRequest -Uri 'https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe' -OutFile 'msys2.exe'"
echo Run msys2.exe and install to C:\msys2

echo 2. After installation, open MSYS2 UCRT64 and run:
echo pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-sfml

echo 3. Building project...
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .

echo 4. Copying DLLs...
copy C:\msys2\ucrt64\bin\sfml-*.dll .

echo 5. Running program...
figure_render.exe
pause