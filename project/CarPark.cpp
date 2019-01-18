#include <iostream>


#include "CarPark.h"
#include "CardReader.h"


CarPark::CarPark(int cardport)
{
    if (!initCarPark(cardport))
        destroyCarPark();
}

CarPark::~CarPark()
{
    destroyCarPark();
}

bool CarPark::initCarPark(int cardport)
{
    m_carport = cardport;
    CardReader * tempCardReader = nullptr;

    tempCardReader = new CardReader(CardReaderType::CardReaderType_Front);
    if (tempCardReader == nullptr)
        return false;
    m_twoCardRead[0] = tempCardReader;

    tempCardReader = new CardReader(CardReaderType::CardReaderType_Back);
    if (tempCardReader == nullptr)
        return false;
    m_twoCardRead[1] = tempCardReader;

    Railing * tempRailing = nullptr;

    tempRailing = new Railing(RailingType::RailingType_Front);
    if (tempRailing == nullptr)
        return false;
    m_twoRailing[0] = tempRailing;

    tempRailing = new Railing(RailingType::RailingType_Back);
    if (tempRailing == nullptr)
        return false;
    m_twoRailing[1] = tempRailing;

    cardportStatus = new bool[m_carport * 2];
    if (cardportStatus == nullptr)
        return false;

    return true;
}

void CarPark::destroyCarPark()
{
    for (int i = 0; i < 2; ++i)
        if (m_twoCardRead[i] != nullptr)
            delete m_twoCardRead[i];

    for (int i = 0; i < 2; ++i)
        if (m_twoRailing[i] != nullptr)
            delete m_twoRailing[i];

    if (cardportStatus != nullptr)
        delete [] cardportStatus;
}

CarPark * CarPark::GetInstance(int carport)
{
    if (carport <=0 )
        return nullptr;
    if (instance == nullptr)
        instance = new CarPark(carport);
    return instance;
}

CardReader * CarPark::getCardReaderByType(int type)
{
    if (type == PeopleOperateType::PeopleOperateType_Stop)
        return m_twoCardRead[0];
    else if (type == PeopleOperateType::PeopleOperateType_Leave)
        return m_twoCardRead[1];
    else
        return nullptr;
}
