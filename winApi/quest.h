#pragma once

enum QUEST_TYPE
{
	QUEST_STAGE1,
};

class quest
{
protected:
	int _exp;	
	int _monster;
	int _gold;
	
	string _name;
	string _description;
	string _item;
	string _questtype;
	string _monsterName;
	string _questStage;
	
	QUEST_TYPE _questType;

public:
	void init(string name, int gold, int ex, string description, 
		string item, int _monster, string _questtype, string _monstername, 
		string questStage);

	string getName() { return this->_name; }
	int getGold() { return this->_gold; }
	int getExp() { return this->_exp; }	
	int getMonster() { return this->_monster; }
	string getItem() { return this->_item; }
	string getQuesttype() { return this->_questtype; }
	string getDescription() { return this->_description; }
	string getMonsterName() { return this->_monsterName; }
	string getQuestStage() { return this->_questStage; }
	QUEST_TYPE getType() { return this->_questType; }

	quest() {}
	~quest() {}
};