if exist build\MinGW_Debug\bin\ImGuiApp_Demo.exe del build\MinGW_Debug\bin\ImGuiApp_Demo.exe

cmake -S . -B build/MinGW_Debug -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake -E time cmake --build build/MinGW_Debug

.\build\MinGW_Debug\bin\ImGuiApp_Demo.exe
