//
// Created by Jonathan on 27/09/2024.
//

#ifndef BRE_STOPWATCH_HPP
#define BRE_STOPWATCH_HPP

#include <chrono>

using namespace std;
using namespace chrono;

enum class TimeUnit {
    MICROSECONDS,
    MILLISECONDS,
    SECONDS
};

class StopWatch {
    time_point<steady_clock> begin;
    time_point<steady_clock> end;
    long long unsigned int time_until_last_stop = 0;
    TimeUnit timeUnit;
    bool running = false;

public:
    StopWatch(TimeUnit timeUnit = TimeUnit::MILLISECONDS) : timeUnit(timeUnit) {}

    void start() {
        begin = steady_clock::now();
        running = true;
    }

    long long unsigned int now() {
        long long unsigned int elapsed = time_until_last_stop;
        if (running) {
            end = steady_clock::now();
            switch (timeUnit) {
                case TimeUnit::MICROSECONDS:
                    elapsed += duration_cast<microseconds>(end - begin).count();
                    break;
                case TimeUnit::MILLISECONDS:
                    elapsed += duration_cast<milliseconds>(end - begin).count();
                    break;
                case TimeUnit::SECONDS:
                    elapsed += duration_cast<seconds>(end - begin).count();
                    break;
            }
        }
        return elapsed;
    }

    void stop() {
        end = steady_clock::now();
        switch (timeUnit) {
            case TimeUnit::MICROSECONDS:
                time_until_last_stop += duration_cast<microseconds>(end - begin).count();
                break;
            case TimeUnit::MILLISECONDS:
                time_until_last_stop += duration_cast<milliseconds>(end - begin).count();
                break;
            case TimeUnit::SECONDS:
                time_until_last_stop += duration_cast<seconds>(end - begin).count();
                break;
        }
        running = false;
    }

    void reset() {
        time_until_last_stop = 0;
        running = false;
    }

    void restart() {
        reset();
        start();
    }
};

#endif //BRE_STOPWATCH_HPP
