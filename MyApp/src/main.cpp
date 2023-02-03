#include <iostream>

#include "ImguiWrapper/ImguiWrapper.hpp"

#include "MainView.hpp"
#include "Model.hpp"

namespace myapp
{

void mainLoop(Model &model)
{
    drawUi(model);

    {
        static bool isCollapsed = true;
        ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);
        isCollapsed = ImGui::Begin("xxDebug", nullptr, 0);

        ImGui::Checkbox("Demo Window", &model.showDemoWindow); // Edit bools storing our window open/close state
        ImGui::Text("Hello world");                            // Edit bools storing our window open/close state

        if (ImGui::Button("my exciting button")) // Buttons return true when clicked (most widgets return true when
                                                 // edited/activated)
        {
            std::cout << "hellox\n";
        }

        ImGui::End();
    }

    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about
    // Dear ImGui!).
    if (model.showDemoWindow)
        ImGui::ShowDemoWindow(&model.showDemoWindow);

    // ImGui::ShowMetricsWindow();
}

} // namespace myapp

int main()
{
    myapp::Model model;
    return imgui_wrapper::runApp("my test app", myapp::mainLoop, model);
}
