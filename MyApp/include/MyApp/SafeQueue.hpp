#include <condition_variable>
#include <queue>
#include <thread>

namespace myapp
{

template <typename T> class SafeQueue
{
  public:
    void push(T element)
    {
        std::lock_guard guard{mMutex};
        mQueue.push(std::move(element));
        mCond.notify_one();
    }

    T pop()
    {
        std::unique_lock lock{mMutex};

        while (mQueue.empty())
        {
            mCond.wait(lock);
        }

        T local = std::move(mQueue.front());
        mQueue.pop();

        return local;
    }

  private:
    std::mutex mMutex;
    std::queue<T> mQueue;
    std::condition_variable mCond;
};

} // namespace myapp
