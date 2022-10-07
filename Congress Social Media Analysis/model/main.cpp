// Daniel Scheuermann
// CS 124
// OL Section

#include <vector>
#include <iostream>
#include "Politician.h"

/**
 * main
 */
int main() {

    std::vector<Politician> politicians;
    std::string filename = "./politician_statistics.csv";

    if (loadFromFile(filename, politicians)) {

        std::cout << std::endl;

        std::cout << politicians.size()
                  << " records read from file" << std::endl;
        int firstId = politicians.front().getRowId();
        std::cout << "The first row ID read was " << firstId << std::endl;
        int lastId = politicians.back().getRowId();
        std::cout << "The last row ID read was " << lastId << std::endl;
    } else {
        std::cout << "Something went wrong." << std::endl;
    }

    // Verify things are working
    politicianTest();

    // Check for bad fields
    verifyAllFieldsSet(politicians);

    // Perform calculations
    showAveragePostsByParty(politicians);

    // Print object to test overload of <<
    std::cout << std::endl;

    std::cout << "Note: NAA is Number of Active Accounts" << std::endl;
    std::cout << "Note: Posts is the total number of posts for that account" << std::endl;
    std::cout << "Note: Favs and Shares are the Favorites/Shares the politicians average post receives" << std::endl;

    std::cout << std::endl;

    std::cout << std::left
              << std::setprecision(2)
              << std::setw(8) << "Row ID"
              << std::setw(15) << "BioguideID"
              << std::setw(6) << "Party"
              << std::setw(11) << "Platform"
              << std::setw(5) << "NAA"
              << std::setw(13) << "Followers"
              << std::setw(6) << "Posts"
              << std::setw(6) << "Favs"
              << std::setw(6) << "Shares"
              << std::endl;
    std::cout << std::string(97,'-') << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << politicians.at(i) << std::endl;
    }

}

