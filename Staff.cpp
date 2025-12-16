// File name: Staff.cpp
#include "Staff.h"
#include <iostream>

// Constructor
Staff::Staff(const StaffInfo& staffInfo, Restaurant* res) : staffInfo(staffInfo), restaurant(res) {}

// Login verification (match staff ID)
bool Staff::login(const std::string& staffId) const
{
    return staffInfo.staffId == staffId;
}

// Confirm reservation (find table by reservation ID -> update status)
bool Staff::confirmReservation(const std::string& reservationId)
{
    // Traverse all restaurant tables to find reservation
    for (Table* table : restaurant->getTables())
    {
        Reservation* res = table->getCurrentReservation();
        if (res && res->getReservationId() == reservationId)
        {
            res->confirmReservation();
            std::cout << "Reservation " << reservationId << " has been confirmed (Table " << table->getTableId() << ")" << std::endl;
            return true;
        }
    }
    std::cerr << "Confirmation failed: Reservation ID " << reservationId << " not found" << std::endl;
    return false;
}

// Reject reservation (release table)
bool Staff::rejectReservation(const std::string& reservationId)
{
    for (Table* table : restaurant->getTables())
    {
        Reservation* res = table->getCurrentReservation();
        if (res && res->getReservationId() == reservationId)
        {
            res->rejectReservation();
            table->removeReservation();  // Disassociate table, table becomes available
            std::cout << "Reservation " << reservationId << " has been rejected (Table " << table->getTableId() << " released)" << std::endl;
            return true;
        }
    }
    std::cerr << "Rejection failed: Reservation ID " << reservationId << " not found" << std::endl;
    return false;
}

// Mark customer arrival (table status becomes "occupied")
bool Staff::markCustomerArrival(int tableId) {
    Table* table = restaurant->findTableById(tableId);
    if (!table)
    {
        std::cerr << "Error: Table ID " << tableId << " does not exist" << std::endl;
        return false;
    }
    if (table->isTableAvailable())
    {
        std::cerr << "Error: Table " << tableId << " is currently free, no need to mark arrival" << std::endl;
        return false;
    }
    std::cout << "Customer has arrived, Table " << tableId << " marked as occupied" << std::endl;
    return true;
}

// Mark customer departure (table becomes available)
bool Staff::markCustomerDeparture(int tableId)
{
    Table* table = restaurant->findTableById(tableId);
    if (!table)
    {
        std::cerr << "Error: Table ID " << tableId << " does not exist" << std::endl;
        return false;
    }
    if (table->isTableAvailable())
    {
        std::cerr << "Error: Table " << tableId << " is already free" << std::endl;
        return false;
    }
    table->removeReservation();  // Disassociate reservation
    table->setAvailability(true);  // Mark as available
    std::cout << "Customer has left, Table " << tableId << " is available again" << std::endl;
    return true;
}

// Handle walk-in customers (allocate available table)
Table* Staff::handleWalkInCustomer(int partySize)
{
    if (partySize <= 0)
    {
        std::cerr << "Error: Number of diners must be a positive integer" << std::endl;
        return nullptr;
    }
    Table* table = restaurant->findAvailableTable(partySize);
    if (table)
    {
        table->setAvailability(false);  // Mark as occupied (no reservation)
        std::cout << "Walk-in customer seated, Table " << table->getTableId() << " (Capacity: " << table->getCapacity() << " people)" << std::endl;
        return table;
    }
    std::cerr << "No available tables, cannot arrange walk-in customers (Number of people: " << partySize << ")" << std::endl;
    return nullptr;
}

// View all table statuses
void Staff::viewAllTableStatus() const
{
    std::cout << "\n===== " << restaurant->getName() << " Table Status =====" << std::endl;
    for (const Table* table : restaurant->getTables())
    {
        std::cout << "Table ID: " << table->getTableId() << ", Capacity: " << table->getCapacity()
        << " people, Location: " << table->getLocation() << ", Status: "
        << (table->isTableAvailable() ? "[Free]" : "[Occupied/Reserved]");
    }
    std::cout << std::endl;
}

// Get staff name
std::string Staff::getName() const
{
    return staffInfo.name;
}

// Get staff position
std::string Staff::getPosition() const
{
    return staffInfo.position;
}
