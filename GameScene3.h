#ifndef __GameScene_3_SCENE_H__
#define __GameScene_3_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"BeginScene.h"
#include"Block.h"

using namespace cocos2d::ui;
using namespace cocostudio::timeline;

class GameScene_3 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene_3);
	//界面按钮控制
	void ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void MusicControling(cocos2d::Ref*pSender, Widget::TouchEventType type);

	Layout*root;
	ImageView*MusicControl;
	Button*ComeBackToBeginScene;

	//游戏操作

	bool canDelete(int x, int y);
	Block* blocks[10][10];
	int map1[10][10];
	int map2[10][10];
	void addMap();
	int record[10][10];
	int NumOfBlocks;
	int CurrentType;
	void addBlock();
	void UDLRDelete(int x, int y);
	int iScore;
	char score_str[10];
	Label* scoreLabel;
	Label* scoreLabel0;

	void releaseMemory();//游戏结束，释放内存
	void blockDrop();
	void moveLeft();
	void cleanRecord();
	bool isOver();//游戏是否结束的判定
	//EventListenerTouchOneByOne* listener;
	//
	void Clear();
	bool onTouchBegan(Touch* touch, Event* event);//玩家点击事件的获取

};

#endif // __GameScene_3_SCENE_H__
