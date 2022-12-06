#pragma once
#include <string>

using namespace std;


// The Game class stores the data from the csv file in a Game object.

class Game
{
private:
	string date;
	int season;
	string homeTeam;
	string visitor;
	string finalScore;
	int homeGoals;
	int visitorGoals;
	string division;
	int tier;
	int totalGoals; // homeGoals + visitorGoals
	int goalDifference; // From the home team's perespective
	string result; // 'A' means away team, 'H' means home team

public:
	Game();

	Game(string _date, int _season, string _homeTeam, string _visitor, string _finalScore, int _homeGoals, int _visitorGoals,
		string _division, int _tier, int _totalGoals, int _goalDifference, string _result);

	void PrintGame();

};

