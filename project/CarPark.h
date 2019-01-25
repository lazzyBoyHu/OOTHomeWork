#ifndef CARPARK_H_
#define CARPARK_H_

#include <iostream>


#include "CardReader.h"
#include "Railing.h"
#include "Sensor.h"

#define HALF_MAX 10

class CarPark
{
    private:
        CardReader* m_twoCardRead[2];
        Railing* m_twoRailing[2];
        Sensor* m_twoSensor[2];
        int m_carport;
        bool * cardportStatus = nullptr;
        static CarPark * instance;
    public:
        ~CarPark();
        static CarPark * GetInstance(int carport = HALF_MAX);
        CardReader * getCardReaderByType(int type);
        Railing * getRailingByType(int type);
        Sensor * getSensorByType(int type);
    private:
        CarPark(int cardport = HALF_MAX);
        bool initCarPark(int cardport);
        void destroyCarPark();
};



#endif
