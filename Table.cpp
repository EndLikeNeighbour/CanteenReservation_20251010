// File name: Table.cpp
#include "Table.h"

// Constructor
Table::Table(int id, int cap, const std::string& loc)
    : tableId(id), capacity(cap), location(loc), isAvailable(true), currentRes(nullptr)
{
}

// Destructor: Release current reservation object
Table::~Table()
{
    if (currentRes != nullptr)
    {
        delete currentRes;
        currentRes = nullptr;
    }
}

// Get table ID
int Table::getTableId() const
{
    return tableId;
}

// Get capacity
int Table::getCapacity() const
{
    return capacity;
}

// Get availability
bool Table::isTableAvailable() const
{
    return isAvailable;
}

// Set availability
void Table::setAvailability(bool available)
{
    isAvailable = available;
}

// Associate reservation (table becomes unavailable after successful reservation)
void Table::setReservation(Reservation* res)
{
    if (currentRes != nullptr)
    {
        delete currentRes;  // Release old reservation (e.g., when modifying reservation)
    }
    currentRes = res;
    isAvailable = (res == nullptr);  // Unavailable if there is a reservation
}

// Disassociate reservation (table becomes available after cancellation)
void Table::removeReservation()
{
    if (currentRes != nullptr)
    {
        delete currentRes;
        currentRes = nullptr;
    }
    isAvailable = true;
}

// Get current reservation
Reservation* Table::getCurrentReservation() const
{
    return currentRes;
}

// Get table location
std::string Table::getLocation() const
{
    return location;
}
