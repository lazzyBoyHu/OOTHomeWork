#include <iostream>
#include <vector>


#include "Manager.h"
#include "ICCardMManageSystem.h"


ICCardManager * ICCardManager::GetInstance()
{
    return instance;
}

bool ICCardManager::AddOneCard(ICCard * card)
{
    if (card == nullptr)
        return false;
    manager->AddItem(card->GetId(), card);
    return true;
}

ICCard * ICCardManager::GetOneCardByCardId(unsigned int id)
{
    return manager->GetItem(id);
}

// ICCard管理器初始化
int ICCardManager::InitICCard()
{
    // 获取数据库的连接
    // 查找所有的数据
    // 遍历所有数据, 并生成对象
    // 并生成所有对象
    std::vector<ICCard> vec;
    /*
       ICCard *temp = new ICCard();
       if (temp == nullptr)
       continue;
       vec.push_back(temp);
       */
    manager->InitItem(&vec);
    return MANAGERINIT_SUCCESS;
}

/**
 */
bool RealICCard::setOwner(Employee * emp)
{
    ICCardManager * instance = ICCardManager::GetInstance();
    if (instance == nullptr)
        return false;
    ICCard * temp = instance->GetOneCardByCardId(i_icCard_id);
    if (emp == nullptr)
        return false;
    if (temp == nullptr)
        return false;
    if (i_icCard_id != temp->GetId())
        return false;
    owner = emp;
    return true;
}
