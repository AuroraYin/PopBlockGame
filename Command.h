#pragma once
#include"GameSpace.h"

class BaseCommand
{
public:
	virtual ~BaseCommand() {}
	virtual int* Execute() = 0;
	virtual int* Unexecute() = 0;
};


class GameCommand :public BaseCommand {
public:
	GameCommand(GameSpace*gs) { //构造函数
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				int iIndex = i + j * 10;
				intCommand[iIndex] = gs->map[i][j]->iType;
			}
		}
	}
private:
	int intCommand[100];
	int * Execute();
	int * Unexecute();
};

class ScoreCommand :public BaseCommand {
public:
	ScoreCommand(int iScore) { //构造函数
		intCommand[0] = iScore;
	}
private:
	int intCommand[1];
	int* Execute() { return intCommand; }
	int* Unexecute() { return intCommand; }
};