#ifndef VIEW_SEATS_HPP
#define VIEW_SEATS_HPP

#include <iostream>
#include <list>
#include <string>
#include "MovieList.hpp" // Include MovieList.hpp for accessing movie details

using namespace std;

// Function to display the list of movies and make a booking
void displayMovies(const list<Movie>& movies) {
    cout << "\n==============================" << endl;
    cout << "       Available Movies      " << endl;
    cout << "==============================\n" << endl;
    
    size_t i = 1;
    for (const auto& movie : movies) {
        cout << "Movie #" << i << ":" << endl;
        cout << "\nTitle: " << movie.title << endl;
        cout << "Director: " << movie.director << endl;
        cout << "Year: " << movie.year << endl;
        cout << "Genre: " << movie.genre << endl;
        cout << "\nShowtimes:" << endl;
        
        size_t j = 1;
        for (const auto& showtime : movie.showtimes) {
            cout << "   (" << j << ") " << showtime << endl;
            ++j;
        }
        
        cout << "---------------------" << endl;
        ++i;
    }
}

// Function to view the seating arrangement for a selected movie and showtime
void viewSeats(const Movie& movie, const string& showtime) {
    cout << "\n=============================================================" << endl;
    cout << "Seating arrangement for \"" << movie.title << "\" at " << showtime << "." << endl;
    cout << "=============================================================" << endl;

    // Call the function to display seats
    displaySeats(movie.title, showtime);
}

// Function to choose a movie and time and view seating arrangements
void chooseMovieAndTime(const list<Movie>& movies) {
    // Display available movies and showtimes
    displayMovies(movies);

    // Ask user to choose a movie and time
    int movieChoice;
    cout << "\nEnter the number of the movie you want to watch: ";
    cin >> movieChoice;

    auto it = movies.begin();
    advance(it, movieChoice - 1); // Move iterator to selected movie

    if (movieChoice < 1 || static_cast<size_t>(movieChoice) > movies.size()) {
        cout << "Invalid movie choice. Please try again." << endl;
        return;
    }

    int showtimeChoice;
    cout << "Enter the number of the preferred showtime: ";
    cin >> showtimeChoice;

    auto& selectedMovie = *it;
    auto showtimeIt = selectedMovie.showtimes.begin();
    advance(showtimeIt, showtimeChoice - 1); // Move iterator to selected showtime

    if (showtimeChoice < 1 || static_cast<size_t>(showtimeChoice) > selectedMovie.showtimes.size()) {
        cout << "Invalid showtime choice. Please try again." << endl;
        return;
    }

    // Get the selected showtime
    string selectedShowtime = *showtimeIt;

    // View seating arrangement for the selected movie and showtime
    viewSeats(selectedMovie, selectedShowtime);
}

#endif // VIEW_SEATS_HPP
