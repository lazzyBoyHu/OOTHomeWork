#ifndef TIMER_H_
#define TIMER_H_

#include <string>
#include <ctime>

/**
 * 定义一个事件类
 * 便于操作时间
 */
class Time
{
    private:
        /**
         * \brief 真实时间
         */
        struct timespec _ts;
        /**
         * \brief 毫秒数
         *
         */
        unsigned long _msec;
        /**
         * \brief 标志
         * 标志_tm结构体数据是否有效
         */
        bool _tm_ok;
        /**
         * \brief 存放日期数据
         */
        struct tm _tm;
    public:
        /**
         * 使用一个当前时间初始化这个Time对象
         */
        Time();
        /**
         * 使用一个延迟的毫秒数来创建一个时间对象
         */
        Time(unsigned long delay);
        /**
         * \brief   返回秒数
         *          在读取秒数的时候需要加上当地时区信息
         * \return 秒数
         */
        inline unsigned long sec() const { return _ts.tv_sec; }
        /**
         * 返回毫秒数
         */
        inline unsigned long msec() const { return _msec; }
        /**
         * 重写>操作符
         * 判断两个Time对象大小
         */
        inline bool operator>(Time &_rt);
        /**
         * 重写<操作符
         * 判断两个Time对象大小
         */
        inline bool operator<(Time &_rt);
        /**
         * 重写<=操作符
         * 判断两个Time对象大小
         */
        inline bool operator<=(Time &_rt);
        /**
         * 重写>=操作符
         * 判断两个Time对象大小
         */
        inline bool operator>=(Time &_rt);
        /**
         * 重写等号操作符
         * 便于判断两个Time对象是否相同
         */
        inline bool operator==(Time &_rt);
        /**
         * 获取这个时间对象的时间的信息
         * return string;
         */
        std::string tostring();
        /**
         * 加延迟偏移量
         */
        inline void addDelay(const unsigned long delay);
};

class Timer
{
    public:
        /**
         * \brief 构造函数
         * \param how_long  定时器的时间，单位：毫秒
         * \param first     有些定时器可能希望在启动时就可以执行一次,所以不能直接addDelay哦
         */
        explicit Timer(const long how_long, bool first = false, const long delay = 0) : _long(how_long), _timer()
        {
            if (!first)
                _timer.addDelay(_long + delay);
        }

        /**
         * \brief 构造函数
         * \param how_long  定时器的时间，单位：毫秒
         * \param first     有些定时器可能希望在启动时就可以执行一次,所以不能直接addDelay哦
         * \param ctv       当前时间
         */
        explicit Timer(const long how_long, bool first, Time &ctv) : _long(how_long), _timer(ctv)
        {
            if (!first)
                _timer.addDelay(_long);
        }

        /**
         * \brief 重新设置定时器的精度和开始计时时间
         * \param how_long  定时器的时间，单位：毫秒
         * \param ctv       当前时间
         *
         */
        void reset(const unsigned long how_long, const Time &cur);

        /**
         * \brief 重新设置定时器的时间
         * \param cur       指定定时器启动的时间
         */
        void current(const Time &cur) { _timer = cur; }
        /**
         * \brief 延时定时器时间
         * \param cur   指定定时器启动的时间
         * \param delay 延时时间
         */
        void next(const Time &cur, const unsigned long delay);

        /**
         * \brief 重新设置定时器的时间
         * \param cur       指定定时器启动的时间
         */
        void next(const Time &cur);

        /**
         * \brief 倒计时剩余秒数.不受时间调整影响.
         * \param cur   当前时间
         * \return 剩余描述
         */
        inline unsigned long leftSec(const Time &cur) { return (_timer.sec() > cur.sec()) ? (_timer.sec() - cur.sec()) : 0; }
        /**
         * \brief 倒计时剩余毫秒数.受时间调整影响
         * \param cur   当前时间
         * \return 剩余值
         */
        inline unsigned long leftMSec(const Time &cur) { return (_timer.msec() > cur.msec()) ? (_timer.msec() - cur.msec()) : 0; }
        inline unsigned long elapseMSec(const Time &cur) { return (_timer.msec() > cur.msec()) ? (_long - (_timer.msec() - cur.msec())) : 0; }
        /**
         * \brief 定时器检查
         * \param cur   检查定时器的时间
         * \return 是否到达指定时间
         */
        inline bool operator()(const Time &cur);

    private:
        /**
         * \brief 定时器时间间隔
         */
        unsigned long _long;
        /**
         * \brief 上次检查定时器的时间
         */
        Time _timer;

    private:
        /**
         * \brief
         * 严格监测需求并不是必须，用的不多，出于效率的考虑，去掉对定时器间隔严格监测的支持
         *
         */
        /**
         * \brief 非严格检测，存在积累误差
         *
         */
        inline void addDelay(const Time &cur);
};

#endif
