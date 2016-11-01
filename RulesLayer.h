#ifndef __RulesLayer_H__
#define __RulesLayer_H__

#include "cocos2d.h"
#include"BeginScene.h"

class RulesLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(RulesLayer);
	Layout*root;
	ImageView*image;
	Button*BackButton;
	
	void ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type);
};

#endif // __RulesLayer_SCENE_H__
