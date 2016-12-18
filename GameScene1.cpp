#include "GameScene1.h"

USING_NS_CC;

Scene* GameScene_1::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene_1::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene_1::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//界面显示，控件定义
	auto rootNode = CSLoader::createNode("GameScene1.csb");
	root3 = (Layout*)rootNode->getChildByName("root3");
	MusicControl1 = (cocos2d::ui::ImageView*)Helper::seekWidgetByName(root3, "Image_2");
	ComeBackToBeginScene = (cocos2d::ui::Button*)Helper::seekWidgetByName(root3, "Button_8");
	UndoButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(root3, "UndoButton");
	RedoButton = (cocos2d::ui::Button*)Helper::seekWidgetByName(root3, "RedoButton");

	MusicControl1->loadTexture("res/menu_sound_on.png");
	MusicControl1->setTouchEnabled(true);
	MusicControl1->addTouchEventListener(CC_CALLBACK_2(GameScene_1::MusicControl, this));

	ComeBackToBeginScene->addTouchEventListener(CC_CALLBACK_2(GameScene_1::ComeBack, this));
	UndoButton->addTouchEventListener(CC_CALLBACK_2(GameScene_1::Undo, this));
	RedoButton->addTouchEventListener(CC_CALLBACK_2(GameScene_1::Redo, this));
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
	
	commandManagerForGame = new CommandManager();
	commandManagerForScore = new CommandManager();
	state = new StateLevel1();
	gameSpace = new GameSpace(state);
	this->addBlock();
	
	auto listener = EventListenerTouchOneByOne::create();
	// 绑定监听事件
	listener->onTouchBegan = CC_CALLBACK_2(GameScene_1::onTouchBegan, this);
	listener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	/////////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}

void GameScene_1::ComeBack(cocos2d::Ref*pSender, Widget::TouchEventType type)
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

void GameScene_1::addBlock()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			gameSpace->blocks[x][y] = new Block(gameSpace->map[x][y]->iType, x, y);
			this->addChild(gameSpace->blocks[x][y]->block);
			gameSpace->blocks[x][y]->block->setPosition(370 + 60 * x, 670);
			auto move = MoveTo::create((640-gameSpace->blocks[x][y]->posY*60)/200.0, 
				Vec2(370 + 60 * gameSpace->blocks[x][y]->posX, 50 + 60 * gameSpace->blocks[x][y]->posY));
			gameSpace->blocks[x][y]->block->runAction(move);
		}
	}
	
}

bool GameScene_1::onTouchBegan(Touch* touch, Event* event)
{
	auto position = touch->getLocation();   //获取用户点击坐标
	//判断用户点击的坐标位置是否在“星星”的范围内
	if (position.x<940 && position.x>340 && position.y > 20 && position.y < 620)
	{
		//将坐标转换为对应在blocks数组的索引
		int x = (int)(position.x - 340) / 60;
		int y = (int)(position.y - 20) / 60;
		GameCommand*commandCurrent = new GameCommand(gameSpace);
		ScoreCommand*scoreCurrent = new ScoreCommand(gameSpace->iScore);
		commandManagerForGame->CallCommand(commandCurrent);
		commandManagerForScore->CallCommand(scoreCurrent);
		commandManagerForGame->ClearAllCommands();
		commandManagerForScore->ClearAllCommands();


		if (gameSpace->canDelete(x, y) == true)
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/pop.mp3");
			gameSpace->UDLRDelete(x, y);
			//后续操作：
			gameSpace->iScore += gameSpace->iNumOfBlocks*gameSpace->iNumOfBlocks * 10;
			//CCLOG("%d", iScore);
			this->gameSpace->blockDrop();
			this->gameSpace->moveLeft();
			this->gameSpace->cleanRecord();
			gameSpace->iNumOfBlocks = 0;
			
			auto userdefault = UserDefault::getInstance();

			sprintf(score_str , "%d", gameSpace->iScore);
			
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


void GameScene_1::MusicControl(cocos2d::Ref*pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::ENDED:

		if (iMusic == 1)
		{
			iMusic = 0;
			MusicControl1->loadTexture("menu_sound_off.png");
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		else
		{
			iMusic = 1;
			MusicControl1->loadTexture("menu_sound_on.png");
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		break;
	}
}

void GameScene_1::Undo(cocos2d::Ref * pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:

		GameCommand*commandCurrent = new GameCommand(gameSpace);
		ScoreCommand*scoreCurrent = new ScoreCommand(gameSpace->iScore);
		
		int*commandOfGame = nullptr;
		int*commandOfScore = nullptr;
		bool bRes1 = commandManagerForGame->Undo(commandOfGame,commandCurrent);
		bool bRes2 = commandManagerForScore->Undo(commandOfScore,scoreCurrent);
		if (bRes1&&bRes2)
		{
			gameSpace->Clear();
			gameSpace->cleanRecord();
			sprintf(score_str, "%d", *commandOfScore);
			scoreLabel->setString(score_str);

			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					gameSpace->iScore = *commandOfScore;
					int index = x + 10 * y;
					gameSpace->map[x][y]->iType = commandOfGame[index];
					gameSpace->blocks[x][y] = new Block(commandOfGame[index], x, y);
					if (commandOfGame[index] > 0) {
						gameSpace->blocks[x][y]->block->setPosition(370 + 60 * gameSpace->blocks[x][y]->posX,
							50 + 60 * gameSpace->blocks[x][y]->posY);
						gameSpace->map[x][y]->iIndexNum = index;
						this->addChild(gameSpace->blocks[x][y]->block);
						auto move = MoveTo::create(0.01, gameSpace->blocks[x][y]->block->getPosition());
						gameSpace->blocks[x][y]->block->runAction(move);
					}
					else
					{
						//gameSpace->blocks[x][y]->block->setPosition(1000, 700);
						//this->addChild(gameSpace->blocks[x][y]->block);
						gameSpace->map[x][y]->iIndexNum = -1;
					}
				}
			}
		}
		else {
			//无法Undo
		}
		break;
	}
}

void GameScene_1::Redo(cocos2d::Ref * pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
		GameCommand*commandCurrent = new GameCommand(gameSpace);
		ScoreCommand*scoreCurrent = new ScoreCommand(gameSpace->iScore);

		int*commandOfGame = nullptr;
		int*commandOfScore = nullptr;
		bool bRes1 = commandManagerForGame->Redo(commandOfGame,commandCurrent);
		bool bRes2 = commandManagerForScore->Redo(commandOfScore,scoreCurrent);
		if (bRes1&&bRes2)
		{
			gameSpace->Clear();
			gameSpace->cleanRecord();
			sprintf(score_str, "%d", *commandOfScore);
			scoreLabel->setString(score_str);

			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					gameSpace->iScore = *commandOfScore;
					int index = x + 10 * y;
					gameSpace->map[x][y]->iType = commandOfGame[index];
					gameSpace->blocks[x][y] = new Block(commandOfGame[index], x, y);
					if (commandOfGame[index] > 0) {
						gameSpace->blocks[x][y]->block->setPosition(370 + 60 * gameSpace->blocks[x][y]->posX,
							50 + 60 * gameSpace->blocks[x][y]->posY);
						gameSpace->map[x][y]->iIndexNum = index;
						this->addChild(gameSpace->blocks[x][y]->block);
						auto move = MoveTo::create(0.01, gameSpace->blocks[x][y]->block->getPosition());
						gameSpace->blocks[x][y]->block->runAction(move);
					}
					else
					{
						//gameSpace->blocks[x][y]->block->setPosition(1000, 700);
						//this->addChild(gameSpace->blocks[x][y]->block);
						gameSpace->map[x][y]->iIndexNum = -1;
					}
				}
			}
		}
		else {
			//无法Redo
		}
		break;
	}
}

