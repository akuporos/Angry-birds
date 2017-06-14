#include "Plank.h"

Plank::Plank(sf::Texture& plank1, int x, int y, int angle, b2World& world_) : world(world_), Damagable(900)
{

	sprite_plank.setTexture(plank1);
	sprite_plank.setOrigin(plank1.getSize().x / 2, plank1.getSize().y / 2);
	sprite_plank.setPosition(x, y);	//нижн€€
	sprite_plank.setRotation(angle);

	b2BodyDef* body_planks_def = new b2BodyDef();
	body_planks_def->type = b2_dynamicBody;
	b2PolygonShape* plank = new b2PolygonShape();
	plank->SetAsBox(plank1.getSize().x / 2 / common::met_to_pix, plank1.getSize().y / 2 / common::met_to_pix);
	b2FixtureDef* fixtureDef1 = new b2FixtureDef();
	fixtureDef1->shape = plank;
	fixtureDef1->density = 0.1f;
	fixtureDef1->friction = 1.0f;

	body_plank = world.CreateBody(body_planks_def);
	body_plank->CreateFixture(fixtureDef1);
	body_plank->SetTransform({ sprite_plank.getPosition().x / common::met_to_pix, sprite_plank.getPosition().y / common::met_to_pix }, sprite_plank.getRotation() * b2_pi / 180);
	body_plank->SetUserData(this);
}


void Plank::update()
{
	sprite_plank.setPosition(body_plank->GetPosition().x * common::met_to_pix, body_plank->GetPosition().y * common::met_to_pix);
	sprite_plank.setRotation(body_plank->GetAngle() / b2_pi * 180);
}

void Plank::draw(sf::RenderWindow& window)
{
	window.draw(sprite_plank);
}

void Plank::damage(int hp)
{
	Damagable::damage(hp);
}

Plank::~Plank()
{
	world.DestroyBody(body_plank);
}