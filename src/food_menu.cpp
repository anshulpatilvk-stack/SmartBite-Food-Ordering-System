#include <iostream>
#include <iomanip>
#include "food_menu.h"

using namespace std;

// MEMBER 1: Array of food items
Food menu[MENU_SIZE] = {
    {1, "Pizza", 150},
    {2, "Burger", 80},
    {3, "Pasta", 120},
    {4, "Sandwich", 60},
    {5, "Fries", 50},
    {6, "Momos", 90},
    {7, "Coffee", 40},
    {8, "Cold Drink", 30}
};

// MEMBER 1: Display Food Menu
// Concept: Array and Structure
// Time Complexity: O(n)
// Space Complexity: O(1)

void displayMenu() {

    cout << "\n========== FOOD MENU ==========\n";

    cout << left << setw(10) << "ID"
         << setw(20) << "Food Name"
         << "Price\n";

    for (int i = 0; i < MENU_SIZE; i++) {

        cout << left << setw(10) << menu[i].id
             << setw(20) << menu[i].name
             << "Rs. " << menu[i].price << endl;
    }
}

// MEMBER 1: Search Food
// Concept: Linear Search
// Time Complexity: O(n)
// Space Complexity: O(1)

void searchFood() {

    int id;
    bool found = false;

    cout << "\nEnter Food ID to search: ";
    cin >> id;

    for (int i = 0; i < MENU_SIZE; i++) {

        if (menu[i].id == id) {

            cout << "\nFood Found!\n";
            cout << "Food Name: " << menu[i].name << endl;
            cout << "Price: Rs. " << menu[i].price << endl;

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nFood item not found!\n";
    }
}

// MEMBER 1: Sort Food by Price
// Concept: Bubble Sort
// Time Complexity: O(n^2)
// Space Complexity: O(1)

void sortFood() {

    for (int i = 0; i < MENU_SIZE - 1; i++) {

        for (int j = 0; j < MENU_SIZE - 1 - i; j++) {

            if (menu[j].price > menu[j + 1].price) {

                Food temp = menu[j];

                menu[j] = menu[j + 1];

                menu[j + 1] = temp;
            }
        }
    }

    cout << "\nFood Menu Sorted by Price!\n";

    displayMenu();
}