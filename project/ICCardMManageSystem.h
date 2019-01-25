#ifndef ICCARDMANAGE_H_
#define ICCARDMANAGE_H_

#include <iostream>

#include "Manager.h"
#include "person.h"
#include "CardReader.h"

// ic卡状态枚举
enum ICCard_State
{
    Nonactivated    = -1,   // 当员工处于离职等异常状态下
    HaveStopCar     = 0,    // 已经有车停在停车场
    CanStopCar      = 1,    // 可以停车
};
// 管理器初始化异常
enum MANAGERINIT_ERROR
{
    MANAGERINIT_SUCCESS      = 1,    // 管理器初始化成功
    MANAGERINIT_DBLINK_ERROR  = 2,    // 管理器初始化数据库连接错误
    MANAGERINIT_INQURE_ERROR  = 3,    // 管理器出事化数据库查询失败
};

// ic卡类, 在服务器上的类, 保存所有的ic卡信息.
class ICCard
{
    private:
        static unsigned int Max_ic_card_id; // 保存最大的一个ID, 便于生成下一个ICCard的ID
    private:
        unsigned int i_icCard_id;   // ic卡ID, ic卡的唯一标识
        unsigned int i_company_id;  // 公司id
        unsigned int i_owner_id;    // 拥有者ID, 即员工的ID
        int i_state;                // ic卡当前所处的状态;
        friend class ParkManger;    // 友元类ParkManger, 用于在异常状态下改变状态
    public:
        ICCard(unsigned int icCard_id, unsigned int company_id, unsigned int owner_id) : i_icCard_id(icCard_id), i_company_id(company_id), i_owner_id(owner_id) { i_state = Nonactivated;}
        bool CheckActivateState() {return i_state < 0 ? false : true;}
        bool CheckStopCar() {return i_state == CanStopCar ? true : false;}
        bool CheckDriveCar() {return i_state == HaveStopCar ? true : false;}
        unsigned int GetId() {return i_icCard_id;}
        unsigned int GetCompanyId() {return i_company_id;}
        unsigned int GetOwnerId() {return i_owner_id;}
};

// 用于模拟一张真实的ic卡
class RealICCard
{
    private:
        unsigned int i_icCard_id;   // ic卡ID, ic卡的唯一标识, 该ID与ICCard的i_icCard_id相同
        Employee * owner;   // RealICCard的所有者
        friend class CardReader;
    protected:
        unsigned int GetId() {return i_icCard_id;}
    public:
        RealICCard(unsigned int icCard_id) : i_icCard_id(icCard_id) {}
        bool setOwner(Employee * emp);
};

class ICCardManager
{
    private:
        static ICCardManager * instance;
        std::string name;
    private:
        ICCardManager() : name("ic card manager") {}
    public:
        static ICCardManager * GetInstance();
        std::string GetName() {return name;}
        bool AddOneCard(ICCard * card);
        ICCard * GetOneCardByCardId(unsigned int id);
        int InitICCard();
};

#endif
