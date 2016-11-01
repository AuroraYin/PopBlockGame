#include "BeginScene.h"

USING_NS_CC;

Scene* BeginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = BeginScene::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool BeginScene::init()
{
	
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");

	Layout*root1 = (Layout*)rootNode->getChildByName("root1");
	Button*RulesButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(root1, "Button_1");
	Button*SelectionButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(root1, "Button_2");

	RulesButton->addTouchEventListener(CC_CALLBACK_2(BeginScene::SeeRules,this));
	SelectionButton->addTouchEventListener(CC_CALLBACK_2(BeginScene::selectionTouch,this));


	addChild(rootNode);

	return true;
}

void BeginScene::selectionTouch(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		auto scene = SelectScene::createScene();
		auto trasition = TransitionCrossFade::create(1.0f, scene);
		director->replaceScene(trasition);
		break;
	}
}


void BeginScene::SeeRules(cocos2d::Ref*pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		auto layer = RulesLayer::create();
		this->addChild(layer);
		
		break;
	}
}
