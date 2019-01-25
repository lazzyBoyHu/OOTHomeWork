#include <iostream>


#include "EventManager.h"
#include "person.h"
#include "CardReader.h"
#include "CarPark.h"
#include "Railing.h"


void Event::end(unsigned int uid)
{
    fire(uid);
}

void Event::fire(unsigned int uid)
{
    std::cout << "Event   user : " << uid << "   fire   --------     do something" << std::endl;
}

bool Event::checkFireTime(Time &current)
{
    return fireTime >= current;
}

void Event::checkErrorMessage(int flag, unsigned int uid, unsigned int tempCardId)
{
    if (flag < 0)
        switch(flag)
        {
            case -1 : std::cout << "查找不到该用户    :    uid  :  " << uid << std::endl;
                      break;
            case -2 : std::cout << "该用户没有ic卡    :    uid  :  " << uid << std::endl;
                      break;
            case -3 : std::cout << "没有carPark对象    " << std::endl;
                      break;
            case -4 : std::cout << "服务器中没有找到对应的卡片信息, 验证失败 uid : " << uid << ",    cardid : " << tempCardId << "   ;" << std::endl;
                      break;
            case -5 : std::cout << "没有找到对应的栏杆对象    :    uid    :    " << uid << std::endl;
                      break;
        }
}

void ReadCardEvent::begin(unsigned int uid)
{
    int flag = 1;
    Employee * emp = EmployeeManager::GetInstance()->GetOnePersonByID(uid);
    if (emp == nullptr)
        flag = NoEmployee;
    if (flag > 0 && emp->GetICCard() == nullptr)
        flag = NoICCard;
    CarPark * carPark = CarPark::GetInstance();
    if (carPark == nullptr)
        flag = NoCarPark;
    CardReader * cardReader = nullptr;
    if (flag > 0)
        cardReader = carPark->getCardReaderByType(emp->getOperateType());
    unsigned int tempCardId = cardReader->getICCardId(emp->GetICCard());
    ICCard * tempICCard = ICCardManager::GetInstance()->GetOneCardByCardId(tempCardId);
    if (tempICCard == nullptr)
        flag = NoICCardMessage;
    if (flag < 0)
        Event::checkErrorMessage(flag, uid, tempCardId);
        /*switch(flag)
        {
            case -1 : std::cout << "查找不到该用户    :    uid  :  " << uid << std::endl;
                      break;
            case -2 : std::cout << "该用户没有ic卡    :    uid  :  " << uid << std::endl;
                      break;
            case -3 : std::cout << "没有carPark对象    " << std::endl;
                      break;
            case -4 : std::cout << "服务器中没有找到对应的卡片信息, 验证失败 uid : " << uid << ",    cardid : " << tempCardId << "   ;" << std::endl;
                      break;
        }*/
    // 验证成功保存相关数据, 方便下一阶段使用
}

void RaiseRailingEvent::begin(unsigned int uid)
{
    int flag = 1;
    Employee * emp = EmployeeManager::GetInstance()->GetOnePersonByID(uid);
    if (emp == nullptr)
        flag = NoEmployee;

    CarPark * carPark = CarPark::GetInstance();
    if (flag > 0 && carPark == nullptr)
        flag = NoCarPark;
    Railing * railing = carPark->getRailingByType(emp->getOperateType());
    if (flag > 0)
    {
        if (railing == nullptr)
            flag = NoRailing;
        else
            if (!railing->isRaised())
                railing->raiseRailing();
    }
    else
    {
        Event::checkErrorMessage(flag, uid);
    }
}

void DownRailingEvent::begin(unsigned int uid)
{
    int flag = 1;
    Employee * emp = EmployeeManager::GetInstance()->GetOnePersonByID(uid);
    if (emp == nullptr)
        flag = NoEmployee;

    CarPark * carPark = CarPark::GetInstance();
    if (flag > 0 && carPark == nullptr)
        flag = NoCarPark;
    Railing * railing = carPark->getRailingByType(emp->getOperateType());
    if (flag > 0)
    {
        if (railing == nullptr)
            flag = NoRailing;
        else
            if (railing->isRaised())
                railing->downRailing();
    }
    else
    {
        Event::checkErrorMessage(flag, uid);
    }
}

EventManager::EventManager()
{
    eventMap.clear();
}

EventManager * EventManager::GetInstance()
{
    if (instance == nullptr)
    {
        EventManager();
        instance = this;
    }
    return instance;
}

void EventManager::checkFire(Time &current)
{
    auto iter = eventMap.begin();
    auto iterEnd = eventMap.end();
    while (iter != iterEnd)
        if (iter->second->checkFireTime(current))
            iter->second->end(iter->first);
}

void EventManager::addEvent(unsigned int uid, Event * event)
{
    eventMap[uid] = event;
}

void EventManager::removeEvent(unsigned int uid)
{
    auto iter = eventMap.find(uid);
    auto iterEnd = eventMap.end();
    if (iter != iterEnd)
        eventMap.erase(iter);
}
