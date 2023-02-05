#include "MyApp/Logger.hpp"
#include "MyApp/Model.hpp"

#include "imgui.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace myapp
{
namespace detail
{
template <typename F> auto makeLogButton(Logger &logger, const char *text, F func)
{
    if (ImGui::Button(text))
    {
        logger.log(std::string("Press button: ") + text);
        func();
    }
}

struct MicrowaveView
{
    void tick()
    {
        if (mIsRunning)
        {
            if (mCookTime <= 0)
            {
                gLogger.log("cooking finished\n");
                mIsRunning = false;
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
            mIsRunning = true;

            using namespace std::chrono_literals;
            mNextSecond = std::chrono::steady_clock::now() + 1s;
        });

        if (mIsRunning)
        {
            makeLogButton(gLogger, "Stop", [&]() { mIsRunning = false; });
        }

        makeLogButton(gLogger, "Reset", [&]() { mCookTime = 0; });
        makeLogButton(gLogger, "+30 sec", [&]() { mCookTime += 30; });

        ImGui::InputInt("cook time", &mCookTime);

        ImGui::End();
    }

    int mCookTime = 10;
    bool mIsRunning = false;
    std::chrono::time_point<std::chrono::steady_clock> mNextSecond;
};

} // namespace detail

struct MainView
{
    void tick(Model &model)
    {
        mView.tick();
    }

    void draw(Model &model)
    {
        mView.draw();
        drawLogger();

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

        static int sleepTime = 1000 / 33;
        ImGui::SliderInt("sleep time per frame", &sleepTime, 0, 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds{sleepTime});

        if (sleepTime > 100)
        {
            std::this_thread::sleep_for(std::chrono::seconds{10});
            sleepTime = 30;
        }
    }

    detail::MicrowaveView mView;
};

void drawUi(Model &model);

} // namespace myapp
