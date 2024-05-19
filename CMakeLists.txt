cmake_minimum_required(VERSION 3.16)

project(ImGuiApp_Demo LANGUAGES CXX)
if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()

add_subdirectory(ImGuiApp)
add_subdirectory(ImGuiApp_Demo)