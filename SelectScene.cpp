#include "SelectScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SelectScene::create();

	scene->addChild(layer);

	return scene;
}

bool SelectScene::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("SelectionScene.csb");


	Layout*root2 = (Layout*)rootNode->getChildByName("root2");
	Button*Level_1 = (cocos2d::ui::Button*)Helper::seekWidgetByName(root2, "Button_3");
	Button*Level_2 = (cocos2d::ui::Button*)Helper::seekWidgetByName(root2, "Button_4");
	Button*Level_3 = (cocos2d::ui::Button*)Helper::seekWidgetByName(root2, "Button_5");
	Button*BackToBeginScene = (cocos2d::ui::Button*)Helper::seekWidgetByName(root2, "Button_6");

	Level_1->addTouchEventListener(CC_CALLBACK_2(SelectScene::ComeToLevel1, this));
	Level_2->addTouchEventListener(CC_CALLBACK_2(SelectScene::ComeToLevel2, this));
	Level_3->addTouchEventListener(CC_CALLBACK_2(SelectScene::ComeToLevel3, this));
	BackToBeginScene->addTouchEventListener(CC_CALLBACK_2(SelectScene::ComeBack, this));

	addChild(rootNode);

	return true;
}

void SelectScene::ComeToLevel1(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		iCurrent = 1;
		auto director = Director::getInstance();
		auto scene = GameScene_1::createScene();
		auto trasition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(trasition);
		break;
	}
}

void SelectScene::ComeToLevel2(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		iCurrent = 2;
		auto director = Director::getInstance();
		auto scene = GameScene_2::createScene();
		auto trasition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(trasition);
		break;
	}
}

void SelectScene::ComeToLevel3(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		iCurrent = 3;
		auto director = Director::getInstance();
		auto scene = GameScene_3::createScene();
		auto trasition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(trasition);
		break;
	}
}
void SelectScene::ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type)
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