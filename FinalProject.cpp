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

void MergeSort(vector<Game>& games, int left, int right)
{
    // m is the point where the array is divided into two sub-arrays
    if (left < right)
    {
        // mid is the point where the array is divided into two subarrays
        int mid = left + (right - left) / 2;
        MergeSort(games, left, mid);
        MergeSort(games, mid + 1, right);
    }


}

// Merge two subarrays from vector

void merge(vector<Game>& games, int left, int mid, int right)
{
    // Create X - games[left...mid] & Y - games[mid+1..right]

    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<Game> X, Y;

    for (int i = 0; i < n1; i++)
    {
        X[i] = games[left + i];
    }

    for (int j = 0; j < n2; j++)
    {

    }



}


int main()
{
    // This vector will hold all the games from the csv file

    vector<Game> games;

    ReadFile("england.csv", games);

    string homeTeam;
    string awayTeam;
    string year;

    
    while (true)
    {
        cout << "Enter Home Team : " << endl;
        cin >> homeTeam;
        
        cout << "Enter Away Team : " << endl;
        cin >> awayTeam;

        cout << "Enter Year : " << endl;
        cin >> year;

        break;

    }
   
    cout << games.size() << endl;

    for (int i = 0; i < 10; i++)
    {
        games[i].PrintGame();
    }



    
}
