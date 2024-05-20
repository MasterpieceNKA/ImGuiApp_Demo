
if exist build\clang_Debug\bin\Debug\ImGuiApp_Demo.exe del build\clang_Debug\bin\Debug\ImGuiApp_Demo.exe

cmake -S . -B build/clang_Debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
cmake -E time cmake --build build/clang_Debug

.\build\clang_Debug\bin\Debug\ImGuiApp_Demo.exe