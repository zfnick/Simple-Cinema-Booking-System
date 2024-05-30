#ifndef SEAT_ARRANGEMENT_HPP
#define SEAT_ARRANGEMENT_HPP

#include <iostream>
#include <queue>
#include <unordered_set>
#include <algorithm> // for std::find
#include <fstream>   // for file operations

using namespace std;

// Define a structure to represent a booking
struct Booking {
    string movie;
    string showtime;
    string seat;
};

// Global vector to store bookings
queue<Booking> bookings;

// Function to check if a seat is available
bool isSeatAvailable(const unordered_set<string>& allSeats, const string& seat) {
    return allSeats.count(seat) > 0;
}

// Function to check if a seat is part of a twin pair
bool isTwinSeat(const string& seat) {
    char row = seat[0];
    int seatNum = stoi(seat.substr(1));

    // Remove the restriction for twin seats in rows 'S' and 'T'
    return !((row == 'A' || row == 'G') && (seatNum == 1 || seatNum == 2 || seatNum == 23 || seatNum == 24)) &&
           !((row == 'B' || row == 'C') && (seatNum == 5 || seatNum == 6 || seatNum == 23)) &&
           !(row == 'S' || row == 'T');
}

// Function to book both seats in a twin pair
void bookTwinSeat(const string& selectedMovie, const string& selectedShowtime, const string& seat) {
    char row = seat[0];
    int seatNum = stoi(seat.substr(1));

    if (row == 'A' || row == 'G') {
        string twinSeat = string(1, row) + to_string(seatNum % 2 == 0 ? seatNum - 1 : seatNum + 1);
        bookings.push({selectedMovie, selectedShowtime, seat});
        bookings.push({selectedMovie, selectedShowtime, twinSeat});
    } else if (row == 'B' || row == 'C') {
        string twinSeat = string(1, row) + to_string(seatNum == 5 ? 6 : 5);
        bookings.push({selectedMovie, selectedShowtime, seat});
        bookings.push({selectedMovie, selectedShowtime, twinSeat});
    }
}

void displaySeats(const string& selectedMovie, const string& selectedShowtime) {

    const double PRICE_ROW_A_TO_F = 15.0;
    const double PRICE_ROW_G_TO_L = 20.0;
    const double PRICE_ROW_M_TO_R = 25.0;
    const double PRICE_ROW_S_TO_T = 22.5;
    const double CHILD_DISCOUNT = 0.5;

    // Variables to track total cost and number of adult and child tickets
    double totalCost = 0.0;
    int adultTickets = 0;
    int childTickets = 0;

    // Output file stream for saving booking details
    ofstream outFile("booking_details.txt", ios::app); // Open file in append mode
    
        // Write movie and showtime information to the file
    outFile << "Movie: " << selectedMovie << endl;
    outFile << "Showtime: " << selectedShowtime << endl;
    

    vector<string> selectedSeats;
    cout << "\n--------------------------" << endl;
    cout << "Cinema Seating Arrangement" << endl;
    cout << "--------------------------" << endl;
    cout << "=========================================================Screen===========================================================\n" << endl;
    cout << "    01  02  03  04  05  06      07  08  09  10  11  12  13  14  15  16  17  18  19  20  21  22      23  24  25  26  27  28\n" << endl;

    // Define a set of all seats (all seats are initially available)
    unordered_set<string> allSeats;
    for (char row = 'A'; row <= 'T'; ++row) {
        for (int seatNum = 1; seatNum <= 28; ++seatNum) {
            string seat = string(1, row) + to_string(seatNum);
            // Exclude specific seats from being available
            if (!(seat == "A1" || seat == "A2" || seat == "A3" || seat == "A4" || seat == "A5" || seat == "A6" ||
                  seat == "A23" || seat == "A24" || seat == "A25" || seat == "A26" || seat == "A27" || seat == "A28" ||
                  seat == "B5" || seat == "B6" || seat == "B23" || seat == "B24" ||
                  seat == "C6" || seat == "C23" ||
                  seat == "G1" || seat == "G2" || seat == "G3" || seat == "G4" || seat == "G5" || seat == "G6" ||
                  seat == "G23" || seat == "G24" || seat == "G25" || seat == "G26" || seat == "G27" || seat == "G28")) {
                allSeats.insert(seat);
            }
        }
    }

 // Loop through rows and seats to display the seating arrangement
for (char row = 'A'; row <= 'T'; ++row) {
    // Output to console and file
    cout << row << "  ";
    for (int seatNum = 1; seatNum <= 28; ++seatNum) {
        string seat = string(1, row) + to_string(seatNum);
        bool seatAvailable = allSeats.count(seat) > 0;
        bool seatBooked = false;
        queue<Booking> tempBookings = bookings; // Copy queue for iteration
        while (!tempBookings.empty()) {
            Booking tempBooking = tempBookings.front();
            tempBookings.pop();
            if (tempBooking.movie == selectedMovie && tempBooking.showtime == selectedShowtime && tempBooking.seat == seat) {
                seatBooked = true;
                break;
            }
        }
        if (seatNum == 7 || seatNum == 23) {
            cout << "    ";
        }

        if (seatBooked) {
            if (row == 'S' || row == 'T') {
                if (seatNum % 2 != 0)
                    cout << "[  x";
                else
                    cout << "x  ]";
            } else {
                cout << "[xx]";  // Seat is booked
            }
            if (row == 'F' && seatNum == 28) {
                cout << "\n";
            }
            if (row == 'L' && seatNum == 28) {
                cout << "\n";
            }
        } else if (seatAvailable) {
            if (row == 'S' || row == 'T') {
                if (seatNum % 2 != 0)
                    cout << "[   ";
                else
                    cout << "   ]";
            } else {
                cout << "[  ]";  // Seat is available
            }
            if (row == 'F' && seatNum == 28) {
                cout << "\n";
            }
            if (row == 'M' && seatNum == 28) {
                cout << "\n";
            }
        } else {
            cout << "    ";  // Seat does not exist
        }
    }
    cout << endl;
}

    cout << "\n\nLegend:" << endl;
    cout << "(Row A-F) - Green (RM15 per seat)" << endl;
    cout << "(Row G-M) - Yellow (RM20 per seat)" << endl;
    cout << "(Row N-R) - Orange (RM25 per seat)" << endl;
    cout << "(Row S-T) - Blue (RM45 per twin seat)" << endl;
    cout << "[Twin seats must be only odd numbers e.g,(S1, S3, T1, T3)]" << endl;    
    cout << "[ ] - Available" << endl;
    cout << "[xx] - Booked" << endl;
    cout << "----------------------------------------------------------------\n" << endl;

cout << "Please select a seat to start booking (Maximum 5) (e.g., B1): ";
string input;

while (selectedSeats.size() < 5 && cin >> input && input != "done") {
   size_t firstDigitIndex = input.find_first_of("0123456789");
   if (firstDigitIndex == string::npos) {
       cout << "Invalid input. Please enter a valid seat or type 'done' to stop: ";
       continue; // Skip the rest of the loop iteration and start from the beginning
   }

   string rowPart = input.substr(0, firstDigitIndex); // Extract row part
   int seatNum = stoi(input.substr(firstDigitIndex)); // Correctly extract seat number

   // Check if the selected seat is valid
   string seat = rowPart + to_string(seatNum); // Reconstruct seat string correctly

   // Check if the seat is directly 1 seat left or right of any of the previously selected seats
   bool seatIsValid = false;
   if (!selectedSeats.empty()) {
       for (const auto &prevSeat : selectedSeats) {
           char prevRow = prevSeat[0];
           int prevSeatNum = stoi(prevSeat.substr(1));

           if ((rowPart[0] == prevRow) && ((seatNum == prevSeatNum - 1) || (seatNum == prevSeatNum + 1))) {
               seatIsValid = true;
               break;
           }
       }
   } else {
       seatIsValid = true; // For the first selected seat
   }

   if (!seatIsValid) {
       cout << "Invalid seat selection. Please select a seat adjacent to the previously selected seats or type 'done' to stop: ";
       continue; // Skip the rest of the loop iteration and start from the beginning
   }

   // Add the selected seat
   selectedSeats.push_back(seat);
   allSeats.erase(seat);
   cout << "Seat " << seat << " added.\n";

   // Check if the seat is in twin seat rows
   if ((rowPart[0] == 'S' || rowPart[0] == 'T') && seatNum % 2 != 0) {
       // Also add the corresponding twin seat
       string twinSeat = rowPart + to_string(seatNum % 2 == 0 ? seatNum - 1 : seatNum + 1);
       if (allSeats.count(twinSeat) && find(selectedSeats.begin(), selectedSeats.end(), twinSeat) == selectedSeats.end()) {
           selectedSeats.push_back(twinSeat);
           allSeats.erase(twinSeat);
           cout << "Seat " << twinSeat << " added.\n";
       }
   }
}

    char choice;
    cout << "Do you want to proceed with booking these seats? (y/n): ";
    cin >> choice;

    bool hasAdultTicket = false;
    bool hasChildTicket = false;

if (choice == 'y' || choice == 'Y') {
    for (const auto &seat : selectedSeats) {
        char ticketType = 'a'; // Default to adult ticket
        char row = seat[0];

        // Only ask for ticket type if NOT in row S or T
        if (row != 'S' && row != 'T') {
            cout << "Is seat " << seat << " for an adult or child? (a/c): ";
            cin >> ticketType;
        } else {
            cout << "Seat " << seat << " is in row " << row << " and can only be booked as an adult ticket.\n";
        }

        if (ticketType == 'a' || row == 'S' || row == 'T') {
            hasAdultTicket = true;
        } else if (ticketType == 'c') {
            hasChildTicket = true;
        }

        double seatPrice = 0.0;
        if (row >= 'A' && row <= 'F') {
            seatPrice = PRICE_ROW_A_TO_F;
        } else if (row >= 'G' && row <= 'M') {
            seatPrice = PRICE_ROW_G_TO_L;
        } else if (row >= 'N' && row <= 'R') {
            seatPrice = PRICE_ROW_M_TO_R;
        } else {
            seatPrice = PRICE_ROW_S_TO_T;
        }

            cout << "\nBooking details for seat " << seat << ":" << endl;
            outFile << "\nBooking details for seat " << seat << ":" << endl;
            if (ticketType == 'a') {
                adultTickets++;
                totalCost += seatPrice;
                cout << "Adult ticket (RM" << seatPrice << ")\n" << endl;
                outFile << "Adult ticket (RM" << seatPrice << ")" << endl;
            } else if (ticketType == 'c') {
                childTickets++;
                totalCost += seatPrice * CHILD_DISCOUNT;
                cout << "Child ticket (RM" << seatPrice * CHILD_DISCOUNT << ")\n" << endl;
                outFile << "Child ticket (RM" << seatPrice * CHILD_DISCOUNT << ")" << endl;
            } else {
                cout << "Invalid input. Assuming adult ticket." << endl;
                outFile << "Adult ticket (RM" << seatPrice << ")" << endl;
                adultTickets++;
                totalCost += seatPrice;
            }

            bookings.push({selectedMovie, selectedShowtime, seat});
            if (isTwinSeat(seat)) {
                bookTwinSeat(selectedMovie, selectedShowtime, seat);
            }
        }

        if ((hasAdultTicket || hasChildTicket) && (hasAdultTicket || !hasChildTicket)) {\
            cout << "Number of Adult Tickets: " << adultTickets << endl;
            cout << "Number of Child Tickets: " << childTickets << endl;
            cout << "=================" << endl;
            cout << "Total Cost: RM" << totalCost << endl;
            cout << "=================" << endl;

            outFile << "\nNumber of Adult Tickets: " << adultTickets << endl;
            outFile << "Number of Child Tickets: " << childTickets << endl;
            outFile << "=================" << endl;
            outFile << "Total Cost: RM" << totalCost << endl;
            outFile << "=================" << endl;
        } else {
            cout << "Booking canceled. No seats have been booked or not enough tickets selected." << endl;
            outFile << "Booking canceled. No seats have been booked or not enough tickets selected." << endl;
        }
    } else {
        cout << "Booking canceled by the user." << endl;
        outFile << "Booking canceled by the user." << endl;
    }
}

#endif //SEAT_ARRANGEMENT_HPP