/***********************************************************************
 * File: main.h
 * Author: KUAN-TE CHENG (B11132007)
 * Create Date: 2023--04-26
 * Editor: KUAN-TE CHENG (B11132007)
 * Update Date: 2023--04-26
 * Description: This Program declare some needed funcions in the minesweeper
***********************************************************************/

#pragma once
#include "Block.h"

bool isInBoard(int r, int c);
bool isAbleRightclick(int r, int c);//if can be flaged. if has been opened, we cant flag it
bool isAbleLeftclick(int r, int c);//if can be opened. if has been opened and flaged, we cant open it
int RunGUI(int argc, char* argv[]);//GUI mode
void RunCommandFile(char[], char[]);
void RunCommandInput();
