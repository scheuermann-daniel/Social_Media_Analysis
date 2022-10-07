// Daniel Scheuermann
// CS 124
// OL Section

#ifndef POLITICIAN_H
#define POLITICIAN_H

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <assert.h>

/**
* This class contains entries for the pewresearch dataset on polticians
 * and their social media statistics. More details at
 * https://www.pewresearch.org/internet/wp-content/uploads/sites/9/2020/07/PDL_07.16.20_congress.social.media_.appendix.B.pdf .
 *
 * Fields Used:
 * rowId: Integer used to provide a unique number to identify each row.
 * platform: a string of the social media platform being studied for that row ("facebook"
 * or "twitter".
 * party: a string containing the political leaning of the politician in question ("R" or "D")
 * bioguideId: a string identifier for the politician used the Biographical Directory of the
 * United States.
 * numActiveAccounts: an integer of how many accounts the politician had on a specified platform
 * that were active.
 * maxFollowers: an integer of the highest number of followers the politician had across all accounts on a platform
 * during their time serving in the 116th Congress.
 * totalPosts: an integer of the total number of posts the politician made while serving
 * in the 116th Congress.
 * avgFavs: an integer of the average number of favorites/reactions the politician received on each
 * post.
 * avgShares: an integer of the amount of shares which the politician's average post receives.
 *
 * To Note: for avgFavs and avgShares, retweets are excluded in the count. Only the original post
 * is analyzed.
 *
 * To Note: The data is gathered from January 1, 2015 to May 31, 2020.
*/

class Politician {

private:
    std::string platform, party, bioguideId;
    int rowId, numActiveAccounts, maxFollowers, totalPosts, avgFavs, avgShares;

public:

    // Constructors

    Politician() {

    }

    Politician(int rowId,
               std::string platform,
               std::string party,
               std::string bioguideId,
               int numActiveAccounts,
               int maxFollowers,
               int totalPosts,
               int avgFavs,
               int avgShares) {
        this->platform = platform;
        this->party = party;
        this->bioguideId = bioguideId;
        this->rowId = rowId;
        this->numActiveAccounts = numActiveAccounts;
        this->maxFollowers = maxFollowers;
        this->totalPosts = totalPosts;
        this->avgFavs = avgFavs;
        this->avgShares = avgShares;
    }

    // Getters

    std::string getPlatform() const {
        return platform;
    }

    std::string getParty() const {
        return party;
    }

    std::string getbioguideId() const {
        return bioguideId;
    }

    int getRowId() const {
        return rowId;
    }

    int getNumActiveAccounts() const {
        return numActiveAccounts;
    }

    int getMaxFollowers() const {
        return maxFollowers;
    }

    int getTotalPosts() const {
        return totalPosts;
    }

    int getAvgFavs() const {
        return avgFavs;
    }

    int getAvgShares() const {
        return avgShares;
    }

    // Setters

    void setPlatform(std::string platform) {
        this->platform = platform;
    }

    void setParty(std::string party) {
        this->party = party;
    }

    void setbioguideId(std::string bioguideId) {
        this->bioguideId = bioguideId;
    }

    void setRowId(int rowId) {
        this->rowId = rowId;
    }

    void setNumActiveAccounts(int numActiveAccounts) {
        this->numActiveAccounts = numActiveAccounts;
    }

    void setMaxFollowers(int maxFollowers) {
        this->maxFollowers = maxFollowers;
    }

    void setTotalPosts(int totalPosts) {
        this->totalPosts = totalPosts;
    }

    void setAvgFavs(int avgFavs) {
        this->avgFavs = avgFavs;
    }

    void setAvgShares(int avgShares) {
        this->avgShares = avgShares;
    }

    /**
     * Overloads stream insertion operator so it prints neatly.
     */
    friend std::ostream& operator << (std::ostream& outs, const Politician& pObj) {
        outs << std::fixed
             << std::left
             << std::setprecision(2)
             << std::setw(8) << pObj.getRowId()
             << std::setw(15) << pObj.getbioguideId()
             << std::setw(6) << pObj.getParty()
             << std::setw(12) << pObj.getPlatform()
             << std::setw(5) << pObj.getNumActiveAccounts()
             << std::setw(13) << pObj.getMaxFollowers()
             << std::setw(6) << pObj.getTotalPosts()
             << std::setw(6) << pObj.getAvgFavs()
             << std::setw(6) << pObj.getAvgShares();
        return outs;
    }
};

// Read data into a vector
bool loadFromFile(std::string filename, std::vector<Politician>& objs) {
    std::ifstream file;
    file.open(filename);

    // Returns false if file could not be opened
    if (!file) {
        return false;
    }

    // Otherwise...

    // Save header then move on
    std::string header = "";
    getline(file, header);

    // Read in data
    int count = 1;
    while (file && file.peek() != EOF) {

        // Make 'error' data in case something couldn't be read
        std::string platform = "n/a";
        std::string party = "n/a";
        std::string bioguideId = "n/a";

        int rowId = -1;
        int numAccountsActive = -1;
        int maxFollowers = -1;
        int totalPosts = -1;
        int avgFavs = -1;
        int avgShares = -1;

        char comma = ',';

        // input data
        file >> rowId;
        if (rowId != count) {
            std::cout << rowId << " !+ " << count << std::endl;
            return false;
        }
        file >> comma;

        // Get string data
        getline(file, platform, comma);
        getline(file, party, comma);
        getline(file, bioguideId, comma);

        // Get integer data
        file >> numAccountsActive;
        file >> comma;
        file >> maxFollowers;
        file >> comma;
        file >> totalPosts;
        file >> comma;
        file >> avgFavs;
        file >> comma;
        file >> avgShares;

        Politician p(rowId, platform, party, bioguideId,
                    numAccountsActive, maxFollowers, totalPosts,
                    avgFavs, avgShares);
        objs.push_back(p);
        count += 1;
    }
    file.close();
    return true;
}

// Calculation average # of posts republicans made and
// average # of posts democrats made.

void showAveragePostsByParty(std::vector<Politician>& objs) {
    // Refers to the number of republicans/democrats on facebook/twitter
    int numRepublicanFacebook = 0;
    int numRepublicanTwitter = 0;
    int numDemocratFacebook = 0;
    int numDemocratTwitter = 0;

    // Refers to total number of posts made by each party on facebook/twitter
    int totalRepublicanFacebook = 0;
    int totalRepublicanTwitter = 0;
    int totalDemocratFacebook = 0;
    int totalDemocratTwitter = 0;

    for (Politician& p : objs) {
        std::string party = p.getParty();
        std::string platform = p.getPlatform();
        int totalPosts = p.getTotalPosts();

        if (party.compare("R") == 0 || party.compare("(R)") == 0) {
            if (platform.compare("facebook") == 0) {
                numRepublicanFacebook += 1;
                totalRepublicanFacebook += totalPosts;
            }

            if (platform.compare("twitter") == 0) {
                numRepublicanTwitter += 1;
                totalRepublicanTwitter += totalPosts;
            }
        }

        if (party.compare("D") == 0 || party.compare("(D)") == 0) {
            if (platform.compare("facebook") == 0) {
                numDemocratFacebook += 1;
                totalDemocratFacebook += totalPosts;
            }

            if (platform.compare("twitter") == 0) {
                numDemocratTwitter += 1;
                totalDemocratTwitter += totalPosts;
            }
        }
    }

    int avgRepublicanFacebookPosts = totalRepublicanFacebook/numRepublicanFacebook;
    int avgRepublicanTwitterPosts = totalRepublicanTwitter/numRepublicanTwitter;

    int avgDemocratFacebookPosts = totalDemocratFacebook/numDemocratFacebook;
    int avgDemocratTwitterPosts = totalDemocratTwitter/numDemocratTwitter;

    // Format and Display
    std::cout << std::endl;
    std::cout << "Post Statistics by Party" << std::endl;
    std::cout << "For Posts Between: January 1, 2015 - May 31, 2020" << std::endl;
    std::cout << "--------------------------" << std::endl;
    std::cout << "Average Number of Republican Facebook Posts: " + std::to_string(avgRepublicanFacebookPosts) << std::endl;
    std::cout << "Average Number of Republican Twitter Posts: " + std::to_string(avgRepublicanTwitterPosts) << std::endl;
    std::cout << std::endl;
    std::cout << "Average Number of Democrat Facebook Posts: " + std::to_string(avgDemocratFacebookPosts) << std::endl;
    std::cout << "Average Number of Democrat Twitter Posts: " + std::to_string(avgDemocratTwitterPosts) << std::endl;
    std::cout << "-------------------------" << std::endl;

}

/**
 * Verifies files and alerts you where the problem is
 */
 void verifyAllFieldsSet(std::vector<Politician>& objs) {
     int i = 1;
     for (Politician& p : objs) {

         if (p.getRowId() != i) {
             std::cout << p.getRowId()
                       << i << std::endl;
         }
         if (p.getRowId() == -1) {
             std::cout << "Bad value for row ID at record "
                       << i << std::endl;
         }
         std::string platform = p.getPlatform();
         if (platform.compare("n/a") == 0) {
             std::cout << "Bad value for platform at record "
                       << i << std::endl;
         }

         std::string party = p.getParty();
         if (party.compare("n/a") == 0) {
             std::cout << "Bad value for party at record "
                       << i << std::endl;
         }

         std::string bioguideId = p.getbioguideId();
         if (bioguideId.compare("n/a") == 0) {
             std::cout << "Bad value for bioguideId at record "
                       << i << std::endl;
         }

         int numActiveAccounts = p.getNumActiveAccounts();
         if (numActiveAccounts == -1) {
             std::cout << "Bad value for numActiveAccounts at record "
                       << i << std::endl;
         }

         int maxFollowers = p.getMaxFollowers();
         if (maxFollowers == -1) {
             std::cout << "Bad value for maxFollowers at record "
                       << i << std::endl;
         }

         int totalPosts = p.getTotalPosts();
         if (totalPosts == -1) {
             std::cout << "Bad value for totalPosts at record "
                       << i << std::endl;
         }

         int avgFavs = p.getAvgFavs();
         if (avgFavs == -1) {
             std::cout << "Bad value for avgFavs at record "
                       << i << std::endl;
         }

         int avgShares = p.getAvgShares();
         if (avgShares == -1) {
             std::cout << "Bad value for avgShares at record "
                       << i << std::endl;
         }
         i++;

     }
 }

 /**
  * Politician object tests assertions
  */
 void politicianTest() {
    Politician test = Politician();

    // Tests setters and getters
    test.setRowId(1);
    assert (test.getRowId() == 1);
    test.setPlatform("facebook");
    assert (test.getPlatform() == "facebook");
    test.setParty("R");
    assert (test.getParty() == "R");
    test.setbioguideId("XXX");
    assert (test.getbioguideId() == "XXX");
    test.setNumActiveAccounts(2);
    assert (test.getNumActiveAccounts() == 2);
    test.setMaxFollowers(3);
    assert (test.getMaxFollowers() == 3);
    test.setTotalPosts(4);
    assert (test.getTotalPosts() == 4);
    test.setAvgFavs(5);
    assert (test.getAvgFavs() == 5);
    test.setAvgShares(6);
    assert (test.getAvgShares() == 6);

    // Test initialization
    Politician test2 = Politician(1, "twitter", "D", "xxx",
                                2, 3, 4, 5, 6);
     assert (test2.getRowId() == 1);
     assert (test2.getPlatform() == "twitter");
     assert (test2.getParty() == "D");
     assert (test2.getbioguideId() == "xxx");
     assert (test2.getNumActiveAccounts() == 2);
     assert (test2.getMaxFollowers() == 3);
     assert (test2.getTotalPosts() == 4);
     assert (test2.getAvgFavs() == 5);
     assert (test2.getAvgShares() == 6);
 }

#endif // POLITICIAN_H