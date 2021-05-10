#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool gameWon = false;

int Intro()
{
	int decision = 0;
	cout << "Welcome to Ben's Noughts and Crosses..." << endl;
	while (decision != 1 && decision != 2 && decision != 3 && decision != 4)
	{
		cout << "\nSelect a mode:" << endl;
		cout << "1 - Local 2 Players" << endl;
		cout << "2 - Online 2 Players:" << endl;
		cout << "3 - Play AI:" << endl;
		cout << "4 - Quit" << endl;
		cin >> decision;
		if (decision != 1 && decision != 2 && decision != 3 && decision != 4)
		{
			system("CLS");
			cout << "Invalid Choice" << endl;
			cout << "Please try again..." << endl;
		}
	}
	return decision;
}

int Ending()
{
	int decision = 0;
	while (decision != 1 && decision != 2 && decision != 3)
	{
		cout << "\nWhat would you like to do:" << endl;
		cout << "1 - Play Again" << endl;
		cout << "2 - Main Menu" << endl;
		cout << "3 - Exit Game" << endl;
		cin >> decision;
		if (decision != 1 && decision != 2 && decision != 3)
		{
			system("CLS");
			cout << "Invalid Choice" << endl;
			cout << "Please try again..." << endl;
		}
	}
	return decision;
}

string** SetSolutions()
{
	string** sol = new string * [8];
	for (int i = 0; i < 8; i++)
	{
		sol[i] = new string[3];
	}
	sol[0][0] = "00";
	sol[0][1] = "02";
	sol[0][2] = "04";

	sol[1][0] = "00";
	sol[1][1] = "10";
	sol[1][2] = "20";

	sol[2][0] = "00";
	sol[2][1] = "12";
	sol[2][2] = "24";

	sol[3][0] = "02";
	sol[3][1] = "12";
	sol[3][2] = "22";

	sol[4][0] = "04";
	sol[4][1] = "12";
	sol[4][2] = "20";

	sol[5][0] = "04";
	sol[5][1] = "14";
	sol[5][2] = "24";

	sol[6][0] = "10";
	sol[6][1] = "12";
	sol[6][2] = "14";

	sol[7][0] = "20";
	sol[7][1] = "22";
	sol[7][2] = "24";

	return sol;
}

bool Valid(char** grid, int place, int player, string** solutions)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
		{
			if (grid[i][j] == (to_string(place)[0]))
			{
				if (0 < place && place <= 10) {
					return true;
				}
			}
		}
	return false;
}

void CheckWin(char** grid, int row, int col, int player, string** solutions)
{
	char token = (player == 1 ? 'X' : 'O');
	string rowColVal = to_string(row) + to_string(col);
	vector<int> matchingSol;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
		{
			if (rowColVal == solutions[i][j])
			{
				matchingSol.push_back(i);
			}
		}


	for (int i = 0; i < matchingSol.size(); i++)
	{
		if (grid[stoi(solutions[matchingSol[i]][0].substr(0,1))][stoi(solutions[matchingSol[i]][0].substr(1,1))] == token)
		{
			if (grid[stoi(solutions[matchingSol[i]][1].substr(0,1))][stoi(solutions[matchingSol[i]][1].substr(1,1))] == token)
			{
				if (grid[stoi(solutions[matchingSol[i]][2].substr(0,1))][stoi(solutions[matchingSol[i]][2].substr(1,1))] == token)
				{
					gameWon = true;
				}
			}
		}
	}
}

char** InitialiseGrid()
{
	char** grid = new char * [3];
	int number = 1;
	for (int i = 0; i < 3; i++)
	{
		grid[i] = new char[5];
		for (int j = 0; j < 5; j++)
		{
			if (j % 2) 
			{
				grid[i][j] = '|';
			}
			else 
			{
				grid[i][j] = (to_string(number)[0]);
				number++;
			}
		}
	}
	return grid;
}

void DisplayGrid(char** grid)
{
	cout << grid[2][0] << grid[2][1] << grid[2][2] << grid[2][3] << grid[2][4] << endl;
	cout << grid[1][0] << grid[1][1] << grid[1][2] << grid[1][3] << grid[1][4] << endl;
	cout << grid[0][0] << grid[0][1] << grid[0][2] << grid[0][3] << grid[0][4] << endl;
}

char** UpdateGrid(char** grid, int place, int player, string** solutions, int turn)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
		{
			if (grid[i][j] == (to_string(place)[0]))
			{
				if (player == 1)
				{
					grid[i][j] = 'X';
				}
				else
				{
					grid[i][j] = 'O';
				}
				if (turn > 4)
					CheckWin(grid, i, j, player, solutions);
			}
		}
	DisplayGrid(grid);
	return grid;
}

vector<pair<int,int>> CalculatePossibleMoves(char** grid)
{
	vector<pair<int, int>> possibleMoves;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
		{
			if (grid[i][j] != 'X' && grid[i][j] != 'O' && grid[i][j] != '|')
			{
				possibleMoves.push_back(make_pair(i, j));
			}
		}
	return possibleMoves;
}

int CheckUpOrDown(char** grid, int x, int y, int z, bool up)
{
	int value = 0;
	if (up)
	{

			if (grid[(z == 0 ? 1 : 0)][y] == 'O')
			{
				if (grid[(z == 2 ? 1 : 2)][y] == 'O')
				{
					value = 10;
				}
				value = 5;
			}
			else
			{
				if (grid[(z == 2 ? 1 : 2)][y] == 'O')
				{
					value = 5;
				}
			}
		
	}
	else
	{

			if (grid[x][(z == 0 ? 2 : 0)] == 'O')
			{
				if (grid[x][(z == 2 ? 4 : 2)] == 'O')
				{
					value = 10;
				}
				value = 5;
			}
			else
			{
				if (grid[x][(z == 2 ? 4 : 2)] == 'O')
				{
					value = 5;
				}
			}
		
	}
	return value;
}

int MinMax(vector<pair<int, int>> pM, char** grid, string** solutions)
{
	int value = 0;
	vector<pair<int, int>> newMoves;
	for (int i = 0; i < pM.size(); i++)
	{
		//checks up
		value = CheckUpOrDown(grid, pM[i].first, pM[i].second, 0, true);
		if (value == 10)
			return stoi(to_string(grid[pM[i].first][pM[i].second]));
		else if (value == 5)
			newMoves.push_back(pM[i]);
		value = CheckUpOrDown(grid, pM[i].first, pM[i].second, 2, true);
		if (value == 10)
			return stoi(to_string(grid[pM[i].first][pM[i].second]));
		else if (value == 5)
			newMoves.push_back(pM[i]);
		value = CheckUpOrDown(grid, pM[i].first, pM[i].second, 4, true);
		if (value == 10)
			return stoi(to_string(grid[pM[i].first][pM[i].second]));
		else if (value == 5)
			newMoves.push_back(pM[i]);

		//checks down
		value = CheckUpOrDown(grid, pM[i].first, pM[i].second, 0, true);
		if (value == 10)
			return stoi(to_string(grid[pM[i].first][pM[i].second]));
		else if (value == 5)
			newMoves.push_back(pM[i]);
		value = CheckUpOrDown(grid, pM[i].first, pM[i].second, 1, true);
		if (value == 10)
			return stoi(to_string(grid[pM[i].first][pM[i].second]));
		else if (value == 5)
			newMoves.push_back(pM[i]);
		value = CheckUpOrDown(grid, pM[i].first, pM[i].second, 2, true);
		if (value == 10)
			return stoi(to_string(grid[pM[i].first][pM[i].second]));
		else if (value == 5)
			newMoves.push_back(pM[i]);

		//checks diag
		if ((pM[i].first != 1 && pM[i].second != 2) || pM[i].first == 1 && pM[i].second == 2)
		{
			if (pM[i].first == 0 && pM[i].second == 0)
			{
				if (grid[1][2] == 'O')
				{
					if (grid[2][4] == 'O')
					{
						value = 10;
					}
				}
				else
				{
					if (grid[2][4] == 'O')
					{
						value = 5;
					}
				}
			}
		}
		if (value == 10)
			return stoi(to_string(grid[pM[i].first][pM[i].second]));
		else if (value == 5)
			newMoves.push_back(pM[i]);
	}
	if (newMoves.size() > 0)
	{
		int nextMove = rand() % newMoves.size();
		return stoi(to_string(grid[newMoves[nextMove].first][newMoves[nextMove].second]));
	}
	else 
	{
		int nextMove = rand() % pM.size();
		return stoi(to_string(grid[pM[nextMove].first][pM[nextMove].second]));
	}
}

void Local(char** grid, string** solutions)
{
	int player = 1;
	int turn = 1;
	do
	{
		cout << "Player " << player << " Make Move Between 1-9:";
		int place;
		cin >> place;

		if (Valid(grid, place, player, solutions))
		{
			grid = UpdateGrid(grid, place, player, solutions, turn);
			if (!gameWon) {
				if (player == 1)
					player = 2;
				else
					player = 1;
			}
			turn++;
		}
		else
			cout << "Invalid Position" << endl;

	} 	while (gameWon == false);
	cout << "\nWell done player " << player << " wins!" << endl;
}

void Online()
{

}

void AI(char** grid, string** solutions)
{
	int player = 1;
	int turn = 1;
	do
	{
		if (player == 1)
		{
			cout << "Player " << player << " Make Move Between 1-9:";
			int place;
			cin >> place;
			if (Valid(grid, place, player, solutions))
			{
				grid = UpdateGrid(grid, place, player, solutions, turn);
				if (!gameWon) {
					if (player == 1)
						player = 2;
					else
						player = 1;
				}
				turn++;
			}
			else
				cout << "Invalid Position" << endl;
		}
		else
		{
			cout << "AI's Move" << endl;
			vector<pair<int, int>> pM = CalculatePossibleMoves(grid);
			int place = 0;
			place = (MinMax(pM, grid, solutions)) - '0';
			grid = UpdateGrid(grid, place, player, solutions, turn);
			if (!gameWon) {
				if (player == 1)
					player = 2;
				else
					player = 1;
			}
			turn++;
		}



	} while (gameWon == false);
	cout << "\nWell done player " << player << " wins!" << endl;
}


int main()
{
	int quit = 0;
	do
	{
		if (quit == 3)
			return(0);
		char **grid = {};
		system("CLS");
		int mode = Intro();
		if (mode == 4)
			return(0);
		do
		{
			if (quit == 3)
				return(0);
			system("CLS");
			grid = InitialiseGrid();
			DisplayGrid(grid);
			string **solutions = {}; 
			solutions = SetSolutions();
			switch (mode) {
			case 1:
				Local(grid, solutions);
				break;
			case 2:
				break;
			case 3:
				AI(grid, solutions);
				break;
			}
			gameWon = false;
			quit = Ending();
		} while (quit == 1);
	} while (!gameWon);
}