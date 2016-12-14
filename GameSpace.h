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
	GameSpace(State* sta);				//���캯��
	//~GameSpace();
	bool canDelete(int x, int y);
	void UDLRDelete(int x, int y);
	void releaseMemory();				//��Ϸ�������ͷ��ڴ�
	void blockDrop();					//ɾ��������Ϸ����齵��
	void moveLeft();					//���ŷ����������
	void cleanRecord();
	bool isOver();						//��Ϸ�Ƿ�������ж�
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