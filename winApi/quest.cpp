#include "stdafx.h"
#include "quest.h"

void quest::init(string name, int gold, int ex, string description, 
	string item, int monster, string questtype, string monstername, 
	string questStage)
{
	_name = name;
	_gold = gold;
	_exp = ex;	
	_description = description;
	_item = item;
	_monster = monster;
	_questtype = questtype;
	_monsterName = monstername;
	_questStage = questStage;
}