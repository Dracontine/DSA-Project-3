#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include "Game.h"

using namespace std;

void ReadFile(string filename, vector<Game>& games)
{
    // Load the file
    ifstream inFile(filename);

    // Read the csv file + store the data in Game objects
    if (inFile.is_open())
    {
        // 1. Read the heading data from the file
        string lineFromFile;
        getline(inFile, lineFromFile);

        // Get all entries/records from the file one line at a time

        while (getline(inFile, lineFromFile))
        {
            istringstream stream(lineFromFile);
    
            string date;
            int season;
            string homeTeam;
            string visitor;
            string finalScore;
            int homeGoals;
            int visitorGoals;
            string division;
            int tier;
            int totalGoals;
            int goalDifference; 
            string result; 

            string token;

            getline(stream, token, ',');
            date = token;

            getline(stream, token, ',');
            season = stoi(token);

            getline(stream, token, ',');
            homeTeam = token;

            getline(stream, token, ',');
            visitor = token;

            getline(stream, token, ',');
            finalScore = token;

            getline(stream, token, ',');
            homeGoals = stoi(token);

            getline(stream, token, ',');
            visitorGoals = stoi(token);

            getline(stream, token , ',');
            division = token;

            getline(stream, token, ',');
            tier = stoi(token);

            getline(stream, token, ',');
            totalGoals = stoi(token);

            getline(stream, token, ',');
            goalDifference = stoi(token);

            getline(stream, token, ',');
            result = token;

            Game game(date, season, homeTeam, visitor, finalScore, homeGoals, visitorGoals, division, tier, totalGoals,
                      goalDifference, result);

            games.push_back(game);
        }

    }

}

// Merge two subarrays from vector

void Merge(vector<Game>& games, int left, int mid, int right)
{
    // Create X - games[left...mid] & Y - games[mid+1..right]

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Game> X;
    vector<Game> Y;
    X.resize(n1);
    Y.resize(n2);


    for (int i = 0; i < n1; i++)
    {
        X[i] = games[left + i];
    }

    for (int j = 0; j < n2; j++)
    {
        Y[j] = games[mid + 1 + j];
    }

    // Merge the vectors X and Y into games

    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (X[i].GetYear() <= Y[j].GetYear())
        {
            games[k] = X[i];
            i++;
        }
        else
        {
            games[k] = Y[j];
            j++;
        }

        k++;
    }

    // When we run out of elements in X and Y append the remaining elements

    while (i < n1)
    {
        games[k] = X[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        games[k] = Y[j];
        j++;
        k++;
    }


}

// Code taken from COP3530 - Sorting - Lecture Slides 89,90.
// This sorting algorithm orders the games by season/year played.
void MergeSort(vector<Game>& games, int left, int right)
{
    // m is the point where the array is divided into two sub-arrays
    if (left < right)
    {
        // mid is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;
        MergeSort(games, left, mid);
        MergeSort(games, mid + 1, right);

        // Merge the sorted subarrays
        Merge(games, left, mid, right);
    }
    
}


// Code for the three functions below were taken from COP3530 - Sorting - Lecture Slides 122
void Swap(Game* a, Game* b)
{
    Game t = *a;
    *a = *b;
    *b = t;
}

// Below QuickSort Algorithm sorts the Games in the alphabetical order of the away/visiting team
// i.e. this algorithm is used only when the home team parameter is entered.

int PartitionAway(vector<Game>& games, int low, int high)
{
    string pivot = games[low].GetAwayTeam();
    int up = low;
    int down = high;

    while (up < down)
    {
        for (int i = up; i < high; i++)
        {
            if (games[up].GetAwayTeam() > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--)
        {
            if (games[down].GetAwayTeam() < pivot)
                break;
            down--;
        }
        if (up < down)
        {
            Swap(&games[up], &games[down]);
        }            
    }
     Swap(&games[low], &games[down]);

    return down;
}

void QuickSortAway(vector<Game>& games, int low, int high)
{
    if (low < high)
    {
        int pivot = PartitionAway(games, low, high);
        QuickSortAway(games, low, pivot - 1);
        QuickSortAway(games, pivot + 1, high);
    }
}

// Below QuickSort Algorithm sorts the games in the alphabetical order of the home team
// i.e. this algorithm is used only when the away team parameter is entered.

int PartitionHome(vector<Game>& games, int low, int high)
{
    string pivot = games[low].GetHomeTeam();
    int up = low;
    int down = high;

    while (up < down)
    {
        for (int i = up; i < high; i++)
        {
            if (games[up].GetHomeTeam() > pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--)
        {
            if (games[down].GetHomeTeam() < pivot)
                break;
            down--;
        }
        if (up < down)
        {
            Swap(&games[up], &games[down]);
        }
    }
    Swap(&games[low], &games[down]);

    return down;
}

void QuickSortHome(vector<Game>& games, int low, int high)
{
    if (low < high)
    {
        int pivot = PartitionHome(games, low, high);
        QuickSortHome(games, low, pivot - 1);
        QuickSortHome(games, pivot + 1, high);
    }
}

// Returns a vector of games played by the home team
// Will be used when only the HomeGame Field has an input.
vector<Game> FilterHomeGames(string homeTeam, vector<Game>& games)
{
    homeTeam = "\"" + homeTeam + "\"";

    vector<Game> homeTeamGames;

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i].GetHomeTeam() == homeTeam)
            homeTeamGames.push_back(games[i]);
    }

    return homeTeamGames;
}

// Returns a vector of games played by the home team
// Will be used when only the AwayGame Field has an input.
vector<Game> FilterAwayGames(string awayTeam, vector<Game>& games)
{
    awayTeam = "\"" + awayTeam + "\"";

    vector<Game> awayTeamGames;

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i].GetAwayTeam() == awayTeam)
            awayTeamGames.push_back(games[i]);
    }

    return awayTeamGames;
}

// Returns a vector of games played in a given year
// Will be used when only the Year Field has an input
vector<Game> FilterByYear(string year, vector<Game>& games)
{
    vector<Game> yearGames;
    
    for (char c : year)
    {
        if (isdigit(c) == false)
            return yearGames;
    }

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i].GetYear() == stoi(year))
            yearGames.push_back(games[i]);
    }

    return yearGames;
}

// Returns a vector of Games with the following specified parameters - HomeTeam, AwayTeam/Visitor, Year
vector<Game> FilterByAll(string homeTeam, string awayTeam, string year, vector<Game>& games)
{
    vector<Game> specificGames;

    homeTeam = "\"" + homeTeam + "\"";
    awayTeam = "\"" + awayTeam + "\"";

    for (char c : year)
    {
        if (isdigit(c) == false)
            return specificGames;
    }

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i].GetYear() == stoi(year) && games[i].GetAwayTeam() == awayTeam && games[i].GetHomeTeam() == homeTeam)
            specificGames.push_back(games[i]);
    }

    return specificGames;
    
}

// Returns a vector of Games with the following specified parameters - HomeTeam, AwayTeam/Visitor
vector<Game> FilterHomeAway(string homeTeam, string awayTeam, vector<Game>& games)
{
    vector<Game> specificGames;

    homeTeam = "\"" + homeTeam + "\"";
    awayTeam = "\"" + awayTeam + "\"";

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i].GetAwayTeam() == awayTeam && games[i].GetHomeTeam() == homeTeam)
            specificGames.push_back(games[i]);
    }
    return specificGames;
}

// Returns a vector of Games with the following specified parameters - HomeTeam, Year
vector<Game> FilterHomeYear(string homeTeam, string year, vector<Game>& games)
{
    vector<Game> yearGames;

    homeTeam = "\"" + homeTeam + "\"";

    for (char c : year)
    {
        if (isdigit(c) == false)
            return yearGames;
    }

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i].GetYear() == stoi(year) && games[i].GetHomeTeam() == homeTeam)
            yearGames.push_back(games[i]);
    }

    return yearGames;
}

// Returns a vector of Games with the following specified parameters - AwayTeam, Year
vector<Game> FilterAwayYear(string awayTeam, string year, vector<Game>& games)
{
    vector<Game> yearGames;

    awayTeam = "\"" + awayTeam + "\"";

    for (char c : year)
    {
        if (isdigit(c) == false)
            return yearGames;
    }

    for (int i = 0; i < games.size(); i++)
    {
        if (games[i].GetYear() == stoi(year) && games[i].GetAwayTeam() == awayTeam)
            yearGames.push_back(games[i]);
    }

    return yearGames;
}

int main()
{
    // This vector will hold all the games from the csv file

    vector<Game> games;
    

    // Reading data from the csv file that contains the desired information
    ReadFile("england.csv", games);

    string homeTeam;
    string awayTeam;
    string year;

    int option;
    int option2;
    
    while (true)
    {
        cout << "1. Home Team Only" << endl;
        cout << "2. Away Team Only" << endl;
        cout << "3. Year Only" << endl;
        cout << "4. Home Team and Away Team" << endl;
        cout << "5. Home Team and Year" << endl;
        cout << "6. Away Team and Year" << endl;
        cout << "7. Home Team, Away Team, and Year" << endl;
        cout << "8. Exit" << endl;

        cin >> option;

        if (option == 1)
        {    
            string homeTeam;

            cout << "Enter Home Team Name : \n";

            getline(cin >> ws, homeTeam);
            
            vector<Game> homeGames = FilterHomeGames(homeTeam, games);


            cout << "1. Lexicographic sort (Names of opponents)" << endl;
            cout << "2. Sort by Year" << endl;
      
            while (true)
            {
                cin >> option2;

                if (option2 == 1)
                    break;
                else if (option2 == 2)
                    break;
                else
                {
                    cout << "Not a valid option! Please choose either 1 or 2" << endl;
                }
                
            }
            
            if (option2 == 1)
            {
                QuickSortAway(homeGames, 0, homeGames.size() - 1);
            }
            else if (option2 == 2)
            {
                MergeSort(homeGames, 0, homeGames.size() - 1);
            }

            cout << "Printing Games : " << endl;

            for (auto x : homeGames)
            {
                x.PrintGame();
            }

            cout << endl;
    
        }
        else if (option == 2)
        {
            cout << "Enter Away Team Name : " << endl;

            getline(cin >> ws, awayTeam);

            cin >> awayTeam;

            vector<Game> awayGames = FilterAwayGames(awayTeam, games);

            cout << "1. Lexicographic sort (By the names of opponents)" << endl;
            cout << "2. Sort by Year" << endl;

            while (true)
            {
                cin >> option2;

                if (option2 == 1)
                    break;
                else if (option2 == 2)
                    break;
                else
                {
                    cout << "Not a valid option! Please choose either 1 or 2" << endl;
                }
            }

            if (option2 == 1)
            {
                QuickSortAway(awayGames, 0, awayGames.size() - 1);
            }
            else if (option2 == 2)
            {
                MergeSort(awayGames, 0, awayGames.size() - 1);
            }

            cout << "Printing Games : " << endl;

            for (auto x : awayGames)
            {
                x.PrintGame();
            }

            cout << endl;

        }
        else if (option == 3)
        {
            cout << "Enter Year (1888 - 2021): " << endl;
            
            while (true)
            {
                cin >> year;

                for (auto x : year)
                {
                    if (isdigit(x) == false)
                    {
                        cout << "Please enter a valid year between 1888 and 2021" << endl;
                        continue;
                    }
                        
                }

                if (stoi(year) >= 1888 && stoi(year) <= 2021)
                {
                    break;
                }
                else
                {
                    cout << "Please enter a valid year between 1888 and 2021" << endl;
                }
            }

            vector<Game> yearGames = FilterByYear(year, games);

            cout << "1. Lexicographic sort (By Home Team Names)" << endl;
            cout << "2. Lexicographic sort (By Away Team Names)" << endl;

            while (true)
            {
                cin >> option2;

                if (option2 == 1)
                    break;
                else if (option2 == 2)
                    break;
                else
                {
                    cout << "Not a valid option! Please choose either 1 or 2" << endl;
                }
            }

            if (option2 == 1)
            {
                QuickSortHome(yearGames, 0, yearGames.size() - 1);
            }
            else if (option2 == 2)
            {
                QuickSortAway(yearGames, 0, yearGames.size() - 1);
            }

            cout << "Printing Games : " << endl;

            for (auto x : yearGames)
            {
                x.PrintGame();
            }

            cout << endl;

        }
        else if (option == 4)
        {
            cout << "Enter Home Team Name : " << endl;

            getline(cin >> ws, homeTeam);
            

            cout << "Enter Away Team Name : " << endl;

            getline(cin >> ws, awayTeam);
            
            vector<Game> specificGames = FilterHomeAway(homeTeam, awayTeam, games);
           
            cout << "Printing Games : " << endl;

            for (auto x : specificGames)
            {
                x.PrintGame();
            }

            cout << endl;
         
        }
        else if (option == 5)
        {

        }
        else if (option == 6)
        {

        }
        else if (option == 7)
        {
           
        }
        else if (option == 8)
        {
            break;
        }
        else
        {
            cout << "Not a valid input! Please input a number between 1 and 8!!" << endl;
        }

    }
    
    cout << endl;
    cout << "Thank you for using the FindFootball application" << endl;

    return 0;
    
}
