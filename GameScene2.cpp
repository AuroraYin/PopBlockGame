#include "GameScene2.h"

USING_NS_CC;

Scene* GameScene_2::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene_2::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene_2::init()
{
	if (!Layer::init())
	{
		return false;
	}
	iCurrent = 2;

	
	auto rootNode = CSLoader::createNode("GameScene2.csb");

	root = (Layout*)rootNode->getChildByName("root");
	MusicControl = (cocos2d::ui::ImageView*)Helper::seekWidgetByName(root, "Image_1");
	ComeBackToBeginScene = (cocos2d::ui::Button*)Helper::seekWidgetByName(root, "Button_1");

	MusicControl->loadTexture("res/menu_sound_on.png");
	MusicControl->setTouchEnabled(true);
	MusicControl->addTouchEventListener(CC_CALLBACK_2(GameScene_2::MusicControling, this));


	ComeBackToBeginScene->addTouchEventListener(CC_CALLBACK_2(GameScene_2::ComeBack, this));
	addChild(rootNode);

	scoreLabel0 = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 36);
	scoreLabel0->setColor(Color3B::BLACK);
	scoreLabel0->setPosition(Vec2(100, 450));
	addChild(scoreLabel0);

	scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 36);
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setPosition(Vec2(200, 450));
	addChild(scoreLabel);
	//////////////////////////////////////////////////////////////////

	state = new StateLevel2();
	gameSpace = new GameSpace(state);
	this->addBlock();

	auto listener = EventListenerTouchOneByOne::create();
	// 绑定监听事件
	listener->onTouchBegan = CC_CALLBACK_2(GameScene_2::onTouchBegan, this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}

void GameScene_2::ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type)
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


void GameScene_2::addBlock()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			gameSpace->blocks[x][y] = new Block(gameSpace->map[x][y]->iType, x, y);
			this->addChild(gameSpace->blocks[x][y]->block);
			gameSpace->blocks[x][y]->block->setPosition(370 + 60 * x, 670);
			auto move = MoveTo::create((640 - gameSpace->blocks[x][y]->posY * 60) / 200.0,
				Vec2(370 + 60 * gameSpace->blocks[x][y]->posX, 50 + 60 * gameSpace->blocks[x][y]->posY));
			gameSpace->blocks[x][y]->block->runAction(move);
		}
	}
}

bool GameScene_2::onTouchBegan(Touch* touch, Event* event)
{
	auto position = touch->getLocation();   //获取用户点击坐标
	//判断用户点击的坐标位置是否在“星星”的范围内
	if (position.x<940 && position.x>340 && position.y > 20 && position.y < 620)
	{
		//将坐标转换为对应在blocks数组的索引
		int x = (int)(position.x - 340) / 60;
		int y = (int)(position.y - 20) / 60;
		
		int posx = gameSpace->map[x][y]->iIndexNum % 10;
		int posy = gameSpace->map[x][y]->iIndexNum / 10;

		if (gameSpace->map[x][y]->iIndexNum>=0&&gameSpace->map[posx][posy]->iType == 7)
		{
			gameSpace->iScore += 200;
			gameSpace->map[x][y]->iType = 0;
			gameSpace->map[x][y]->iIndexNum = -1;
			sprintf(score_str, "%d", gameSpace->iScore);
			gameSpace->blocks[posx][posy]->blockDelete();
			scoreLabel->setString(score_str);
			gameSpace->blockDrop();
			gameSpace->moveLeft();
		}
		if (gameSpace->canDelete(x, y) == true)
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/pop.mp3");
			gameSpace->UDLRDelete(x, y);
			//后续操作：
			gameSpace->iScore += gameSpace->iNumOfBlocks*gameSpace->iNumOfBlocks * 10;
			//CCLOG("%d", iScore);
			gameSpace->blockDrop();
			gameSpace->moveLeft();
			gameSpace->cleanRecord();
			gameSpace->iNumOfBlocks = 0;

			auto userdefault = UserDefault::getInstance();

			sprintf(score_str, "%d", gameSpace->iScore);

			scoreLabel->setString(score_str);


			if (gameSpace->isOver() == true)
			{
				if (gameSpace->iScore >= 3000)
				{
					gameSpace->Clear();
					auto layer = YouwinLayer::create();
					this->addChild(layer);
				}
				else
				{
					gameSpace->Clear();
					auto layer = GameOverLayer::create();
					this->addChild(layer);
				}
			}
			return true;
		}
	}
	return false;
}


void GameScene_2::MusicControling(cocos2d::Ref*pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:

		if (iMusic == 1)
		{
			iMusic = 0;
			MusicControl->loadTexture("menu_sound_off.png");
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		else
		{
			iMusic = 1;
			MusicControl->loadTexture("menu_sound_on.png");
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		break;
	}
}

