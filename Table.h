#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "Reservation.h"  // Dependent on Reservation class (a table can be associated with a reservation)

class Table
{
private:
    int tableId;               // Table ID (unique, e.g., 1, 2, 3)
    int capacity;              // Capacity (maximum number of diners)
    std::string location;      // Location (e.g., "Window Side", "Private Room A")
    bool isAvailable;          // Availability (true=Free, false=Occupied/Reserved)
    Reservation* currentRes;   // Currently associated reservation (nullptr=No reservation)

public:
    // Constructor (initial status is available, no reservation)
    Table(int id, int cap, const std::string& loc);//capacity location

    // Destructor: Release current reservation object
    ~Table();

    // Get table ID
    int getTableId() const;

    // Get capacity
    int getCapacity() const;

    // Get availability
    bool isTableAvailable() const;

    // Set availability (called by Staff, e.g., mark as available after customer leaves)
    void setAvailability(bool available);

    // Associate reservation (table becomes unavailable after successful reservation)
    void setReservation(Reservation* res);

    // Disassociate reservation (table becomes available after cancellation)
    void removeReservation();

    // Get current reservation (return nullptr if no reservation)
    Reservation* getCurrentReservation() const;

    // Get table location
    std::string getLocation() const;
};

#endif // TABLE_H
