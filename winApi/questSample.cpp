#include "stdafx.h"
#include "questSample.h"

void questSample::init(void)
{
	questSetup();
}

void questSample::questSetup(quest * pQuest)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Äù½ºÆ®.json");
	for (auto it = root["quest"].begin(); it != root["quest"].end(); it++)
	{
		if ((*it).isObject())
		{
			quest* qQuest = new quest;
			qQuest->init
			(
				(*it)["_name"].asString(),
				(*it)["_gold"].asInt(),
				(*it)["_exp"].asInt(),
				(*it)["_description"].asString(),
				(*it)["_item"].asString(),
				(*it)["_monster"].asInt(),
				(*it)["_questType"].asString(),
				(*it)["_monsterName"].asString(),
				(*it)["_questStage"].asString()
			);
			_quest.push(qQuest);			
		}
	}
}