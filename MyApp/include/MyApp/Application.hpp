#include "MyApp/MainView.hpp"

#include "MyApp/SafeQueue.hpp"

#include <iostream>

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

    void tick()
    {
        mMainView.tick(mModel);
        mMainView.draw(mModel);
    }

  private:
    Model mModel;
    MainView mMainView;

    std::thread mThread;

    enum class Message
    {
        quit
    };
    SafeQueue<Message> mQueue;
};

} // namespace myapp
