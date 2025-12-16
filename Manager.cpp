// File name: Manager.cpp
#include "Manager.h"
#include <fstream>  // Used for generating report files
#include <iostream>
#include <iomanip>  // Used for formatted output

// Constructor: Call parent class Staff constructor, position fixed as "Manager"
Manager::Manager(StaffInfo& staffInfo, Restaurant* res) : Staff(staffInfo, res)
{
    staffInfo.position = "Manager";  // Force position to Manager
}

// Add new table
void Manager::addNewTable(int tableId, int capacity, const std::string& location)
{
    Table* newTable = new Table(tableId, capacity, location);
    restaurant->addTable(newTable);  // Call restaurant's add table method
}

// Remove table
bool Manager::removeTable(int tableId)
{
    return restaurant->removeTable(tableId);  // Call restaurant's remove table method
}

// Update menu (add/delete dishes)
void Manager::updateMenu(const FoodItem& item, bool isAdd)
{
    Menu* menu = restaurant->getMenu();
    if (isAdd)
    {
        menu->addFoodItem(item);  // Call Menu's add dish method
    }
    else
    {
        menu->removeFoodItem(item.foodName);  // Call Menu's delete dish method
    }
}

// Modify dish price/availability
bool Manager::modifyMenuItem(const std::string& foodName, double newPrice, bool newAvailability)
{
    Menu* menu = restaurant->getMenu();
    return menu->modifyFoodItem(foodName, newPrice, newAvailability);  // Call Menu's modify method
}

// Generate reservation report (statistics by date, saved as txt file)
void Manager::generateReservationReport(const std::string& date) const
{
    std::ofstream report("ReservationReport_" + date + ".txt");
    if (!report.is_open())
    {
        std::cerr << "Error: Failed to generate report file" << std::endl;
        return;
    }

    report << "===== " << restaurant->getName() << " 预定报表 (" << date << ") =====" << std::endl;
    int totalReservations = 0;
    int confirmed = 0, pending = 0, cancelled = 0, rejected = 0;

    // Traverse all table reservations
    for (const Table* table : restaurant->getTables())
    {
        Reservation* res = table->getCurrentReservation();
        if (res && res->getDateTime().substr(0, 10) == date)
        {  // Assume date format "YYYY-MM-DD HH:MM"
            totalReservations++;
            report << "\nTable ID: " << table->getTableId() << "\n"
                   << "预订ID: " << res->getReservationId() << "\n"
                   << "顾客: " << res->getCustomerName() << " (" << res->getCustomerPhone() << ")\n"
                   << "预订时间: " << res->getDateTime() << "\n"
                   << "就餐人数: " << res->getPartySize() << "\n"
                   << "状态: " << res->getStatus() << "\n"
                   << "特殊需求: " << res->getCustomerRequest() << std::endl;

            // Statistics by status
            if (res->getStatus() == "Confirmed") confirmed++;
            else if (res->getStatus() == "Pending") pending++;
            else if (res->getStatus() == "Cancelled") cancelled++;
            else if (res->getStatus() == "Rejected") rejected++;
        }
    }

    // Statistical information
    report << "\n===== Statistics =====" << std::endl;
    report << "预定总数: " << totalReservations << "\n"
           << "Confirmed: " << confirmed << ", Pending: " << pending
           << ", Cancelled: " << cancelled << ", Rejected: " << rejected << std::endl;
    report.close();

    std::cout << "Report generated successfully: ReservationReport_" << date << ".txt" << std::endl;
}

// View business statistics (simplified version: dish price distribution, table usage rate)
void Manager::viewBusinessStats() const
{
    std::cout << "\n===== Business Statistics =====" << std::endl;

    // 1. Table usage rate
    int totalTables = restaurant->getTables().size();
    int occupiedTables = 0;
    for (const Table* table : restaurant->getTables())
    {
        if (!table->isTableAvailable()) occupiedTables++;
    }
    double tableUsageRate = totalTables > 0 ? (occupiedTables * 100.0 / totalTables) : 0;
    std::cout << "Table usage rate: " << std::fixed << std::setprecision(1) << tableUsageRate << "% (" << occupiedTables << "/" << totalTables << ")" << std::endl;

    // 2. Dish price distribution
    Menu* menu = restaurant->getMenu();
    std::vector<FoodItem> items = menu->getFoodItems();
    double avgPrice = 0.0;
    for (const auto& item : items) avgPrice += item.foodPrice;
    avgPrice = items.empty() ? 0 : avgPrice / items.size();
    std::cout << "Average dish price: ¥" << std::fixed << std::setprecision(1) << avgPrice << ", Total dishes: " << items.size() << std::endl;
}
