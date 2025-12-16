// File name: Menu.cpp
#include "Menu.h"
#include <iostream>
#include <algorithm>  // Used for finding dishes (find_if)

Menu::Menu()
{
    foodItems =
    {
        {"红烧牛窝骨", 78.0, "热菜", true},
        {"糖醋菊花鱼", 38.0, "热菜", true},
        {"八珍豆腐", 68.0, "热菜", true},
        {"老爆三", 48.0, "热菜", true},
        {"锅塌里脊", 58.0, "热菜", true},
        {"凉拌豆腐丝", 16.0, "凉菜", true},
        {"驴打滚", 36.0, "甜品", false},
        {"青提芋圆", 36.0, "甜品", true},
        {"棒打今日橙", 8.0, "饮品", true}
    };
}

// Display all dishes (grouped by category)
void Menu::showFoodList() const
{
    std::cout << "\n===== Restaurant Menu =====" << std::endl;
    std::string currentCategory = "";
    for (const auto& item : foodItems)
    {
        // Display grouped by category (e.g., "Hot Dishes" first, then "Cold Dishes")
        if (item.category != currentCategory)
        {
            currentCategory = item.category;
            std::cout << "\n[" << currentCategory << "]" << std::endl;
        }
        std::cout << "- " << item.foodName << ": ¥" << item.foodPrice<< (item.IsAvailable ? "" : " (Out of stock)") << std::endl;
    }
}

// Display price of specified dish
double Menu::showPrice(const std::string& FoodName) const
{
    for (const auto& item : foodItems)
    {
        if (item.foodName == FoodName && item.IsAvailable)
        {
            return item.foodPrice;
        }
    }
    return -1.0;  // Dish does not exist or is out of stock
}

// Calculate order amount
double Menu::calculatePayment(const std::vector<std::string>& order) const
{
    double total = 0.0;
    for (const auto& food : order)
    {
        double price = showPrice(food);
        if (price == -1.0)
        {
            std::cerr << "Warning: Dish '" << food << "' does not exist or is out of stock, will not be included in the total amount" << std::endl;
        }
        else
        {
            total += price;
        }
    }
    return total;
}

// Add dish (Manager function)
void Menu::addFoodItem(const FoodItem& item)
{
    std::string targetCategory = item.category;
    auto lastSameCategory = foodItems.end();
    // Check if dish with the same name already exists
    for (const auto& existing : foodItems)
    {
        if (existing.foodName == item.foodName)
        {
            std::cerr << "Error: Dish '" << item.foodName << "' already exists, addition failed" << std::endl;
            return;
        }
    }
    for (auto it = foodItems.begin(); it != foodItems.end(); ++it)
    {
        if (it->category == targetCategory)
        {
            lastSameCategory = it; // 持续更新为最后一个同分类菜品
        }
    }
    auto insertPos = foodItems.end();
    if (lastSameCategory != foodItems.end())
    {
        insertPos = lastSameCategory + 1;
    }
    foodItems.insert(insertPos, item);
    std::cout << "Dish '" << item.foodName << "' added successfully" << std::endl;
}

// Delete dish (Manager function)
bool Menu::removeFoodItem(const std::string& foodName)
{
    auto it = std::find_if(foodItems.begin(), foodItems.end(),[&](const FoodItem& item) { return item.foodName == foodName; });
    if (it != foodItems.end())
    {
        foodItems.erase(it);
        std::cout << "Dish '" << foodName << "' deleted successfully" << std::endl;
        return true;
    }
    std::cerr << "Error: Dish '" << foodName << "' does not exist, deletion failed" << std::endl;
    return false;
}

// Modify dish price and availability (Manager function)
bool Menu::modifyFoodItem(const std::string& foodName, double newPrice, bool newAvailability)
{
    for (auto& item : foodItems)
    {
        if (item.foodName == foodName)
        {
            item.foodPrice = newPrice;
            item.IsAvailable = newAvailability;
            std::cout << "Dish '" << foodName << "' modified successfully: New price ¥" << newPrice
                      << ", Status: " << (newAvailability ? "In stock" : "Out of stock") << std::endl;
            return true;
        }
    }
    std::cerr << "Error: Dish '" << foodName << "' does not exist, modification failed" << std::endl;
    return false;
}

// Recommend dishes (Simple logic: 0.75 hot dishes per person + 1 cold dish + 1 drink)
std::vector<std::string> Menu::recommendDishes(int partySize) const
{
    std::vector<std::string> recommendations;
    int hotDishes = std::max(1, (int)(partySize * 0.75));  // Number of hot dishes
    int coldDishes = 1;
    int drinks = 1;

    // Filter available dishes
    std::vector<FoodItem> availableHot, availableCold, availableDrinks;
    for (const auto& item : foodItems)
    {
        if (!item.IsAvailable) continue;
        if (item.category == "Hot Dishes") availableHot.push_back(item);
        else if (item.category == "Cold Dishes") availableCold.push_back(item);
        else if (item.category == "Drinks") availableDrinks.push_back(item);
    }

    // Add recommendations (take first N available dishes)
    for (int i = 0; i < hotDishes && i < availableHot.size(); ++i)
    {
        recommendations.push_back(availableHot[i].foodName);
    }
    if (coldDishes > 0 && !availableCold.empty())
    {
        recommendations.push_back(availableCold[0].foodName);
    }
    if (drinks > 0 && !availableDrinks.empty())
    {
        recommendations.push_back(availableDrinks[0].foodName);
    }

    return recommendations;
}

// Get all dishes (for UI calls)
std::vector<FoodItem> Menu::getFoodItems() const
{
    return foodItems;
}
