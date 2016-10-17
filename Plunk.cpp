#include "Plunk.h"



Plunk::Plunk(std::string str, b2World& world_) : world(world_)
{
	plank1.loadFromFile(str);

	for (int i = 0; i < 4; i++)
	{
		sprite_planks[i].setTexture(plank1);
		sprite_planks[i].setOrigin(plank1.getSize().x / 2, plank1.getSize().y / 2);
	}

	sprite_planks[0].setPosition(750, 330); //лева€
	sprite_planks[1].setPosition(800, 265);	//верхн€€
	sprite_planks[1].setRotation(90);
	sprite_planks[2].setPosition(850, 330);	//права€
	sprite_planks[3].setPosition(800, 395);	//нижн€€
	sprite_planks[3].setRotation(90);

	b2BodyDef body_planks_def;
	body_planks_def.type = b2_dynamicBody;
	b2PolygonShape plank;
	plank.SetAsBox(5.0f / common::met_to_pix, 50.0f / common::met_to_pix);
	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &plank;
	fixtureDef1.density = 0.1f;
	fixtureDef1.friction = 1.0f;

	for (int i = 0; i < 4; i++)
	{
		body_plank[i] = world.CreateBody(&body_planks_def);
		body_plank[i]->CreateFixture(&fixtureDef1);
		body_plank[i]->SetTransform({ sprite_planks[i].getPosition().x / common::met_to_pix, sprite_planks[i].getPosition().y / common::met_to_pix }, sprite_planks[i].getRotation() * b2_pi / 180);
	}
}

void Plunk::update()
{
	for (int i = 0; i < 4; i++)
	{
		sprite_planks[i].setPosition(body_plank[i]->GetPosition().x * common::met_to_pix, body_plank[i]->GetPosition().y * common::met_to_pix);
		sprite_planks[i].setRotation(body_plank[i]->GetAngle() / b2_pi * 180);
	}
}

void Plunk::draw(sf::RenderWindow& window)
{
	for (int i = 0; i<4; i++)
		window.draw(sprite_planks[i]);
}