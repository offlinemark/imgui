add_executable(app src/main.cpp src/MainView.cpp src/Logger.cpp)
target_include_directories(app PRIVATE include)
target_link_libraries(app PRIVATE ImguiWrapper XImgui)
