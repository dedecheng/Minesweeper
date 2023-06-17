/***********************************************************************
 * File: Block.cpp
 * Author: Raymin
 * Create date: 2023/04/13
 * Editor: Raymin
 * Update Date: 2023/04/26
 * Description: This program define the class Block and initialize all variables
 * ***********************************************************************/
#include "Block.h"

Block::Block()
	:isBlank(false), isBomb(false), isFlag(false), isQMark(false), isOpen(false), nearBomb(0) {};