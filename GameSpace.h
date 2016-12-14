#ifndef __GAME_SPACE_H__
#define __GAME_SPACE_H__
#include "cocos2d.h"
#include"Block.h"
#include"State.h"

USING_NS_CC;

class MapNode {
public:
	int iType;
	int iIndexNum;
	int iRecord;
	void setNode(int itype, int index);
	void changeRecord();
	bool isPass() { return iRecord == 0 ? true : false; }
};

class GameSpace
{
public:
	GameSpace(State* sta);				//构造函数
	//~GameSpace();
	bool canDelete(int x, int y);
	void UDLRDelete(int x, int y);
	void releaseMemory();				//游戏结束，释放内存
	void blockDrop();					//删除方块后，上方方块降落
	void moveLeft();					//底排方块向左对齐
	void cleanRecord();
	bool isOver();						//游戏是否结束的判定
	void Clear();
	Block* blocks[10][10];
	int iNumOfBlocks = 0;
	int iCurrentType;
	int iScore = 0;
	State* GameSpaceState;
	MapNode* map[10][10];

private:
	
};


#endif