cmake_minimum_required (VERSION 3.10)
project (DPW_Quadtree)

find_package(OpenCV REQUIRED)

include_directories (${OpenCV_INCLUDE_DIRS})

add_executable(DPW_Quadtree main.cpp Functions.cpp)

target_link_libraries(DPW_Quadtree ${OpenCV_LIBS})
