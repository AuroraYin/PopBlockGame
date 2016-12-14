#include "Block.h"
#include "cocos2d.h"
USING_NS_CC;

Block::Block(int type, int x, int y)
{
	this->blockInit(type, x, y);
}

void Block::blockInit(int type, int x, int y)//(x,y)为方块在数组中的位置(0,0)->(9,9）
{
	this->type = type;
	this->posX = x;
	this->posY = y;
	switch (type)
	{
	case(1) :
		block = Sprite::create("block1.png");
		break;
	case(2) :
		block = Sprite::create("block2.png");
		break;
	case(3) :
		block = Sprite::create("block3.png");
		break;
	case(4) :
		block = Sprite::create("block4.png");
		break;
	case(5) :
		block = Sprite::create("block5.png");
		break;
	case(7) :
		block = Sprite::create("box.png");
		break;
	case(6) :
		block = Sprite::create("stone.png");
		break;
	case(8) :
		block = Sprite::create("bomb.png");
		break;
	}
	//block->setPosition(370 + 60 * x, 670);
}

void Block::blockDelete()
{
	this->type = 0;
	this->block->setTexture("block0.png");
	this->block->setPosition(Vec2(30, 610));
}

void Block::moveTo(int x, int y)
{
	auto* move = MoveTo::create(0.1, Vec2(370 + 60 * x, 50 + 60 * y));
	this->block->runAction(move);
}