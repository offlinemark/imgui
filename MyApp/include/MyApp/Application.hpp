#include "MainView.hpp"

#include "imgui.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace myapp
{

class Application
{
  public:
    void draw()
    {
        drawUi(mModel);

        {
            static bool isCollapsed = true;
            ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);
            isCollapsed = ImGui::Begin("xxDebug", nullptr, 0);

            ImGui::Checkbox("Demo Window", &mModel.showDemoWindow); // Edit bools storing our window open/close state
            ImGui::Text("Hello world");                             // Edit bools storing our window open/close state

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
        if (mModel.showDemoWindow)
            ImGui::ShowDemoWindow(&mModel.showDemoWindow);

        // ImGui::ShowMetricsWindow();

        static int framesPerSecond;
        ImGui::SliderInt("sleep time per frame", &framesPerSecond, 0, 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds{framesPerSecond});
    }

  private:
    Model mModel;
};

} // namespace myapp
