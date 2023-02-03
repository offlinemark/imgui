find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
  imgui
  dist/imgui.cpp
  dist/imgui_demo.cpp
  dist/imgui_draw.cpp
  dist/imgui_tables.cpp
  dist/imgui_widgets.cpp
  dist/backends/imgui_impl_glfw.cpp
  dist/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC dist dist/backends)
target_link_libraries(imgui glfw OpenGL::GL)
