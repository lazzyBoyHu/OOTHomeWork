#include "Manager.h"

/**
 * 构造函数
 * 创建时调用清除函数
 */
template <typename T>
Manager<T>::Manager()
{
    CleanManager();
}

/**
 * 析构函数
 */
template <typename T>
Manager<T>::~Manager<T>()
{
}

/**
 * 在创建时需要对这个map进行清空, 以免出现数据问题
 */
template <typename T>
void Manager<T>::CleanManager()
{
    manager.clean();
}

/**
 * 起服时初始化所有管理器中的数据
 * 数据来源于数据库或者其他的存储
 * 由于我不想去改原来的代码, 为了兼容这个实现每个T类中都需要一个 GetId() 函数;
 * 好的实现方法应该是, 项目中使用的类应该都有一个公共的基类, 在基类中实现这个函数
 */
template <typename T>
void Manager<T>::InitItem(std::vector<T> * items)
{
    if (items != nullptr)
    {
        auto it = items->begin();
        auto itEnd = items->end();
        for (; it != itEnd; it++)
            AddItem(it->GetId(), it);
    }
}

/**
 * 添加项目
 */
template <typename T>
void Manager<T>::AddItem(unsigned int id, T * item)
{
    manager.insert(std::pair<unsigned int, T*>(id, item));
}

/**
 * 获取元素
 */
template <typename T>
T * Manager<T>::GetItem(unsigned int id)
{
    if (manager[id] != nullptr)
        return manager[id];
    return nullptr;
}
