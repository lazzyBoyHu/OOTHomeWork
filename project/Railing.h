#ifndef RAILING_H_
#define RAILING_H_


enum RailingType
{
    RailingType_Front,
    RailingType_Back,
};

enum RailingStatus
{
    RailingStatus_Raise,
    RailingStatus_Down,
};

class Railing
{
    private:
        int m_railingType;
        int m_status;
    public:
        Railing(int railingType, int status = RailingStatus_Raise);
        bool isRaised()
        {
            if (RailingStatus_Raise == m_status)
                return true;
            return false;
        }
        void raiseRailing()
        {
            m_status = RailingStatus_Raise;
        }
        void downRailing()
        {
            m_status = RailingStatus_Down;
        }
};

#endif
