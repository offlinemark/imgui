cmake_minimum_required(VERSION 3.0.0)
project(app VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ImguiWrapper)
add_subdirectory(src)
add_subdirectory(third-party/imgui)
