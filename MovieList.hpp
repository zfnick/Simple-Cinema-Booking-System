#ifndef MOVIE_LIST_HPP
#define MOVIE_LIST_HPP

#include <iostream>
#include <list>
#include <string>
#include "seatArrangement.hpp" // Include seatArrangement.hpp for accessing displaySeats()

using namespace std;

// Define a Movie structure to hold movie details
struct Movie {
    string title;
    string director;
    int year;
    string genre;
    list<string> showtimes;
};

struct Node {
    Movie data;
    Node* next;
};

// Function to display the list of movies and make a booking
void displayMovies() {
    Node* movies = new Node{
        {"The Shawshank Redemption", "Frank Darabont", 1994, "Drama", {"10:00 AM", "2:00 PM", "6:00 PM"}},
        new Node{
            {"The Godfather", "Francis Ford Coppola", 1972, "Crime", {"11:00 AM", "3:00 PM", "7:00 PM"}},
            new Node{
                {"The Dark Knight", "Christopher Nolan", 2008, "Action", {"12:00 PM", "4:00 PM", "8:00 PM"}},
                nullptr
            }
        }
    };

    cout << "\n==============================" << endl;
    cout << "       Available Movies      " << endl;
    cout << "==============================\n" << endl;
    
    Node* current = movies;
    for (size_t i = 0; current != nullptr; ++i) {
        cout << "Movie #" << i + 1 << ":" << endl;
        cout << "\nTitle: " << current->data.title << endl;
        cout << "Director: " << current->data.director << endl;
        cout << "Year: " << current->data.year << endl;
        cout << "Genre: " << current->data.genre << endl;
        cout << "\nShowtimes:" << endl;

    // Display showtimes
        int showtimeCount = 1;
        for (const auto& showtime : current->data.showtimes) {
            cout << showtimeCount++ << ") " << showtime << endl;
        }
        
        cout << "---------------------" << endl;
        current = current->next;
    }

    int movieChoice;
    cout << "\nEnter the number of the movie you want to watch: ";
    cin >> movieChoice;

    Node* selectedMovieNode = movies;
    for (int i = 1; i < movieChoice && selectedMovieNode != nullptr; ++i) {
        selectedMovieNode = selectedMovieNode->next;
    }

    if (movieChoice < 1 || selectedMovieNode == nullptr) {
        cout << "Invalid movie choice. Please try again." << endl;
        return;
    }

    int showtimeChoice;
    cout << "Enter the number of the preferred showtime: ";
    cin >> showtimeChoice;

    if (showtimeChoice < 1 || showtimeChoice > selectedMovieNode->data.showtimes.size()) {
        cout << "Invalid showtime choice. Please try again." << endl;
        return;
    }

    string selectedMovie = selectedMovieNode->data.title;
    string selectedShowtime = selectedMovieNode->data.showtimes.front(); // Assuming the list is ordered
    cout << "\n=============================================================" << endl;
    cout << "You have selected \"" << selectedMovie << "\" at " << selectedShowtime << "." << endl;
    cout << "=============================================================" << endl;

    displaySeats(selectedMovie, selectedShowtime);
}


#endif
