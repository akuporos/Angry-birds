#pragma once

#include <Box2D\Box2D.h>
#include "Pig.h"
#include <iostream>
#include "Plank.h"

class ContactListener : public b2ContactListener

{
public:
	ContactListener();
	void PostSolve(b2Contact* contact, const b2ContactImpulse* Impulse);
};

