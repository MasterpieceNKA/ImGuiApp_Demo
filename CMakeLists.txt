cmake_minimum_required(VERSION 3.16)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
    MESSAGE(STATUS "Setting CMAKE_TOOLCHAIN_FILE in root : ${CMAKE_TOOLCHAIN_FILE}")
endif() 

project(ImGuiApp_Demo LANGUAGES CXX)

if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()

add_subdirectory(ImGuiApp)
add_subdirectory(ImGuiApp_Demo)

# Copy figures into documentation folder
file(GLOB IMG_FILES "${CMAKE_CURRENT_LIST_DIR}/figures/*")
foreach(IMG_FILE ${IMG_FILES})
	file(COPY ${IMG_FILE} DESTINATION ${CMAKE_CURRENT_LIST_DIR}/docs/html/figures)
endforeach(IMG_FILE) 

# Copy imgui.ini configuration file into application folder 
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Release) 
file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR}) 
file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR}/bin) 
file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR}/bin/Debug) 
file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR}/bin/Release)  
