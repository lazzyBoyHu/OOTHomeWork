#ifndef CARDREADER_H_
#define CARDREADER_H_

#include <iostream>

#include "ICCardMManageSystem.h"

enum CardReaderType
{
    CardReaderType_Front,
    CardReaderType_Back,
};

enum CardReaderErrorNum
{
    NoICCard = -1,
};

class CardReader
{
    private:
        int m_type;
    public:
        CardReader(int type) : m_type(type) { }
        ~CardReader() { }
        long getICCardId(RealICCard * realCard)
        {
            if (realCard == nullptr)
                return NoICCard;

            return realCard->GetId();
        }
};

#endif
