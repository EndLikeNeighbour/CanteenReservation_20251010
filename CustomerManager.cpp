// File name: CustomerManager.cpp
#include "CustomerManager.h"

// Static member variable initialization
CustomerManager* CustomerManager::instance = nullptr;

CustomerManager* CustomerManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CustomerManager();
    }
    return instance;
}

Customer* CustomerManager::findCustomerByPhone(const std::string& phone)
{
    auto it = customers.find(phone);
    if (it != customers.end())
    {
        return it->second;  // Return existing customer object
    }
    return nullptr;  // No corresponding customer found
}

void CustomerManager::addCustomer(Customer* customer)
{
    std::string phone = customer->getPhone();
    customers[phone] = customer;
}

void CustomerManager::cleanup()
{
    for (auto& pair : customers)
    {
        delete pair.second;  // Release customer object
    }
    customers.clear();
}
