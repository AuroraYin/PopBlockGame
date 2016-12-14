#include "GameSpace.h"

USING_NS_CC;

GameSpace::GameSpace(State * sta)
{
	int* rawMap = sta->CreateMap();
	int ix, iy;
	for (int iCurrent = 0; iCurrent < 100; iCurrent++) {
		ix = iCurrent % 10;
		iy = iCurrent / 10;
		map[ix][iy] = new MapNode();
		map[ix][iy]->iIndexNum = iCurrent;
		map[ix][iy]->iType = rawMap[iCurrent];
		map[ix][iy]->iRecord = -1;
		//blocks[ix][iy] = new Block(rawMap[iCurrent], ix, iy);
	}
	iNumOfBlocks = 0;
	iScore = 0;
}

bool GameSpace::canDelete(int x, int y)
{
	int type = map[x][y]->iType;
	bool isadd = false;
	if (map[x][y]->iType != 0)
	{
		if (y + 1 < 10 && map[x][y + 1]->iType == type&&map[x][y + 1]->iRecord == -1)//上方存在未检测过的同色方块
		{
			//Up
			isadd = true;
		}
		if (y > 0 && map[x][y - 1]->iType == type&&map[x][y - 1]->iType == -1)
		{
			//Down
			isadd = true;
		}
		if (x > 0 && map[x - 1][y]->iType == type&&map[x - 1][y]->iRecord == -1)
		{
			//Left
			isadd = true;
		}
		if (x + 1 < 10 && map[x + 1][y]->iType == type&&map[x + 1][y]->iRecord == -1)
		{
			//Right
			isadd = true;
		}
		if (isadd == true)
		{
			map[x][y]->changeRecord();
			iNumOfBlocks++;;
			map[x][y]->iType = 0;
			iCurrentType = type;
			return true;
		}
		else return false;
	}
	else return false;
}

void GameSpace::UDLRDelete(int x, int y)
{
	int posx = map[x][y]->iIndexNum % 10;
	int posy = map[x][y]->iIndexNum / 10;
	blocks[posx][posy]->blockDelete();//直接消除对应的方块
	map[x][y]->iIndexNum = -1;
	//依次计算对应点的上下左右相邻的星星
	if (y + 1 < 10 && map[x][y + 1]->iType == iCurrentType&&map[x][y + 1]->iRecord == -1)//上方存在未检测过的同色方块
	{
		//Up
		map[x][y + 1]->changeRecord();
		map[x][y + 1]->iType = 0;
		iNumOfBlocks++;
		UDLRDelete(x, y + 1);
	}
	if (y > 0 && map[x][y - 1]->iType == iCurrentType&&map[x][y - 1]->iRecord == -1)
	{
		//Down
		map[x][y - 1]->changeRecord();
		map[x][y - 1]->iType = 0;
		iNumOfBlocks++;
		UDLRDelete(x, y - 1);
	}
	if (x > 0 && map[x - 1][y]->iType == iCurrentType&&map[x - 1][y]->iRecord == -1)
	{
		//Left
		map[x - 1][y]->changeRecord();
		map[x - 1][y]->iType = 0;
		iNumOfBlocks++;
		UDLRDelete(x - 1, y);
	}
	if (x + 1 < 10 && map[x + 1][y]->iType == iCurrentType&&map[x + 1][y]->iRecord == -1)
	{
		//Right
		map[x + 1][y]->changeRecord();
		map[x + 1][y]->iType = 0;
		iNumOfBlocks++;
		UDLRDelete(x + 1, y);
	}
}

void GameSpace::blockDrop()
{
	for (int y = 1; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			// 遍历每一个非最底层的星星，看其下方是否存在空白

			if (map[x][y]->iType>0)//有方块，需要检测其是否能够向下移动
			{
				for (int i = 0; i < y; i++)
				{
					if (map[x][i]->iType == 0)//有空位
					{
						int posx = map[x][y]->iIndexNum % 10;
						int posy = map[x][y]->iIndexNum / 10;
						map[x][i]->iType = map[x][y]->iType;
						map[x][y]->iType = 0;
						map[x][i]->iIndexNum = map[x][y]->iIndexNum;
						map[x][y]->iIndexNum = -1;
						blocks[posx][posy]->moveTo(x, i);
						break;
					}
				}
			}
		}
	}
}

void GameSpace::moveLeft()
{
	for (int x = 1; x < 10; x++)
	{
		if (map[x][0]->iType >0)
		{
			for (int i = 0; i < x; i++)
			{
				if (map[i][0]->iType == 0)
				{
					for (int y = 0; y < 10; y++)
					{
						if (map[x][y]->iType>0)
						{
							int posx = map[x][y]->iIndexNum % 10;
							int posy = map[x][y]->iIndexNum / 10;
							map[i][y]->iType = map[x][y]->iType;
							map[x][y]->iType = 0;
							map[i][y]->iIndexNum = map[x][y]->iIndexNum;
							map[x][y]->iIndexNum = -1;
							blocks[posx][posy]->moveTo(i, y);
						}
					}
					break;
				}
			}

		}
	}
}

void GameSpace::cleanRecord()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
			map[x][y]->iRecord = -1;
	}
}


bool GameSpace::isOver()
{
	bool result = true;
	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			if ((map[x][y]->iType != 0) && map[x + 1][y]->iType == map[x][y]->iType)
				result = false;
			if (map[x][y]->iType != 0 && map[x][y]->iType == map[x][y + 1]->iType)
				result = false;
		}
	}
	return result;
}

void GameSpace::Clear()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			blocks[i][j]->block->removeFromParent();
		}
	}
}

void MapNode::setNode(int itype, int index)
{
	iType = itype; iIndexNum = index;
}

void MapNode::changeRecord()
{
	iRecord = 0;
}
