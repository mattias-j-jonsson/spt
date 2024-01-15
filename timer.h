#pragma once

class Timer
{
private:
    bool active;
public:
    Timer();
    ~Timer();

    void setTimeout(auto func, int delay);
    void setInterval(auto func, int interval);

    void stop();

    void stop(int delay);

    bool isActive();
};