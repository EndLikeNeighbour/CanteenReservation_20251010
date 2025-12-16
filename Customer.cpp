// File name: Customer.cpp
#include "Customer.h"
#include <iostream>
#include <algorithm>  // Used for finding reservation records

// Constructor
Customer::Customer(const CustomerInfo& customerInfo) : info(customerInfo) 
{
}

// Destructor: Release all personal reservation records
Customer::~Customer() 
{
}

// Login verification (match phone number)
bool Customer::login(const std::string& inputPhone) const 
{
    return info.phone == inputPhone;
}

// Make a reservation (Core logic: Find available table -> Create reservation -> Associate with table)
std::string Customer::makeReservation(Restaurant* restaurant, const std::string& dateTime, int partySize, const std::string& specialRequest, const std::string& preferredLocation) {
    if (partySize <= 0) 
    {
        std::cerr << "Error: Number of diners must be a positive integer" << std::endl;
        return "";
    }
    if (dateTime.empty()) 
    {
        std::cerr << "Error: Please select a reservation time" << std::endl;
        return "";
    }

    // Step 1: Find available table through restaurant
    Table* availableTable = restaurant->findAvailableTable(partySize, preferredLocation);
    if (availableTable == nullptr) 
    {
        std::cerr << "Reservation failed: No available tables (Number of people: " << partySize << ", Time: " << dateTime << ")" << std::endl;
        return "";
    }

    // Step 2: Create reservation object
    Reservation* newReservation = new Reservation(info, dateTime, partySize, specialRequest);

    // Step 3: Associate reservation with table (table status becomes unavailable)
    availableTable->setReservation(newReservation);

    reservations.push_back(newReservation);

    std::cout << "Reservation successful! Reservation ID: " << newReservation->getReservationId()<< ", Table ID: " << availableTable->getTableId() << std::endl;
    return newReservation->getReservationId();
}

// Cancel reservation (find and delete by reservation ID)
bool Customer::cancelReservation(const std::string& reservationId)
{
    auto it = std::find_if(reservations.begin(), reservations.end(),[&](Reservation* res) { return res->getReservationId() == reservationId; });

    if (it != reservations.end()) 
    {
        Reservation* resToCancel = *it;
        // Step 1: Modify reservation status to "Cancelled"
        resToCancel->cancelReservation();
        // Step 2: Remove from personal records (Note: Reservation in table is released by Table destructor, only delete pointer here)
        reservations.erase(it);
        delete resToCancel;  // Release reservation object
        std::cout << "Reservation " << reservationId << " has been cancelled" << std::endl;
        return true;
    }
    std::cerr << "Cancellation failed: Reservation ID " << reservationId << " not found" << std::endl;
    return false;
}

// View personal reservation records
void Customer::viewReservations() const 
{
    if (reservations.empty()) 
    {
        std::cout << "You have no reservation records" << std::endl;
        return;
    }

    std::cout << "\n===== " << info.name << "'s Reservation Records =====" << std::endl;
    for (const Reservation* res : reservations) 
    {
        std::cout << "预订ID: " << res->getReservationId() << "\n"
                  << "时间: " << res->getDateTime() << "\n"
                  << "就餐人数: " << res->getPartySize() << "\n"
                  << "状态: " << res->getStatus() << "\n"
                  << "特殊需求: " << res->getCustomerRequest() << "\n" << std::endl;
    }
}

// Get customer name
std::string Customer::getName() const 
{
    return info.name;
}

// Get customer phone number
std::string Customer::getPhone() const 
{
    return info.phone;
}

// Update personal information
void Customer::updateInfo(const CustomerInfo& newInfo) 
{
    info = newInfo;
    std::cout << "Personal information updated successfully" << std::endl;
}
