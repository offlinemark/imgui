cmake_minimum_required(VERSION 3.0.0)
project(app VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
  imgui
  third-party/imgui/imgui.cpp
  third-party/imgui/imgui_demo.cpp
  third-party/imgui/imgui_draw.cpp
  third-party/imgui/imgui_tables.cpp
  third-party/imgui/imgui_widgets.cpp
  third-party/imgui/backends/imgui_impl_glfw.cpp
  third-party/imgui/backends/imgui_impl_opengl3.cpp
)
target_include_directories(
  imgui PUBLIC third-party/imgui third-party/imgui/backends
)
target_link_libraries(imgui glfw OpenGL::GL)

add_subdirectory(src)
