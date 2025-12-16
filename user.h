#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>

struct FoodItem
{
    std::string foodName;
    double foodPrice;
    std::string category;
    bool IsAvailable;
};
struct CustomerInfo
{
    std::string name;
    std::string phone;
};
struct StaffInfo
{
    std::string staffId;  // Staff ID (unique identifier)
    std::string name;     // Name
    std::string position; // Position ("Staff" or "Manager")
    std::string phone;    // Contact phone number
};

#endif //!USER_H
