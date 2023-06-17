/***********************************************************************
 * File: variable.h
 * Author: Tone
 * Create date: 2023/04/13
 * Editor: Tone
 * Update Date: 2023/04/26
 * Description: This program declare some external variables
 * ***********************************************************************/
#pragma once
#include "Block.h"
#include <string>

extern int rowSize, colSize;
extern Block board[100][100];
enum class State
{
	Standby,
	Playing,
	Gameover
};
extern State state;
