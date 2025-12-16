// File name: Restaurant.cpp
#include "Restaurant.h"
#include "Customer.h"
#include "Reservation.h"
#include <iostream>
#include <algorithm>  // Used for finding tables (find_if)

// Constructor: Initialize restaurant name, address, create menu, and add default tables
Restaurant::Restaurant(const std::string& resName, const std::string& resAddr): name(resName), address(resAddr), menu(new Menu())
{
    // Add default tables (load from database in actual projects)
    tables.push_back(new Table(1, 4, "Window Side"));   // Table 1, 4 people, Window Side
    tables.push_back(new Table(2, 4, "Hall"));   // Table 2, 4 people, Hall
    tables.push_back(new Table(3, 6, "Private Room"));   // Table 3, 6 people, Private Room
    tables.push_back(new Table(4, 2, "Bar"));   // Table 4, 2 people, Bar
}

// Destructor: Release all tables and menu
Restaurant::~Restaurant()
{
    // Release tables
    for (Table* table : tables)
    {
        delete table;
    }
    tables.clear();
    // Release menu
    delete menu;
    menu = nullptr;
}

// Add table (Manager function)
void Restaurant::addTable(Table* table)
{
    // Check if table ID already exists
    if (findTableById(table->getTableId()) != nullptr)
    {
        std::cerr << "Error: Table ID " << table->getTableId() << " already exists, addition failed" << std::endl;
        delete table;  // Avoid memory leak
        return;
    }
    tables.push_back(table);
    std::cout << "Table " << table->getTableId() << " added successfully (Capacity: " << table->getCapacity() << " people, Location: " << table->getLocation() << ")" << std::endl;
}

// Remove table (Manager function)
bool Restaurant::removeTable(int tableId)
{
    auto it = std::find_if(tables.begin(), tables.end(),[tableId](Table* table) { return table->getTableId() == tableId; });
    if (it != tables.end())
    {
        Table* tableToRemove = *it;
        tables.erase(it);
        delete tableToRemove;  // Release table object
        std::cout << "Table " << tableId << " has been removed" << std::endl;
        return true;
    }
    std::cerr << "Error: Table ID " << tableId << " does not exist, removal failed" << std::endl;
    return false;
}

// Find table by ID
Table* Restaurant::findTableById(int tableId) const
{
    for (Table* table : tables)
    {
        if (table->getTableId() == tableId)
        {
            return table;
        }
    }
    return nullptr;
}

// Find available table by capacity and location (core reservation logic)
Table* Restaurant::findAvailableTable(int partySize, const std::string& preferredLocation) const
{
    for (Table* table : tables)
    {
        // Condition 1: Table is available; Condition 2: Capacity >= number of diners; Condition 3: Location matches (optional)
        if (table->isTableAvailable() && table->getCapacity() >= partySize && (preferredLocation.empty() || table->getLocation() == preferredLocation))
        {
            return table;  // Return first matching table
        }
    }
    // If no location-matched table found, return any available table with sufficient capacity
    if (!preferredLocation.empty())
    {
        for (Table* table : tables)
        {
            if (table->isTableAvailable() && table->getCapacity() >= partySize)
            {
                return table;
            }
        }
    }
    return nullptr;  // No available tables
}

// Get all tables
std::vector<Table*> Restaurant::getTables() const
{
    return tables;
}

// Get menu
Menu* Restaurant::getMenu() const
{
    return menu;
}

// Get restaurant name
std::string Restaurant::getName() const
{
    return name;
}

// Get restaurant address
std::string Restaurant::getAddress() const
{
    return address;
}
