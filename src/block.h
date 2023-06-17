/***********************************************************************
 * File: Block.h
 * Author: Tone
 * Create date: 2023/04/13
 * Editor: Raymin
 * Update Date: 2023/04/26
 * Description: This Program declare the Block class and some needed funcions
 * ***********************************************************************/
#pragma once

class Block {
private:
	bool isBlank, isBomb, isFlag, isQMark, isOpen;
	int nearBomb; /* Optional: for print GameAnswer -> redundent */

public:
	// Constructor
	Block();

	// get function
	bool getBlank(void) { return this->isBlank; }
	bool getBomb(void) { return this->isBomb; }
	bool getFlag(void) { return this->isFlag; }
	bool getQMark(void) { return this->isQMark; }
	bool getOpen(void) { return this->isOpen; }
	int getnearBomb(void) { return this->nearBomb; }

	// set function
	void setBlank(bool state) { this->isBlank = state; }
	void setBomb(bool state) { this->isBomb = state; }
	void setFlag(bool state) { this->isFlag = state; }
	void setQMark(bool state) { this->isQMark = state; }
	void setOpen(bool state) { this->isOpen = state; }
	void setnearBomb(int num) { this->nearBomb = num; }

	// function
};
