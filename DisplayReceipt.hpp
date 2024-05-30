#ifndef DISPLAY_RECEIPT_HPP
#define DISPLAY_RECEIPT_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include "seatArrangement.hpp" // assuming this includes the necessary functions for seat arrangements

using namespace std;

void displayReceipt() {
    ifstream inFile("booking_details.txt");
    if (!inFile.is_open()) {
        cout << "Error: Unable to open booking details file." << endl;
        return;
    }

    cout << "\n======================================" << endl;
    cout << setw(20) << "Booking Receipt" << endl;
    cout << "======================================" << endl;

    string line;
    while (getline(inFile, line)) {
        if (line.find("Booking details") != string::npos) {
            cout << "" << line << endl;
        } else if (line.find("Total Cost") != string::npos || line.find("Number of") != string::npos) {
            cout << "" << line << endl;
        } else {
            cout << line << endl;
        }
    }

    cout << "\n=============End of Receipt===========" << endl;


    inFile.close();
}

#endif // DISPLAY_RECEIPT_HPP
