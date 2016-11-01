#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__

#include "BeginScene.h"

using namespace cocos2d::ui;
using namespace cocostudio::timeline;


class SelectScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(SelectScene);

	void ComeToLevel1(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void ComeToLevel2(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void ComeToLevel3(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type);

};

#endif // __SelectScene_SCENE_H__
