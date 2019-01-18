#include <iostream>
#include <string>
#include <ctime>
#include <time.h>

#include "timer.h"


Time::Time()
{
    clock_gettime(CLOCK_REALTIME, &_ts);
    _msec = _ts.tv_nsec / 1000000L + _ts.tv_sec * 1000;
    _tm_ok = false;
}

Time::Time(unsigned long delay)
{
    clock_gettime(CLOCK_REALTIME, &_ts);
    _ts.tv_nsec += (delay * 1000000L);
    _ts.tv_sec += (_ts.tv_nsec / 1000000000L);
    _ts.tv_nsec %= 1000000000L;
    _msec = _ts.tv_sec * 1000L + _ts.tv_nsec / 1000000L;
    _tm_ok = false;
}

inline bool Time::operator>(Time &_rt)
{
    if (_msec > _rt._msec)
        return true;
    return false;
}

inline bool Time::operator<(Time &_rt)
{
    if (_msec > _rt._msec)
        return false;
    return true;
}

inline bool Time::operator<=(Time &_rt)
{
    if (_msec > _rt._msec)
        return false;
    return true;
}

inline bool Time::operator>=(Time &_rt)
{
    if (_msec < _rt._msec)
        return false;
    return true;
}

inline bool Time::operator==(Time &_rt)
{
    if (_msec == _rt._msec)
        return true;
    return false;
}

std::string Time::tostring()
{
    if (!_tm_ok)
        _tm = *std::gmtime(&_ts.tv_sec);
    std::string s( "时间是: ");
    s += std::to_string(_tm.tm_year);
    s.append("年, ");
    s += std::to_string(_tm.tm_mon);
    s.append("月, ");
    s += std::to_string(_tm.tm_mday);
    s.append("日, ");
    s += std::to_string(_tm.tm_hour);
    s.append("时, ");
    s += std::to_string(_tm.tm_min);
    s.append("分, ");
    s += std::to_string(_tm.tm_sec);
    s.append("秒.");
    return s;
}

inline void Time::addDelay(const unsigned long delay)
{
    _ts.tv_nsec += (delay * 1000000L);
    _ts.tv_sec += (_ts.tv_nsec / 1000000000L);
    _ts.tv_nsec %= 1000000000L;
    _msec = sec() * 1000L + _ts.tv_nsec / 1000000L;
    _tm_ok = false;
}

void Timer::reset(const unsigned long how_long, const Time &cur)
{
    _long = how_long;
    _timer = cur;
    _timer.addDelay(_long);
}

void Timer::next(const Time &cur, const unsigned long delay)
{
    _timer = cur;
    _timer.addDelay(delay);
}

void Timer::next(const Time &cur)
{
    _timer = cur;
    _timer.addDelay(_long);
}

inline bool Timer::operator()(const Time &cur)
{
    if (_timer.msec() > cur.msec())
    {
        return false;
    }
    addDelay(cur);
    return true;
}

inline void Timer::addDelay(const Time &cur)
{
    _timer = cur;
    _timer.addDelay(_long);
}
