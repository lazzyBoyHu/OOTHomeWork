#include <iostream>


#include "EventManager.h"
#include "person.h"
#include "CardReader.h"
#include "CarPark.h"


void Event::end(unsigned int uid)
{
    fire(uid);
}

void Event::fire(unsigned int uid)
{
    std::cout << "Event   user : " << uid << "   fire   --------     do something" << std::endl;
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
        }
    // 验证成功保存相关数据, 方便下一阶段使用
}

void RaiseRailingEvent::begin(unsigned int uid)
{
    int flag = 1;
    Employee * emp = EmployeeManager::GetInstance()->GetOnePersonByID(uid);
    if (emp == nullptr)
        flag = NoEmployee;
}
