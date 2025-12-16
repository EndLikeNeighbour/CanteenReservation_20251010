#ifndef MENU_H
#define MENU_H

#include <vector>
#include "user.h"  // Reference FoodItem structure

class Menu
{
private:
    std::vector<FoodItem> foodItems;  // Dish list (sorted by category)

public:
    // Default constructor (load default dishes, load from database in actual projects)
    Menu();

    // Display all dish lists (grouped by category)
    void showFoodList() const;

    // Display price of specified dish (return -1 if dish does not exist)
    double showPrice(const std::string& foodName) const;

    // Calculate order amount (input dish name list, return total price)
    double calculatePayment(const std::vector<std::string>& order) const;

    // Add dish (only Manager can call)
    void addFoodItem(const FoodItem& item);

    // Delete dish (only Manager can call)
    bool removeFoodItem(const std::string& foodName);

    // Modify dish price or availability (only Manager can call)
    bool modifyFoodItem(const std::string& foodName, double newPrice, bool newAvailability);

    // Recommend dishes (recommend based on number of diners, e.g., "3 meat 1 vegetarian for 4 people")
    std::vector<std::string> recommendDishes(int partySize) const;

    // Get all dishes (for UI display)
    std::vector<FoodItem> getFoodItems() const;
};

#endif // MENU_H
