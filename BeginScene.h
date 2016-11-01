#ifndef __BEGIN_SCENE_H__
#define __BEGIN_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"SelectScene.h"
#include"GameScene1.h"
#include"GameScene2.h"
#include"GameScene3.h"
#include"YouwinLayer.h"
#include"GameOverLayer.h"
#include"GlobalVariables.h"
#include"SimpleAudioEngine.h"
#include"RulesLayer.h"

using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

class BeginScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(BeginScene);

	void selectionTouch(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void SeeRules(cocos2d::Ref*pSender, Widget::TouchEventType type);
};

#endif // __BEGIN_SCENE_H__
