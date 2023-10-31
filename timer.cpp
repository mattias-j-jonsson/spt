// put timer class here

#include<thread>


class Timer
{
private:
    bool active;
public:
    Timer() {
        this->active = true;
    }
    ~Timer() {

    }
    void setTimeout(auto func, int delay) {
        this->active = true;
        std::thread t([=, *this] () {
            if(this->active == false) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            if(this->active == false) return;
            func();
        });
        t.detach();
    }
    void setInterval(auto func, int interval) {
        this->active = true;
        std::thread t([=, *this] () {
            while(true) {
                if(this->active == false) return;
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                if(this->active == false) return;
                func();
            }
        });
        t.detach();
    }

    void stop() {
        this->active = false;
    }

    void stop(int delay) {
        this->setTimeout([&]() {this->stop();}, delay);
    }

    bool isActive() {
        return this->active;
    }
};
