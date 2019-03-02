#ifndef SENSOR_H_
#define SENSOR_H_

enum SensorType
{
    SensorType_Front,
    SensorType_Back,
};

enum SensorWorkStatus
{
    SensorWorkStatus_Work,
    SensorWorkStatus_Stop,
};

enum SensorSingalType
{
    SensorSingalType_None,
    SensorSingalType_Fired,
};

class Sensor
{
    private:
        int m_sensorType;
        int m_workStatus;       // 传感器的工作状态
        bool singal;            // 是否检测到信号
    public:
        Sensor(int sensorType) : m_sensorType(sensorType), m_workStatus(SensorWorkStatus_Stop) { }
        ~Sensor() {}

        void changeWorkStatus(int status)
        {
            m_workStatus = status;
        }
        // 通过定时器调用
        void work()
        {
            if (m_workStatus == SensorWorkStatus::SensorWorkStatus_Work)
            {
                // 等待车辆通过信号, 收到信号, 继续下一个事件
                if (singal)
                {
                    sendDownRailingMessage();
                    singal = false;
                }
            }
        }
        bool canWork()
        {
            if (m_workStatus == SensorWorkStatus::SensorWorkStatus_Work)
                return true;
            return false;
        }
        void sendDownRailingMessage()
        {
            // 如何通知事件管理器应该进行下一个事件
        }
};

#endif
