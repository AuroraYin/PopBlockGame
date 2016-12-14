#include "State.h"

int * StateLevel1::CreateMap() {
	int* iMap = new int[100];
	for (int i = 0; i<100; i++) {
		iMap[i] = rand() % 5 + 1;     //产生0~99的随机数
		//log("%d", iMap[i]);
	}
	return iMap;
}

int * StateLevel3::CreateMap()
{
	int* iMap = new int[100];
	for (int i = 0; i<100; i++) {
		iMap[i] = rand() % 5 + 1;     //产生0~99的随机数
									  //log("%d", iMap[i]);
	}
	return iMap;
}

int * StateLevel2::CreateMap()
{
	int* iMap = new int[100];
	for (int i = 0; i<100; i++) {
		iMap[i] = rand() % 5 + 1;     //产生0~99的随机数
									  //log("%d", iMap[i]);
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
