#include <iostream>
#include <iomanip>
#include "food_menu.h"

using namespace std;

// Array to store food items
Food menu[8] = {
    {1, "Pizza", 150},
    {2, "Burger", 80},
    {3, "Pasta", 120},
    {4, "Sandwich", 60},
    {5, "Fries", 50},
    {6, "Momos", 90},
    {7, "Coffee", 40},
    {8, "Cold Drink", 30}
};

// Display food menu Time:-O(n) Space:-O(1)
void displayMenu() {

    cout << "\n========== FOOD MENU ==========\n";

    cout << left << setw(10) << "ID"
         << setw(20) << "Food Name"
         << "Price\n";

    for (int i = 0; i < 8; i++) {

        cout << left << setw(10) << menu[i].id
             << setw(20) << menu[i].name
             << "Rs. " << menu[i].price << endl;
    }
}

// Search food using Linear Search Time:-O(n) Space:-O(1)
void searchFood() {

    int id;
    bool found = false;

    cout << "\nEnter Food ID to search: ";
    cin >> id;

    for (int i = 0; i < 8; i++) {

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

// Sort food using Bubble Sort Time:-O(n^2) Space:-O(1)
void sortFood() {

    for (int i = 0; i < 7; i++) {

        for (int j = 0; j < 7 - i; j++) {

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
