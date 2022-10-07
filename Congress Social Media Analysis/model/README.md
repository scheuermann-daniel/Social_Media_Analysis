Daniel Scheuermann

The dataset I am used was obtained from pewresearch.org. It’s a nonprofit organization which gathers data through public opinion polling,
demographic research, and content analysis. All data on their site is free, however you do need to sign up for an account. The dataset I used
is for the year 2015-2020. It had 12 fields, however some are currently empty and so I have deleted them. This leaves the remaining fields to
be:

* rowId: Integer. Not in the original data set. I added this so each row had a unique identifier allowing for ease of access in finding specific rows.
* platform: String.The social media outlet which was posted on. This is a categorical variable.
* party: String. The political party of the congressperson posting. This is also a categorical variable. It should be noted that they use
  abbreviations for this (D or R).
* buiguideId: String Identifier. The Biographical Directory of the US Congress identifier for the politician.
* numActiveAccounts: Integer. How many active accounts they have on each platform.
* maxFollowers: Integer. how many people are following them.
* totalPosts: Integer. How many times they posted on that account.
* avgFavs: Integer. The number of interactions that the politicians average post received.
* avgShares: Integer. The number of shares on the politicians average post.
  
Peculiarities: The 'party' column either has 'R' '(R)' '(D)' or 'D'. This creates a spectrum of the political party of the politician. For ease of access in analyzing basic Republican vs Democratic social media statistics, I treated 'R' and '(R)' as the same and 'D' and '(D)' as the same.
  
I chose this set because social media is so prominent now and I thought it’d be cool to see some stats on it regarding the people who run our
  country.

The entries, by default, are ordered by platform and, within each platform, ordered by bioguideId. Meaning, the first half of the dataset is all the 'facebook' platform and then within that section, it's ordered by the bio ID (A000055, A000360, etc).

Demonstrating each function working is simple, as in each function there is something displayed if it works correctly and then an error message if something works incorrectly. Here are the main functions and how we know they work:
* While the loadFromFile function in itself doesn't display anything if there's an error (unless the file can't be opened, in which it returns 'false'), the values are all initialized to an impossible  value (-1 for integers, 'n/a' for strings) and the verifyAllFieldsSet function makes sure there's no impossible values in the data set, displaying where they are if there are any.
  * There's also a counter in main.cpp when we call the loadFromFile function, counting each row read. Since the following is displayed:
    ````
    1078 records read from file
    The first row ID read was 1
    The last row ID read was 1078
    ````
  * And since there are 1078 lines in the dataset, we know that each line was read in correctly.
* We also know that each class function (Setters and Getters) work correctly since the function politicianTest tests them all by setting them to something using the setter methods, then using the getter methods to assert them. If they failed, this would return an error. However, since there is no error, we know that there is no problems with those methods.

Finally, my calculation function essentially calculates the average number of facebook/twitter posts for each political party. The result of this function was:
````
Post Statistics by Party
For Posts Between: January 1, 2015 - May 31, 2020
--------------------------
Average Number of Republican Facebook Posts: 724
Average Number of Republican Twitter Posts: 1521

Average Number of Democrat Facebook Posts: 993
Average Number of Democrat Twitter Posts: 2446
-------------------------
````
We can be sure that this works because a simple excel sheet calculation (doing it manually) yields the same result. The function works by adding all the total posts for each democratic/republican politician and dividing it by the number of politicians in that party.

In the end, I was surprised by the result! Since our former President, Donald Trump, is known to be quite the active social media poster, I assumed that since he had such a large republican follower base, they would've been the same. Instead, It seems like democratic politicians during that time period have almost 1000 more twitter posts!