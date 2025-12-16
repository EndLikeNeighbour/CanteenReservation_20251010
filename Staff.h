#ifndef STAFF_H
#define STAFF_H

#include <string>
#include "user.h"
#include "Restaurant.h"
#include "Reservation.h"
#include "Table.h"

class Staff
{
protected:  // Protected members: accessible by subclass Manager
    StaffInfo staffInfo;         // Staff basic information (ID, name, position, etc.)
    Restaurant* restaurant; // Restaurant to which the staff belongs (operate restaurant resources)

public:
    // Constructor: Initialize staff information and affiliated restaurant
    Staff(const StaffInfo& staffInfo, Restaurant* res);

    // Virtual destructor: support polymorphism
    virtual ~Staff() = default;

    // Staff login (verify by staff ID)
    bool login(const std::string& staffId) const;

    // Confirm reservation (change reservation status to "Confirmed")
    bool confirmReservation(const std::string& reservationId);

    // Reject reservation (change reservation status to "Rejected", and release table)
    bool rejectReservation(const std::string& reservationId);

    // Mark customer arrival (update table status to "Occupied")
    bool markCustomerArrival(int tableId);

    // Mark customer departure (release table, update status to "Available")
    bool markCustomerDeparture(int tableId);

    // Handle walk-in customers (allocate table for customers without reservation)
    Table* handleWalkInCustomer(int partySize);

    // View all table statuses of the restaurant
    void viewAllTableStatus() const;

    // Get staff name
    std::string getName() const;

    // Get staff position
    std::string getPosition() const;
};

#endif // STAFF_H
