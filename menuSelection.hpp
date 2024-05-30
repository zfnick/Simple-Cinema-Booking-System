#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <cstdlib> // for exit()
#include "seatArrangement.hpp" // assuming this includes the necessary functions for seat arrangements
#include "movieList.hpp"
#include "ViewSeats.hpp" // Include the header file for ViewSeats
#include "DisplayReceipt.hpp"

using namespace std;

// Declare ViewSeats function to make it accessible to displayMenu
void displaySeats();

void displayMenu() {
    cout << "\nPlease select an option from the menu below:" << endl;
    cout << "1. Browse Movies" << endl;
    cout << "2. Display receipt" << endl;
    cout << "3. Exit" << endl;

    int option;
    cout << "\nEnter your choice: ";
    cin >> option;

    switch (option) {
        case 1:
            cout << "\nBrowsing Movies:" << endl;
            displayMovies(); // Display available movies
            break;
        case 2:
            cout << "\nDisplay receipt:" << endl;
            displayReceipt(); // Add functionality to print booking receipt
            break;
        case 3:
            cout << "\n----------------------------" << endl;
            cout << "System Terminated. Thank You." << endl;
            cout << "-----------------------------" << endl;
            exit(0);
        default:
            cout << "\n--------------------------------" << endl;
            cout << "Invalid option. Please try again." << endl;
            cout << "--------------------------------" << endl;
    }
}

#endif // MENU_HPP
