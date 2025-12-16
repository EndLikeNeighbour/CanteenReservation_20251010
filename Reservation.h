#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include "user.h"

class Reservation
{
private:
    std::string reservationId;  // Reservation ID (unique, e.g., "RES20251010001")
    CustomerInfo customerInfo;  // Customer information (name, phone, etc.)
    std::string dateTime;       // Reservation time (format "YYYY-MM-DD HH:MM")
    int partySize;              // Number of diners
    std::string specialRequest; // Special requests (e.g., "window side seat")
    std::string status;         // Status ("Pending"/"Confirmed"/"Cancelled"/"Rejected")
    std::string customerRequest;

public:
    // Constructor (generate reservation ID, default status is Pending)
    Reservation(const CustomerInfo& info, const std::string& dt, int size, const std::string& req);

    // Get reservation ID
    std::string getReservationId() const;

    // Get customer name (encapsulate customerInfo.name)
    std::string getCustomerName() const;

    // Get customer phone number (encapsulate customerInfo.phone)
    std::string getCustomerPhone() const;

    // Modify special requests
    void modifyRequest(const std::string& newReq);

    // Cancel reservation (modify status to Cancelled)
    void cancelReservation();

    // Reject reservation (modify status to Rejected, called by Staff)
    void rejectReservation();

    // Confirm reservation (modify status to Confirmed, called by Staff)
    void confirmReservation();

    // Get current status
    std::string getStatus() const;

    // Get reservation time
    std::string getDateTime() const;

    // Get number of diners
    int getPartySize() const;

    std::string getCustomerRequest() const
    {
        return customerRequest;
    }
};

#endif // RESERVATION_H
