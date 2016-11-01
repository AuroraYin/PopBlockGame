#include "RulesLayer.h"

bool RulesLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("ruleLayer.csb");

	root = (Layout*)rootNode->getChildByName("root");
	BackButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(root, "Button_1");

	BackButton->addTouchEventListener(CC_CALLBACK_2(RulesLayer::ComeBack, this));
	
	addChild(rootNode);

	return true;
}

void RulesLayer::ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		this->removeFromParentAndCleanup(true);
		break;
	}
}

