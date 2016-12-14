#ifndef __GAMESCENE_1_SCENE_H__
#define __GAMESCENE_1_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "BeginScene.h"
#include "Block.h"
#include "GameSpace.h"
#include "State.h"

using namespace cocos2d::ui;
using namespace cocostudio::timeline;

class GameScene_1 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene_1);
	//���水ť����
	void ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void MusicControl(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void addBlock();
	//EventListenerTouchOneByOne* listener;
	bool onTouchBegan(Touch* touch, Event* event);//��ҵ���¼��Ļ�ȡ
	
	Layout*root3;
	ImageView*MusicControl1;
	Button*ComeBackToBeginScene;
	State* state;
	GameSpace* gameSpace;
	char score_str[10] ;
	Label* scoreLabel;
	Label* scoreLabel0;	

};

#endif // __GameScene_1_SCENE_H__
