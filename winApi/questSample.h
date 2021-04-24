#pragma once
#include "quest.h"

class quest;

class questSample
{
private:
	queue <quest*>_quest;

public:
	void questSetup(quest* pQuest = NULL);
	queue<quest*>* getQuest() { return &this->_quest; };
	void init(void);

	questSample() {}
	~questSample() {}
};