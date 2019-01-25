#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include <iostream>
#include <map>

#include "timer/timer.h"

// 事件类型
enum EventType
{
    EventType_ReadCard,
    EventType_RaiseRailing,
    EventType_LayDownRailing,
    EventType_Monitor,
};

enum EventErrorum
{
    NoEmployee = -1,
    NoICCard = -2,
    NoCarPark = -3,
    NoICCardMessage = -4,
    NoRailing = -5,
};

// 事件基类
class Event
{
    private:
        unsigned int m_eventType;
        std::string m_eventName;
        long m_delayTime;
        Time fireTime;
    public:
        Event(unsigned int eventType, std::string name, long delayTime) :
            m_eventType(eventType),
            m_eventName(name),
            m_delayTime(delayTime)
            {
                fireTime = Time(m_delayTime);
            }
        virtual ~Event() {}
        virtual void begin(unsigned int uid);
        void end(unsigned int uid);
        /**
         * 用于绑定一下相关的其他操作
         */
        virtual void fire(unsigned int uid);
        /**
         * 用于输出出错信息
         */
        void checkErrorMessage(int flag, unsigned int uid, unsigned int tempCardId = 0);
        /**
         * 检查时间
         */
        bool checkFireTime(Time &current);
};

class ReadCardEvent : public Event
{
    public:
        ReadCardEvent(unsigned int eventType, std::string name, long delayTime) : Event(eventType, name, delayTime) {}
        ~ReadCardEvent() {}
        void begin(unsigned int uid);
        void fire(unsigned int uid);
};

class RaiseRailingEvent : public Event
{
    public:
        RaiseRailingEvent(unsigned int eventType, std::string name, long delayTime) : Event(eventType, name, delayTime) {}
        ~RaiseRailingEvent() {}
        void begin(unsigned int uid);
        void fire(unsigned int uid);
};

class DownRailingEvent : public Event
{
    public:
        DownRailingEvent(unsigned int eventType, std::string name, long delayTime) : Event(eventType, name, delayTime) {}
        ~DownRailingEvent() {}
        void begin(unsigned int uid);
        void fire(unsigned int uid);
};

/*class SenserEvent : public Event
{
        SenserEvent(unsigned int eventType, std::string name, long delayTime) : Event(eventType, name, delayTime) {}
        ~SenserEvent() {}
        void begin(unsigned int uid);
        void fire(unsigned int uid);
};*/

class EventManager
{
    private:
        std::map<unsigned int, Event*> eventMap;
        static EventManager * instance;
    private:
        EventManager();
    public:
        void checkFire(Time &current);
        void addEvent(unsigned int uid, Event * event);
        void removeEvent(unsigned int uid);
        static EventManager * GetInstance();
};

#endif
