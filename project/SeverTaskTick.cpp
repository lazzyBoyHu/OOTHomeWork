#include <iostream>
#include <chrono>

#include "SeverTaskTick.h"



Time SeverTimer::currentTime;

SeverTimer::SeverTimer() : _one_sec(1000L)
{
    timerThread = std::make_shared<std::thread>(&SeverTimer::run, this);
}


SeverTimer::~SeverTimer()
{
    isFinalStop = true;
    timerThread->join();
}

void SeverTimer::run()
{
    std::chrono::milliseconds dura(CHECKPRECISION);

    while(!isFinalStop)
    {
        if (_one_sec(currentTime))
            dealOneSec();

        std::this_thread::sleep_for(dura);
    }
}
