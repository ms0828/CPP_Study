#pragma once

class Player
{
public:
	void KillMonster();

public:
	int _hp;
	int _attack;

	class Monster* _target;
};

