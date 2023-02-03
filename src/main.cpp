#include <iostream>
#include <string>
#include <vector>

#include "ImguiWrapper/ImguiWrapper.hpp"

// TODO: Port to ImGuiTextBuffer
class Logger
{
  public:
    void log(std::string text)
    {
        mLogLines.push_back(std::move(text));
    }

    const std::vector<std::string> &lines()
    {
        return mLogLines;
    }

  private:
    std::vector<std::string> mLogLines;
};

struct Model
{

    int mCookTime = 0;

    bool showDemoWindow = true;
};

Logger gLogger;

void drawLogger(Model &model)
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

void drawUi(Model &model)
{
    drawMicrowaveWindow(model);
    drawLogger(model);
}

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

int main()
{
    Model model;
    return imgui_wrapper::runApp(mainLoop, model);
}
