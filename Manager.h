#ifndef MANAGER_H
#define MANAGER_H

#include "Staff.h"
#include "user.h"  // FoodItem structure (split from common.h)

class Manager : public Staff
{
public:
    // Constructor: Reuse Staff constructor, position fixed as "Manager"
    Manager(StaffInfo& staffInfo, Restaurant* res);

    // Extended function: Add new table (restaurant expansion)
    void addNewTable(int tableId, int capacity, const std::string& location);

    // Extended function: Remove table (restaurant downsizing)
    bool removeTable(int tableId);

    // Extended function: Update menu (add/modify/delete dishes)
    void updateMenu(const FoodItem& item, bool isAdd);
    bool modifyMenuItem(const std::string& foodName, double newPrice, bool newAvailability);

    // Extended function: Generate reservation report (statistics by date)
    void generateReservationReport(const std::string& date) const;

    // Extended function: View business statistics (dish sales, table usage rate, etc., simplified version)
    void viewBusinessStats() const;
};

#endif // MANAGER_H
