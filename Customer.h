#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "user.h"
#include "Reservation.h"
#include "Restaurant.h"

class Customer {
private:
    CustomerInfo info;                      // Customer basic information (name, phone, email, etc.)
    std::vector<Reservation*> reservations; // Personal reservation records (a customer can have multiple reservations)

public:
    // Constructor: Initialize customer through info structure
    Customer(const CustomerInfo& customerInfo);

    // Destructor: Release personal reservation records
    ~Customer();

    // Login verification (simplified version: verify by phone number, connect to database in actual projects)
    bool login(const std::string& phone) const;

    // Personal information acquisition methods

    // Make a reservation (Core function: Request reservation from restaurant, return reservation ID or empty string)
    std::string makeReservation(Restaurant* restaurant, const std::string& dateTime, int partySize, const std::string& specialRequest, const std::string& preferredLocation = "");

    // Cancel reservation (cancel by reservation ID)
    bool cancelReservation(const std::string& reservationId);

    // View all personal reservations
    void viewReservations() const;

    // Get customer name
    std::string getName() const;

    // Get customer phone number (unique identifier)
    std::string getPhone() const;

    // Update personal information
    void updateInfo(const CustomerInfo& newInfo);

    // New: Get personal reservation records
    std::vector<Reservation*> getReservations() const { return reservations; }

    // New: Add reservation to personal records
    void addPersonalReservation(Reservation* res) { reservations.push_back(res); }
};

#endif // CUSTOMER_H
