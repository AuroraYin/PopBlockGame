#ifndef __BLOCK_H__
#define __BLOCK_H__
#include "cocos2d.h"
USING_NS_CC;

class Block
{
public:
	int posX;
	int posY;
	int type;                                             //��ʾ���������
	Sprite* block;                                        //������ʾ����ľ������
	void blockDelete();                                   //ɾ������
	Block(int type, int x, int y);
	void blockInit(int type, int x, int y);               //��ʼ������
	void moveTo(int x, int y);                            //�����ƶ�
};
#endif