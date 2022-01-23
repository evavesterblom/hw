#include <functional>
#include <thread>

class intervalTimer
{
    public:
        void run();
        void stop();
        intervalTimer(std::function<void()> callbackFunction, int intervalMillis);
        ~intervalTimer();
        
    private:
        int intervalMillis;
        std::function<void()> callbackFunction;
        void loop();
        bool stopped;
        std::thread t;
};