/***********************************************************************
 * File: main.cpp
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--04-26
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--04-26
 * Description: This program control whole minesweeper operating
***********************************************************************/

#include<iostream>
#include<string>
#include <sstream>
#include "Block.h"
#include "Command.h"
#include "variable.h"
#include "main.h"
#include <fstream>
#include <io.h>

using namespace std;

int rowSize, colSize;//boundary of GameBoard
Block board[100][100];//GameBoard
State state; //current game state
bool load; //if board is loaded


int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		cout << "arg error!" << endl;
		return 0;
	}
	else if (argc == 1)
	{
		return RunGUI(argc, argv);
	}
	else if (argc == 4 && string(argv[1]) == string("CommandFile"))
	{
		RunCommandFile(argv[2], argv[3]);
	}
	else if (argc == 2 && string(argv[1]) == string("CommandInput"))
	{
		RunCommandInput();
	}
	else if (argc == 2 && string(argv[1]) == string("GUI"))
	{
		return RunGUI(argc, argv);
	}
	else
	{
		cout << "arg error!" << endl;
		return 0;
	}

}

/**
  * Intent : Run GUI mode
  * Pre : argc and argv
  * Post : integer
 */
int RunGUI(int argc, char* argv[])
{
	return 0;
}

/**
  * Intent : Run minesweeper and read input from CommandFile
  * Pre : two string, one is inputFile, one isoutputFile.
  * Post : none
 */
void RunCommandFile(char a[], char b[])
{
	//initialize
	state = State::Standby;
	load = false;
	string input, cmd, c = string(a), o = string(b);
	fstream inputFile, outputFile;
	inputFile.open(c);
	outputFile.open(o);

	//input till EOF
	while (getline(inputFile, input))
	{
		stringstream ss(input);//use ss to cut input string
		ss >> cmd;

		//determine what command would execute
		if (cmd == "Load")
		{
			if (state == State::Standby)
			{
				ss >> cmd;//boardfile, random count or random rate
				bool tof = 0;
				//determine what type
				if (cmd == "BoardFile")
				{
					ss >> cmd;//filename
					if (_access(cmd.c_str(), 0) != -1)
					{
						tof = true;
						loadBoardFile(cmd);
					}
				}
				else if (cmd == "RandomCount")
				{
					int m, n, count;

					ss >> m >> n >> count;

					if (m * n >= count && m > 0 && n > 0 && count >= 0)
					{
						tof = true;
						loadRandomCount(m, n, count);
					}
				}
				else if (cmd == "RandomRate")
				{
					int m, n;
					double rate;

					ss >> m >> n >> rate;

					if (m > 0 && n > 0 && rate >= 0 && rate <= 1)
					{
						tof = true;
						loadRandomRate(m, n, rate);
					}

				}

				if (tof)
				{
					load = true;
					outputFile << "<" << input << "> : Success" << endl;
				}
				else
				{
					outputFile << "<" << input << "> : Failed" << endl;
				}
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "StartGame")
		{
			if (load && state == State::Standby)
			{
				//chang game state
				state = State::Playing;

				outputFile << "<" << input << "> : Success" << endl;
			}
			else //if board is not loaded, we cant start game
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Print")
		{
			ss >> cmd;

			outputFile << "<" << input << "> : ";

			print(cmd, outputFile);
		}
		else if (cmd == "LeftClick")
		{
			int row, col;

			ss >> row >> col;

			if (state == State::Playing && isAbleLeftclick(row, col))
			{
				leftClick(row, col);

				outputFile << "<" << input << "> : Success" << endl;

				if (state == State::Gameover)
				{
					if (winOrNot())
					{
						outputFile << "You win the game" << endl;
					}
					else
					{
						outputFile << "You lose the game" << endl;
					}
				}
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "RightClick")
		{
			int row, col;

			ss >> row >> col;

			if (state == State::Playing && isAbleRightclick(row, col))
			{
				rightClick(row, col);

				outputFile << "<" << input << "> : Success" << endl;
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Replay")
		{
			if (state == State::Gameover)
			{
				//reset information
				state = State::Standby;
				load = false;

				outputFile << "<" << input << "> : Success" << endl;
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Quit")
		{
			if (state == State::Gameover)
			{
				outputFile << "<" << input << "> : Success" << endl;

				return;
			}
			else
			{
				outputFile << "<" << input << "> : Failed" << endl;
			}
		}
		else
		{
			outputFile << "<" << input << "> : Failed" << endl;
		}

		ss.str("");
		ss.clear();
	}

	inputFile.close();
	outputFile.close();

	return;
}

/**
  * Intent : Run minesweeper and read input from console
  * Pre : none
  * Post : none
 */
void RunCommandInput()
{
	//initialize
	state = State::Standby;
	load = false;
	string input, cmd;

	//input till EOF
	while (getline(cin, input))
	{
		stringstream ss(input);//use ss to cut input string
		ss >> cmd;

		//determine what command would execute
		if (cmd == "Load")
		{
			if (state == State::Standby)
			{
				ss >> cmd;//boardfile, random count or random rate

				bool tof = 0;

				//determine what type
				if (cmd == "BoardFile")
				{
					ss >> cmd;//filename

					if (_access(cmd.c_str(), 0) != -1)
					{
						tof = true;
						loadBoardFile(cmd);
					}
				}
				else if (cmd == "RandomCount")
				{
					int m, n, count;

					ss >> m >> n >> count;

					if (m * n >= count && m > 0 && n > 0 && count >= 0)
					{
						tof = true;
						loadRandomCount(m, n, count);
					}
				}
				else if (cmd == "RandomRate")
				{
					int m, n;
					double rate;

					ss >> m >> n >> rate;

					if (m > 0 && n > 0 && rate >= 0 && rate <= 1)
					{
						tof = true;
						loadRandomRate(m, n, rate);
					}

				}

				if (tof)
				{
					load = true;
					cout << "<" << input << "> : Success" << endl;
				}
				else
				{
					cout << "<" << input << "> : Failed" << endl;
				}
			}
			else
			{
				cout << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "StartGame")
		{
			if (load && state == State::Standby)
			{
				//chang game state
				state = State::Playing;

				cout << "<" << input << "> : Success" << endl;
			}
			else //if board is not loaded, we cant start game
			{
				cout << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Print")
		{
			ss >> cmd;

			cout << "<" << input << "> : ";

			print(cmd);
		}
		else if (cmd == "LeftClick")
		{
			int row, col;

			ss >> row >> col;

			if (state == State::Playing && isAbleLeftclick(row, col))
			{
				leftClick(row, col);

				cout << "<" << input << "> : Success" << endl;

				if (state == State::Gameover)
				{
					if (winOrNot())
					{
						cout << "You win the game" << endl;
					}
					else
					{
						cout << "You lose the game" << endl;
					}
				}
			}
			else
			{
				cout << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "RightClick")
		{
			int row, col;
			ss >> row >> col;
			if (state == State::Playing && isAbleRightclick(row, col))
			{
				rightClick(row, col);
				cout << "<" << input << "> : Success" << endl;
			}
			else
			{
				cout << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Replay")
		{
			if (state == State::Gameover)
			{
				//reset information
				state = State::Standby;
				load = false;

				cout << "<" << input << "> : Success" << endl;
			}
			else
			{
				cout << "<" << input << "> : Failed" << endl;
			}
		}
		else if (cmd == "Quit")
		{
			if (state == State::Gameover)
			{
				cout << "<" << input << "> : Success" << endl;
				return;
			}
			else
			{
				cout << "<" << input << "> : Failed" << endl;
			}
		}
		else
		{
			cout << "<" << input << "> : Failed" << endl;
		}

		ss.str("");
		ss.clear();
	}

	return;
}

/**
  * Intent : whether point(r,c) is in board
  * Pre : two integer
  * Post : bool
 */
bool isInBoard(int r, int c)
{
	//test if in range
	if (r >= 0 && r < rowSize && c >= 0 && c < colSize)return true;
	else return false;
}

/**
  * Intent : whether point(r,c) is able to rightclick
  * Pre : two integer
  * Post : bool
 */
bool isAbleRightclick(int r, int c)
{
	//it has to be in board and not opened
	if (!isInBoard(r, c)) return false;
	if (board[r][c].getOpen()) return false;
	else return true;
}

/**
  * Intent : whether point(r,c) is able to leftclick
  * Pre : two integer
  * Post : bool
 */
bool isAbleLeftclick(int r, int c)
{
	//it has to be in board, not opened and not flag.
	if (!isInBoard(r, c)) return false;
	if (board[r][c].getOpen() || board[r][c].getFlag()) return false;
	else return true;
}