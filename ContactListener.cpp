#include "ContactListener.h"

ContactListener::ContactListener()
{
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* Impulse)
{
	if (Impulse->normalImpulses[0] < 0.0016) return;
	Damagable *b1 = (Damagable *)contact->GetFixtureA()->GetBody()->GetUserData();
	Damagable *b2 = (Damagable *)contact->GetFixtureB()->GetBody()->GetUserData();
	if (b1 != 0)
	{
		//std::cout << Impulse->normalImpulses[0] << std::endl;
		b1->damage(Impulse->normalImpulses[0]);
	}
	if (b2 != 0)
	{
		//if(Impulse->normalImpulses[0]>0.0015)
		//std::cout << Impulse->normalImpulses[0] << std::endl;
		b2->damage(Impulse->normalImpulses[0]*1106);
	}
}
