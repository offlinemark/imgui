#include "MyApp/MainView.hpp"
#include "MyApp/Logger.hpp"

#include "imgui.h"

#include <iostream>

namespace myapp
{

namespace
{
template <typename F> auto makeLogButton(Logger &logger, const char *text, F func)
{
    if (ImGui::Button(text))
    {
        logger.log(std::string("Press button: ") + text);
        func();
    }
}

struct View
{
    void tick()
    {
        if (isRunning)
        {
            if (mCookTime <= 0)
            {
                gLogger.log("cooking finished\n");
                isRunning = false;
            }
            if (std::chrono::steady_clock::now() >= mNextSecond)
            {
                --mCookTime;

                using namespace std::chrono_literals;
                mNextSecond = std::chrono::steady_clock::now() + 1s;
                std::cout << "blah " << mCookTime << "\n";
            }
        }
    }
    void draw()
    {
        ImGui::Begin("Microwave Simulator");

        makeLogButton(gLogger, "Start", [&]() {
            isRunning = true;

            using namespace std::chrono_literals;
            mNextSecond = std::chrono::steady_clock::now() + 1s;
        });
        makeLogButton(gLogger, "Stop", [&]() { isRunning = false; });
        makeLogButton(gLogger, "Reset", [&]() { mCookTime = 0; });
        makeLogButton(gLogger, "+30 sec", [&]() { mCookTime += 30; });

        ImGui::InputInt("cook time", &mCookTime);

        ImGui::End();
    }

    int mCookTime = 10;

    bool isRunning = false;

    bool showDemoWindow = true;

    std::chrono::time_point<std::chrono::steady_clock> mNextSecond;
};

} // namespace

void drawMicrowaveWindow(Model &model)
{
}

void drawUi(Model &model)
{
    static View view;

    view.draw();
    view.draw();

    drawMicrowaveWindow(model);
    drawLogger();
}

} // namespace myapp
