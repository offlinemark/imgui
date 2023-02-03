#include "MyApp/MainView.hpp"
#include "MyApp/Logger.hpp"

#include "imgui.h"

namespace myapp
{

namespace
{

auto makeLogButton(Logger &logger, const char *text)
{
    if (ImGui::Button(text))
    {
        logger.log(std::string("Press button: ") + text);
    }
}

void drawMicrowaveWindow(Model &model)
{
    ImGui::Begin("Microwave Simulator");

    makeLogButton(gLogger, "Start");
    makeLogButton(gLogger, "Stop");
    makeLogButton(gLogger, "+30 sec");

    ImGui::End();
}

} // namespace

void drawUi(Model &model)
{
    drawMicrowaveWindow(model);
    drawLogger();
}

} // namespace myapp
