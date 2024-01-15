// put timer class here

#include <thread>
#include "timer.h"


Timer::Timer() {
    this->active = true;
}

Timer::~Timer() {

}

void Timer::setTimeout(auto func, int delay) {
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

void Timer::stop() {
    this->active = false;
}

void Timer::stop(int delay) {
    this->setTimeout([&]() {this->stop();}, delay);
}

bool Timer::isActive() {
    return this->active;
}
