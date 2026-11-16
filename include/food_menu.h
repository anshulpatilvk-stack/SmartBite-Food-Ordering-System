#ifndef FOOD_MENU_H
#define FOOD_MENU_H

#include <string>
using namespace std;

// Food structure
struct Food {
    int id;
    string name;
    float price;
};

// Function declarations
void displayMenu();
void searchFood();
void sortFood();

#endif
