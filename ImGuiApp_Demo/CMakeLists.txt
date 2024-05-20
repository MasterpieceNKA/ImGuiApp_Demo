project(ImGuiApp_Demo LANGUAGES CXX)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dependencies)

include_directories(
    ${ImGuiApp_INCLUDE_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

set(ImGuiApp_Demo_SOURCE ${CMAKE_CURRENT_LIST_DIR}/src/ImGuiApp_Demo.cpp)

add_executable(${PROJECT_NAME} ${ImGuiApp_Demo_SOURCE})

target_link_libraries(${PROJECT_NAME} PUBLIC ImGuiApp)