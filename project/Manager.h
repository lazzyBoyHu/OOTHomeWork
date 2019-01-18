#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <map>
#include <vector>

/**
 * 定义一个单例管理器类, 用于管理每种对象的集合
 * 用instance来代表这个单例对象
 * manager为一个map, 用于保存这一组需要管理的对象, map的键表示这个对象的索引, 后边的值指这个变量
 */
template <typename T>
class Manager
{
    private:
        std::map<unsigned int, T*> manager;

    public:
        Manager();
        virtual ~Manager();
    private:
        Manager(const Manager<T>&) {}
        Manager<T>& operator=(const Manager<T>&){}

    public:
        void InitItem(std::vector<T> * items);
        void AddItem(unsigned int id, T * item);
        T * GetItem(unsigned int id);
    private:
        void CleanManager();
        std::string GetName();
        void AddOnePerson();
        Employee * GetOnePersonByID();
};

#endif
