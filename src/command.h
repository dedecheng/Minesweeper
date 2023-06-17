/***********************************************************************
 * File: Command.h
 * Author: Tone
 * Create date: 2023/04/13
 * Editor: Tone
 * Update Date: 2023/04/13
 * Description: This program declare some needed funcions in the minesweeper
 * ***********************************************************************/
#pragma once
#include "Block.h"
#include <string>
#include <fstream>

void loadBoardFile(std::string filename); // load board file
void loadRandomCount(int m, int n, int count); // load random count
void loadRandomRate(int m, int n, double rate); // load random rate
void print(std::string info, std::fstream& out); // print on file
void print(std::string infot); // print on the console
void leftClick(int x, int y);
void rightClick(int x, int y);
bool winOrNot();