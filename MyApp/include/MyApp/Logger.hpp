#pragma once

#include <string>
#include <vector>

namespace myapp
{

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

inline Logger gLogger;

void drawLogger();

} // namespace myapp
