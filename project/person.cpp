#include <iostream>
#include <map>

#include "person.h"

bool Employee::SetRealICCard(RealICCard * rIcCard)
{
    ICCardManager * icCard_manager = ICCardManager::GetInstance();
    if (rIcCard == nullptr)
        return false;
    if (icCard_manager == nullptr)
        return false;

    ICCard * card = icCard_manager->GetOneCardByCardId(rIcCard->GetId());
    if (card == nullptr)
        return false;
    if (card->GetOwnerId() != this->e_employee_id)
        return false;
    return true;
}

EmployeeManager * EmployeeManager::GetInstance()
{
    if (employee_instance == nullptr)
        employee_instance = new EmployeeManager();
    return employee_instance;
}

std::string EmployeeManager::GetName()
{
    return p_name;
}

int EmployeeManager::EmployeeManagerInit()
{
    return 1;
}

bool EmployeeManager::AddOneEmployee(Employee * emp)
{
    if (emp == nullptr)
        return false;
    p_manager->AddItem(emp->GetId(), emp);
    return true;
}

Employee * EmployeeManager::GetOnePersonByID(unsigned int id)
{
    return p_manager->GetItem(id);
}
