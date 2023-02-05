#include "MainView.hpp"
#include "MyApp/SafeQueue.hpp"

#include "imgui.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace myapp
{

class Application
{
  public:
    Application()
    {
        std::cout << "ctor\n";
        mThread = std::thread([&]() {
            std::cout << "from other thread\n";

            while (true)
            {
                const auto message = mQueue.pop();
                if (message == Message::quit)
                {
                    break;
                }
            }

            std::cout << "thread exit\n";
        });
    }

    ~Application()
    {
        std::cout << "dtor\n";
        mQueue.push(Message::quit);
        mThread.join();
        std::cout << "dtor2\n";
    }

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

        static int sleepTime = 1000 / 33;
        ImGui::SliderInt("sleep time per frame", &sleepTime, 0, 1000);
        std::this_thread::sleep_for(std::chrono::milliseconds{sleepTime});

        if (sleepTime > 100)
        {
            std::this_thread::sleep_for(std::chrono::seconds{10});
            sleepTime = 30;
        }
    }

  private:
    Model mModel;

    std::thread mThread;

    enum class Message
    {
        quit
    };
    SafeQueue<Message> mQueue;
};

} // namespace myapp
