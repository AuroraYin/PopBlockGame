#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cocos2d.h"
USING_NS_CC;

class Block
{
public:
	int posX;
	int posY;
	int type;                                             //标示方块的种类
	Sprite* block;                                        //用于显示方块的精灵对象
	void blockDelete();                                   //删除方块
	Block(int type, int x, int y);
	void blockInit(int type, int x, int y);               //初始化方块
	void moveTo(int x, int y);                            //方块移动
};
#endif