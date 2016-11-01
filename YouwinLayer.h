#ifndef __YOUWINLAYER_H__
#define __YOUWINLAYER_H__

#include "cocos2d.h"
#include"BeginScene.h"

class YouwinLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(YouwinLayer);
	Layout*root;
	ImageView*image;
	Button*BackButton;
	Button*RePlayButton;

	void ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type);
	void NextTouch(cocos2d::Ref*pSender, Widget::TouchEventType type);
};

#endif // __YouwinLayer_SCENE_H__
