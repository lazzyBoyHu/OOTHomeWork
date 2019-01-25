#include <iostream>

#include "Manager.h"


class Server
{
    public:
        bool initServer();
        void destroyServer();
};




int main()
{
    /**
     * 获取一个server对象
     * 使用server对象进行初始化
     * 在初始化的过程中, 将加载所有的数据, 初始化所有的管理器
     */
    Server server;
    if (server.initServer())
    {
        // 主循环
        while(true)
        {
        }
    }
    server.destroyServer();
    return 0;
}
