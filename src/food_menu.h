#ifndef FOOD_MENU_H
#define FOOD_MENU_H

#include <string>
using namespace std;

// MEMBER 1: Food Structure
// Stores ID, name and price of each food item.

struct Food {
    int id;
    string name;
    float price;
};

// Total number of food items
const int MENU_SIZE = 8;

// Makes the menu array accessible in other files
extern Food menu[MENU_SIZE];

// MEMBER 1: Function declarations

void displayMenu();
void searchFood();
void sortFood();

#endif