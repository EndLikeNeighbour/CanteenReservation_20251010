// File name: Reservation.cpp
#include "Reservation.h"
#include <ctime>  // Used for generating unique ID (based on time)

// Constructor: Generate unique reservation ID (format "RES+date+sequence number", simplified to timestamp here)
Reservation::Reservation(const CustomerInfo& info, const std::string& dt, int size, const std::string& req): customerInfo(info), dateTime(dt), partySize(size), specialRequest(req), status("Pending")
{
    // Generate simple unique ID (use UUID or database auto-increment ID in actual projects)
    time_t now = time(nullptr);
    reservationId = std::to_string(now);
}

// Get reservation ID
std::string Reservation::getReservationId() const
{
    return reservationId;
}

// Get customer name
std::string Reservation::getCustomerName() const
{
    return customerInfo.name;
}

// Get customer phone number
std::string Reservation::getCustomerPhone() const
{
    return customerInfo.phone;
}

// Modify special requests
void Reservation::modifyRequest(const std::string& newReq)
{
    specialRequest = newReq;
}

// Cancel reservation
void Reservation::cancelReservation()
{
    status = "Cancelled";
}

// Reject reservation
void Reservation::rejectReservation()
{
    status = "Rejected";
}

// Confirm reservation
void Reservation::confirmReservation()
{
    status = "Confirmed";
}

// Get status
std::string Reservation::getStatus() const
{
    return status;
}

// Get reservation time
std::string Reservation::getDateTime() const
{
    return dateTime;
}

// Get number of diners
int Reservation::getPartySize() const
{
    return partySize;
}
