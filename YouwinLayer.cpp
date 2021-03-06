#include "YouwinLayer.h"

bool YouwinLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("winLayer.csb");

	root = (Layout*)rootNode->getChildByName("root");
	BackButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(root, "Button_1");
	RePlayButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(root, "Button_2");

	BackButton->addTouchEventListener(CC_CALLBACK_2(YouwinLayer::ComeBack, this));
	RePlayButton->addTouchEventListener(CC_CALLBACK_2(YouwinLayer::NextTouch, this));

	SimpleAudioEngine::getInstance()->playEffect("res/music/win.mp3");

	addChild(rootNode);

	return true;
}

void YouwinLayer::ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = BeginScene::createScene();
		auto trasition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(trasition);
		break;
	}
}

void YouwinLayer::NextTouch(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		Scene*scene;
		switch (iCurrent)
		{
		case(1) :
			scene = GameScene_2::createScene();
			director->replaceScene(scene);
			break;
		case(2) :
			scene = GameScene_3::createScene();
			director->replaceScene(scene);
			break;
		case(3) :
			scene = SelectScene::createScene();
			director->replaceScene(scene);
			break;
		default:
			break;
		}

		this->removeFromParentAndCleanup(true);

		break;
	}
}
