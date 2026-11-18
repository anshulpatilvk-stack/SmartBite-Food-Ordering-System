#include <iostream>
#include <iomanip>
#include "food_menu.h"

using namespace std;

// Maximum number of items in one order
const int MAX_ITEMS = 10;
const int MAX_ORDERS = 100;

// ==================================================
// SHARED STRUCTURE
// Used by Member 2, Member 3 and Member 4
// ==================================================

struct Order {

    int orderID;

    Food items[MAX_ITEMS];

    int quantity[MAX_ITEMS];

    int itemCount;

    float total;

    string status;
};

// ==================================================
// MEMBER 2: PLACE ORDER AND BILLING
// Concepts: Array, Structure and Functions
// ==================================================

int nextOrderID = 1;

// Function to place an order

Order placeOrder() {

    Order newOrder;

    newOrder.orderID = nextOrderID++;

    newOrder.itemCount = 0;

    newOrder.total = 0;

    newOrder.status = "Pending";

    int id, qty;

    cout << "\n========== PLACE ORDER ==========\n";

    displayMenu();

    cout << "\nEnter Food ID (0 to finish): ";

    while (cin >> id && id != 0) {

        bool found = false;

        for (int i = 0; i < MENU_SIZE; i++) {

            if (menu[i].id == id) {

                found = true;

                if (newOrder.itemCount >= MAX_ITEMS) {
                    cout << "Maximum item limit reached!\n";
                    break;
                }

                cout << "Enter Quantity: ";
                cin >> qty;

                if (qty <= 0) {
                    cout << "Invalid quantity!\n";
                    break;
                }

                // Store food item in order array
                int index = newOrder.itemCount;

                newOrder.items[index] = menu[i];

                newOrder.quantity[index] = qty;

                newOrder.total += menu[i].price * qty;

                newOrder.itemCount++;

                cout << "Item Added Successfully!\n";

                break;
            }
        }

        if (!found) {
            cout << "Invalid Food ID!\n";
        }

        cout << "\nEnter next Food ID (0 to finish): ";
    }

    return newOrder;
}

// Function to generate bill

void generateBill(Order order) {

    cout << "\n========== SMART BITE BILL ==========\n";

    cout << "Order ID: " << order.orderID << endl;

    cout << "-------------------------------------\n";

    cout << left << setw(18) << "Food"
         << setw(10) << "Quantity"
         << "Amount\n";

    for (int i = 0; i < order.itemCount; i++) {

        cout << left << setw(18) << order.items[i].name
             << setw(10) << order.quantity[i]
             << "Rs. "
             << order.items[i].price * order.quantity[i]
             << endl;
    }

    cout << "-------------------------------------\n";

    cout << "Total Amount: Rs. " << order.total << endl;

    cout << "Status: " << order.status << endl;

    cout << "=====================================\n";
}

// ==================================================
// MEMBER 3: ORDER HISTORY
// Concept: Singly Linked List
// ==================================================

// Node of linked list

struct Node {

    Order data;

    Node* next;
};

// Head pointer

Node* head = NULL;

// Function to add order to history
// Time Complexity: O(1)

void addHistory(Order order) {

    Node* newNode = new Node;

    newNode->data = order;

    newNode->next = head;

    head = newNode;
}

// Display complete order history
// Time Complexity: O(n)

void displayHistory() {

    cout << "\n========== ORDER HISTORY ==========\n";

    if (head == NULL) {

        cout << "No Order History Available!\n";

        return;
    }

    Node* temp = head;

    while (temp != NULL) {

        cout << "\nOrder ID: "
             << temp->data.orderID;

        cout << "\nTotal: Rs. "
             << temp->data.total;

        cout << "\nStatus: "
             << temp->data.status;

        cout << "\n-------------------------\n";

        temp = temp->next;
    }
}

// Update order status in linked list

void updateHistory(int id, string newStatus) {

    Node* temp = head;

    while (temp != NULL) {

        if (temp->data.orderID == id) {

            temp->data.status = newStatus;

            return;
        }

        temp = temp->next;
    }
}

// ==================================================
// MEMBER 4: STACK IMPLEMENTATION
// Concept: Stack (LIFO)
// Used for Undo Last Order
// ==================================================

class Stack {

    Order arr[MAX_ORDERS];

    int top;

public:

    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_ORDERS - 1;
    }

    void push(Order order) {

        if (isFull()) {
            cout << "Undo Stack is Full!\n";
            return;
        }

        arr[++top] = order;
    }

    Order pop() {

        return arr[top--];
    }
};

// ==================================================
// MEMBER 4: CIRCULAR QUEUE IMPLEMENTATION
// Concept: Circular Queue (FIFO)
// Used for Processing Orders
// ==================================================

class CircularQueue {

    Order arr[MAX_ORDERS];

    int front;
    int rear;
    int size;

public:

    CircularQueue() {

        front = -1;

        rear = -1;

        size = 0;
    }

    bool isEmpty() {

        return size == 0;
    }

    bool isFull() {

        return size == MAX_ORDERS;
    }

    // Insert order into circular queue

    bool enqueue(Order order) {

        if (isFull()) {

            cout << "Order Queue is Full!\n";

            return false;
        }

        if (isEmpty()) {

            front = 0;
        }

        rear = (rear + 1) % MAX_ORDERS;

        arr[rear] = order;

        size++;

        return true;
    }

    // Remove oldest order from queue

    Order dequeue() {

        Order temp = arr[front];

        if (size == 1) {

            front = -1;

            rear = -1;
        }

        else {

            front = (front + 1) % MAX_ORDERS;
        }

        size--;

        return temp;
    }

    // Remove most recently placed order
    // Used by Undo operation

    bool removeRear(int id) {

        if (isEmpty()) {
            return false;
        }

        if (arr[rear].orderID != id) {
            return false;
        }

        if (size == 1) {

            front = -1;

            rear = -1;
        }

        else {

            rear = (rear - 1 + MAX_ORDERS) % MAX_ORDERS;
        }

        size--;

        return true;
    }
};

// Create global stack and queue

Stack undoStack;

CircularQueue orderQueue;

// ==================================================
// MEMBER 4: UNDO LAST ORDER
// Uses Stack and Circular Queue
// ==================================================

void undoOrder() {

    if (undoStack.isEmpty()) {

        cout << "\nNo order available to undo!\n";

        return;
    }

    while (!undoStack.isEmpty()) {

        Order lastOrder = undoStack.pop();

        // Check whether order is still pending
        // An already processed order cannot be undone

        if (lastOrder.status == "Pending") {

            if (orderQueue.removeRear(lastOrder.orderID)) {

                updateHistory(lastOrder.orderID, "Cancelled");

                cout << "\nLast Order Successfully Undone!\n";

                cout << "Cancelled Order ID: "
                     << lastOrder.orderID << endl;

                return;
            }
        }
    }

    cout << "\nNo pending order available to undo!\n";
}

// ==================================================
// MEMBER 4: PROCESS ORDER
// Uses Circular Queue (FIFO)
// ==================================================

void processOrder() {

    if (orderQueue.isEmpty()) {

        cout << "\nNo Orders Available for Processing!\n";

        return;
    }

    Order currentOrder = orderQueue.dequeue();

    updateHistory(currentOrder.orderID, "Processed");

    cout << "\n========== ORDER PROCESSING ==========\n";

    cout << "Processing Order ID: "
         << currentOrder.orderID << endl;

    cout << "Customer Bill: Rs. "
         << currentOrder.total << endl;

    cout << "Order Successfully Processed!\n";

    cout << "======================================\n";
}

// ==================================================
// MAIN FUNCTION
// Integrates all four members' contributions
// ==================================================

int main() {

    int choice;

    cout << "\n";
    cout << "========================================\n";
    cout << "       WELCOME TO SMART BITE            \n";
    cout << "          FOOD ORDERING SYSTEM          \n";
    cout << "========================================\n";

    do {

        cout << "\n========== MAIN MENU ==========\n";

        cout << "1. Display Food Menu\n";

        cout << "2. Search Food\n";

        cout << "3. Sort Food by Price\n";

        cout << "4. Place Order\n";

        cout << "5. Generate Order History\n";

        cout << "6. Undo Last Order\n";

        cout << "7. Process Next Order\n";

        cout << "0. Exit\n";

        cout << "===============================\n";

        cout << "Enter Your Choice: ";

        cin >> choice;

        switch (choice) {

            // MEMBER 1

            case 1:

                displayMenu();

                break;

            case 2:

                searchFood();

                break;

            case 3:

                sortFood();

                break;

            // MEMBER 2

            case 4: {

                Order newOrder = placeOrder();

                if (newOrder.itemCount == 0) {

                    cout << "\nNo Items Selected. Order Not Placed!\n";

                    break;
                }

                // Add order to circular queue

                if (!orderQueue.enqueue(newOrder)) {

                    cout << "Order could not be placed!\n";

                    break;
                }

                // Add order to undo stack

                undoStack.push(newOrder);

                // Save order in linked list history

                addHistory(newOrder);

                // Generate customer bill

                generateBill(newOrder);

                cout << "\nOrder Placed Successfully!\n";

                break;
            }

            // MEMBER 3

            case 5:

                displayHistory();

                break;

            // MEMBER 4

            case 6:

                undoOrder();

                break;

            case 7:

                processOrder();

                break;

            case 0:

                cout << "\nThank You for Using Smart Bite!\n";

                break;

            default:

                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 0);

    return 0;
}