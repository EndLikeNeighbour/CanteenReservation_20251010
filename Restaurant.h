#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>
#include "Table.h"
#include "Menu.h"
#include <vector>
#include "Reservation.h"

class Restaurant
{
private:
    std::string name;               // Restaurant name
    std::string address;            // Restaurant address
    std::vector<Table*> tables;     // Aggregate tables (a restaurant contains multiple tables)
    Menu* menu;                     // Aggregate menu (a restaurant has one menu)
    std::vector<Reservation*> reservations;

public:
    // Constructor: Initialize restaurant information, menu and default tables
    Restaurant(const std::string& resName, const std::string& resAddr);

    // Destructor: Release all table and menu objects
    ~Restaurant();

    // Add table (called by Manager, expand restaurant capacity)
    void addTable(Table* table);

    // Remove table (called by Manager, e.g., table damaged)
    bool removeTable(int tableId);

    // Find table by ID (used for customer reservation, staff management)
    Table* findTableById(int tableId) const;

    // Find available table by capacity and availability (match suitable table for reservation)
    Table* findAvailableTable(int partySize, const std::string& preferredLocation = "") const;

    // Get all tables (for UI to display table statuses)
    std::vector<Table*> getTables() const;

    // Get menu (customers view menu, staff/manager modify menu)
    Menu* getMenu() const;

    // Get restaurant name
    std::string getName() const;

    // Get restaurant address
    std::string getAddress() const;

};

#endif // RESTAURANT_H
