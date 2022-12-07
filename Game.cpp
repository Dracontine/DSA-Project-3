#include "Game.h"
#include<iostream>

using namespace std;

Game::Game()
{
	 date = "";
	 season = 0;
	 homeTeam = "";
	 visitor = "";
	 finalScore = "";
	 homeGoals = 0;
	 visitorGoals = 0;
	 division = "";
	 tier = 0;
	 totalGoals = 0; // homeGoals + visitorGoals
	 goalDifference = 0; // From the home team's perespective
	 result = ""; // 'A' means away team, 'H' means home team
}

Game::Game(string _date, int _season, string _homeTeam, string _visitor, string _finalScore, int _homeGoals, int _visitorGoals,
	string _division, int _tier, int _totalGoals, int _goalDifference, string _result)
{
	 date = _date;
	 season = _season;
	 homeTeam = _homeTeam;
	 visitor = _visitor;
	 finalScore = _finalScore;
	 homeGoals = _homeGoals;
	 visitorGoals = _visitorGoals;
	 division = _division;
	 tier = _tier;
	 totalGoals = _totalGoals;
	 goalDifference = _goalDifference; 
	 result = _result; 
}

void Game::PrintGame()
{
	cout << date << " | ";
	cout << season << " | ";
	cout << homeTeam << " | ";
	cout << visitor << " | ";
	cout << finalScore << " | ";
	cout << result << endl;
}

int Game::GetYear()
{
	return this->season;
}

string Game::GetAwayTeam()
{
	return this->visitor;
}

string Game::GetHomeTeam()
{
	return this->homeTeam;
}

void Game::PrintYear()
{
	cout << this->season << endl;
}

