#pragma once

class Damagable
{
protected :
	int hp;
public:
	Damagable(int hp);
	virtual void damage(int hp)
	{
		if(hp>150)
			this->hp -= hp;
	}
	bool is_alive();
};

