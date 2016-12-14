#ifndef __STATE_H__
#define __STATE_H__
#include "cocos2d.h"
USING_NS_CC;

class State {
public:
	virtual int* CreateMap()=0;
};

class StateLevel1 : public State {
public:
	int * CreateMap();
};

class StateLevel2 : public State {
public:
	int * CreateMap();
};

class StateLevel3 : public State {
public:
	int * CreateMap();
};

class StateLevel4 :public State {
public:
	int*CreateMap();
};
#endif