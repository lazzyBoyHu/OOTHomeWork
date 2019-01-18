#ifndef SEVERTASKTICK_H_
#define SEVERTASKTICK_H_

#include <thread>
#include <memory>
#include <functional>
#include <iostream>
#include <mutex>

#include "timer/timer.h"

#define CHECKPRECISION 500  // 定义定时器检查精度

class SeverTimer
{
    private:
        /**
         * 一秒定时器
         */
        Timer _one_sec;
        /**
         * 对象指针
         */
        SeverTimer * instance;
        /**
         * 当前时间
         */
        static Time currentTime;
    public:
        /**
         * 线程函数
         */
        void run();
        /**
         * 一秒定时器处理函数
         */
        void dealOneSec();
        /**
         * 获取对象
         */
        SeverTimer * GetInstance();
        /**
         * 析构函数
         */
        ~SeverTimer();
    private:
        SeverTimer();
        std::shared_ptr<std::thread> timerThread;
        bool isFinalStop;   // 服务器停机标志, 当服务器请求停机时, 停止定时器
};

#endif
