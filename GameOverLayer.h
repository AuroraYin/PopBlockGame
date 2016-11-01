#ifndef __GAMEOVERLAYER_H__
#define __GAMEOVERLAYER_H__

#include "cocos2d.h"
#include"BeginScene.h"

class GameOverLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
	Layout*root;
	ImageView*image;
	Button*BackButton;
	Button*RePlayButton;

	void ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void RePlay(cocos2d::Ref*pSender, Widget::TouchEventType type);
};

#endif // __GameOverLayer_SCENE_H__
