cmake_minimum_required(VERSION 3.16)

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
file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR}/bin) 
if(IS_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
	file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR}/Debug)
	MESSAGE(STATUS "imgui.ini was copied into ${CMAKE_BINARY_DIR}/Debug")
endif(IS_DIRECTORY)
if(IS_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
	file(COPY imgui.ini DESTINATION ${CMAKE_BINARY_DIR}/Release)
	MESSAGE(STATUS "imgui.ini was copied into ${CMAKE_BINARY_DIR}/Release")
endif(IS_DIRECTORY)
#file(GLOB FOUND_SUBDIRECTORY_NAMES LIST_DIRECTORIES true ${CMAKE_BINARY_DIR}/bin/*)
#foreach(FOUND_SUBDIRECTORY_NAME ${FOUND_SUBDIRECTORY_NAMES})
#	IF(IS_DIRECTORY ${FOUND_SUBDIRECTORY_NAME})
#		file(COPY imgui.ini DESTINATION ${FOUND_SUBDIRECTORY_NAME})
#		MESSAGE(STATUS "imgui.ini was copied into ${FOUND_SUBDIRECTORY_NAME}")
#	ENDIF()
#endforeach(FOUND_SUBDIRECTORY_NAME) 