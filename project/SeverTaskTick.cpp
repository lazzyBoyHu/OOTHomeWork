#include <iostream>
#include <chrono>

#include "SeverTaskTick.h"
#include "CarPark.h"
#include "EventManager.h"



Time SeverTimer::currentTime;

SeverTimer::SeverTimer() : _one_sec(1000L), _two_hundred_millisec(200L)
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
        if (_two_hundred_millisec(currentTime))
            dealTwoMillisec();

        std::this_thread::sleep_for(dura);
    }
}

void SeverTimer::dealOneSec()
{
}

void SeverTimer::dealTwoMillisec()
{
    CarPark * carPark = CarPark::GetInstance();
    if (carPark != nullptr)
        for (int i = 0; i < 2; ++i)
        {
            Sensor * tempSensor = carPark->getSensorByType(i);
            if (tempSensor != nullptr && tempSensor->canWork())
                tempSensor->work();
        }

    EventManager * eventManager = EventManager::GetInstance();
    if (eventManager != nullptr)
        eventManager->checkFire(currentTime);
}
