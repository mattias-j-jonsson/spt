// spt app of the most advanced type will be created here

#include<iostream>
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

void countDown(int lengthOfCountdown) {
    int start = lengthOfCountdown;

    // Gör en "iteration" innan timern skapas för att kompenera för att Timer sover ett intervall innan den kör lambdafunktionen
    std::cout << "00:" << (start < 10 ? "0"+std::to_string(start) : std::to_string(start)) << std::endl;
    start--;

    Timer t = Timer();
    t.setInterval([&] () {
        // std::system("clear");
        if(start < 0) {
            t.stop();
            return;
        }
        std::cout << "00:" << (start < 10 ? "0"+std::to_string(start) : std::to_string(start)) << std::endl;
        start--;
    }, 1000);
    // t.setTimeout([&]() {t.stop();}, (start+2)*1000);
    // t.stop((start+1)*1000);
    while(t.isActive()) {}
}


void holdingSPT(int repetitions, int hold) {
    if(hold < 0 || repetitions < 0) {
        std::cout << "Incorrect arguments." << std::endl;
        return;
    }
    int rest = 2*hold;
    int reps_left = repetitions;
    while(reps_left > 0) {
        countDown(hold);
        countDown(rest);
        reps_left--;
    }
}

void powerSPT() {
    int reps = 10;
    int reps_left = reps;
    int hold = 4;
    int pause = 2;
    while(reps_left > 0) {
        countDown(hold);
        countDown(pause);
        reps_left--;
    }
}




int main(int argc, char const *argv[])
{
    
    holdingSPT(2, 3);
    // countDown(2);
    // powerSPT();

    // std::system("ls");
    // int interval = 450;
    // Timer t = Timer();

    // t.setInterval([&] () {std::cout << "hey, every " << interval << " ms." << "e=" << e << std::endl;}, interval);

    // t.setTimeout([&] () {std::cout << "STOP THIS MADNESS!!" << std::endl; t.stop();}, 7000);

    // std::this_thread::sleep_for(std::chrono::seconds(5));
    // interval = 50;
    // std::this_thread::sleep_for(std::chrono::seconds(5));


    return 0;
}