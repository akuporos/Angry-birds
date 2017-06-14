#include "Damagable.h"

Damagable::Damagable(int hp)
{
	this->hp = hp;
}

bool Damagable::is_alive()
{
	return this->hp > 0;
}


