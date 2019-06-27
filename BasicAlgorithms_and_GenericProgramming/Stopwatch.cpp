//  Created by Patrick Wilke on 13.12.18.

#include "Stopwatch.h"

Stopwatch::Stopwatch():is_running_{false}{};
///////////////////////////////////////////////////////////////////////
void Stopwatch::Start(){
    if (is_running_) {
        std::cout<<"Watch is still. Start not possible!\n";
        return;
    }
    is_running_=true;
    begin_=std::chrono::high_resolution_clock::now();
}
///////////////////////////////////////////////////////////////////////
void Stopwatch::Stop(){
    end_=std::chrono::high_resolution_clock::now();
    if (!is_running_) {
        std::cout<<"Watch was not running. Stop not possible!\n";
        return;
    }
    is_running_=false;
    measured_times_ .push_back(std::chrono::duration_cast<Seconds>(end_-begin_));
}
///////////////////////////////////////////////////////////////////////
void Stopwatch::StopAndRestart(){
    Stop();
    Start();
}
///////////////////////////////////////////////////////////////////////
void Stopwatch::PrintLast(){
    std::cout<<"Last time measured: "<<measured_times_.back().count()<<"    s\n";
}
///////////////////////////////////////////////////////////////////////
void Stopwatch::PrintAll(){
    long i=1;
    for (auto& x:measured_times_) {
        std::cout<<"Time measured "<<i<<": "<<x.count()<<" s\n";
        ++i;
    }
}
