#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H

#include "Customer.h"
#include <unordered_map>
#include <string>

/**
 * @brief Customer Manager - Responsible for managing and reusing customer objects
 * @details Use singleton pattern to ensure only one instance globally
 */
class CustomerManager
{
private:
    static CustomerManager* instance;
    std::unordered_map<std::string, Customer*> customers; // key: phone number

public:
    /**
     * @brief Get singleton instance of CustomerManager
     */
    static CustomerManager* getInstance();

    /**
     * @brief Find customer by phone number
     * @param phone Customer phone number
     * @return Return Customer pointer if found, otherwise return nullptr
     */
    Customer* findCustomerByPhone(const std::string& phone);

    /**
     * @brief Add new customer to manager
     * @param customer Customer object to add
     */
    void addCustomer(Customer* customer);

    /**
     * @brief Clean up all customer objects
     */
    void cleanup();

private:
    CustomerManager() = default;  // Private constructor
    ~CustomerManager() = default;
};

#endif // CUSTOMER_MANAGER_H
#pragma once
