#ifndef __GameScene_2_SCENE_H__
#define __GameScene_2_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"BeginScene.h"
#include"Block.h"
#include "State.h"
#include "GameSpace.h"

using namespace cocos2d::ui;
using namespace cocostudio::timeline;

class GameScene_2 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene_2);
	//界面按钮控制
	void ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void MusicControling(cocos2d::Ref*pSender, Widget::TouchEventType type);

private:
	Layout*root;
	ImageView*MusicControl;
	Button*ComeBackToBeginScene;
	State* state;
	GameSpace* gameSpace;
	char score_str[10];
	Label* scoreLabel;
	Label* scoreLabel0;
	void addBlock();
	bool onTouchBegan(Touch* touch, Event* event);//玩家点击事件的获取

};

#endif // __GameScene_2_SCENE_H__
