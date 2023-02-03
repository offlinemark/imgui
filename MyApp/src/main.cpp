
#include "Application.hpp"

#include "ImguiWrapper/ImguiWrapper.hpp"

int main()
{
    myapp::Application app;
    return imgui_wrapper::runApp("my test app", app);
}
