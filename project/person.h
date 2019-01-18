#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>

#include "ICCardMManageSystem.h"
#include "Manager.h"

enum PeopleOperateType
{
    PeopleOperateType_None,     // 什么也不干
    PeopleOperateType_Stop,     // 停车
    PeopleOperateType_Leave,    // 离开
};

class Person
{
    private:
        std::string p_name;
        int p_operateType;
    public:
        Person(std::string name, int operateType = PeopleOperateType_None) : p_name(name), p_operateType(operateType) {}
        void setName(std::string name) { p_name = name; }
        std::string getName() { return p_name; }
        int getOperateType() { return p_operateType; }
        void stopCar() {}
        void driveLeave() {}
};

enum Employee_Type
{
    Employee_Normal         = 0,
    Employee_ParkManager    = 1,
};

class Employee : public Person
{
    private:
        std::string e_company_name;
        unsigned int e_company_id;
        unsigned int e_employee_id;
        RealICCard * e_icCard = nullptr;
    protected:
        unsigned int e_employer_type;
    public:
        Employee(std::string name, std::string company_name, unsigned int company_id, unsigned int employee_id) : Person(name), e_company_name(company_name), e_company_id(company_id), e_employee_id(employee_id) {e_employer_type = Employee_Normal;}
        unsigned int GetId(){return e_employee_id;}
        bool SetRealICCard(RealICCard * rIcCard);
        RealICCard * GetICCard() { return e_icCard; }
};

class ParkManger : public Employee
{
    private:
        void ChangeICCardState(ICCard * icCard,int state) {icCard->i_state = state;}
        void SetEmployeeType() {e_employer_type = Employee_ParkManager;}
    public:
        ParkManger(std::string name, std::string company_name, unsigned int company_id, unsigned int employee_id) : Employee(name, company_name, company_id, employee_id) {SetEmployeeType();}
};

class EmployeeManager : Manager<Person>
{
    private:
        static EmployeeManager * employee_instance;
        Manager<Employee> * p_manager;
        std::string p_name;
    private:
        EmployeeManager() : p_name("person manager") {p_manager = new Manager<Employee>();}
    public:
        static EmployeeManager * GetInstance();
        std::string GetName();
        int EmployeeManagerInit();
        bool AddOneEmployee(Employee * emp);
        Employee * GetOnePersonByID(unsigned int id);
};

#endif
