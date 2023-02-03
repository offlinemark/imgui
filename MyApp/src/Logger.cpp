#include "MyApp/Logger.hpp"

#include "imgui.h"

namespace myapp
{

void drawLogger()
{
    ImGui::Begin("Logger");
    for (const auto &line : gLogger.lines())
    {
        ImGui::Text("%s", line.c_str());
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    // ImGui::SetScrollHereY(1.0f);

    ImGui::End();
}

} // namespace myapp
