//  Created by Patrick Wilke on 13.12.18.

#ifndef Stopwatch_h
#define Stopwatch_h

#include <chrono>
#include <iostream>
#include <vector>

    
class Stopwatch{

    typedef std::chrono::time_point<std::chrono::high_resolution_clock>     TimePoint;
    typedef std::chrono::duration<double, std::ratio<1>> Seconds;

public:
    Stopwatch();

    void Start();

    void Stop();

    void StopAndRestart();

    void PrintLast();

    void PrintAll();

private:
    TimePoint begin_, end_;
    bool is_running_;
    std::vector<Seconds> measured_times_;
};

#endif /* Stopwatch_h */
