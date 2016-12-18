#include "State.h"

int * StateLevel1::CreateMap() {
	int* iMap = new int[100];
	for (int i = 0; i<100; i++) {
		iMap[i] = rand() % 5 + 1;   
		//log("%d", iMap[i]);
	}
	return iMap;
}

int * StateLevel3::CreateMap()
{
	int* iMap = new int[100];
	for (int i = 0; i<100; i++) {
		iMap[i] = rand() % 6 + 1;     //产生0~99的随机数
									  //log("%d", iMap[i]);
	}
	for (int i = 0; i < 5; i++) {
		int iBombx = rand() % 10;
		int iBomby = rand() % 10;
		iMap[iBombx + iBomby * 10] = 8;
	}
	return iMap;
}

int * StateLevel2::CreateMap()
{
	int* iMap = new int[100];
	for (int i = 0; i<100; i++) {
		iMap[i] = rand() % 6 + 1;     //产生0~99的随机数
									  //log("%d", iMap[i]);
	}
	for (int i = 0; i < 3; i++) {
		int iGiftx = rand() % 10;
		int iGifty = rand() % 10;
		iMap[iGiftx + iGifty * 10] = 7;
	}
	return iMap;
}

int * StateLevel4::CreateMap()
{
	int* iMap = new int[100];
	for (int i = 0; i<100; i++) {
		iMap[i] = 1;
	}
	return iMap;
}
