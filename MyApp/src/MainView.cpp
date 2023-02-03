#include "MainView.hpp"
#include "Logger.hpp"

#include "imgui.h"

namespace
{

auto makeLogButton(Logger &logger, const char *text)
{
    if (ImGui::Button(text))
    {
        logger.log(std::string("Press button: ") + text);
    }
}

} // namespace

void drawMicrowaveWindow(Model &model)
{
    ImGui::Begin("Microwave Simulator");

    makeLogButton(gLogger, "Start");
    makeLogButton(gLogger, "Stop");
    makeLogButton(gLogger, "+30 sec");

    ImGui::End();
}

void drawUi(Model &model)
{
    drawMicrowaveWindow(model);
    drawLogger();
}
