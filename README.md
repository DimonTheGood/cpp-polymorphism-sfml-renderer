1. Скачай MSYS2 (MinGW) https://www.msys2.org/, добавь в PATH.
2. Скачай CMake https://cmake.org/download/
3. Установи компилятор и библиотеки в MSYS2:
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-sfml
4. Собери
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .