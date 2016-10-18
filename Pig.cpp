#include "Pig.h"

Pig::Pig(sf::Texture& pig, b2World& world_, float pig_dimbody_x, float pig_dimbody_y) : world(world_), Damagable(2000)
{
	dimbody_x = pig_dimbody_x;
	dimbody_y = pig_dimbody_y;

	sprite = sf::Sprite(pig, sf::IntRect(0, 0, frame_width, frame_height));
	sprite.setPosition(dimbody_x, dimbody_y);
	sprite.setOrigin(frame_width / 2, frame_height / 2);

	b2BodyDef* bodyDef = new b2BodyDef();
	bodyDef->type = b2_dynamicBody;
	bodyDef->position.Set(dimbody_x / common::met_to_pix, dimbody_y / common::met_to_pix);

	b2CircleShape* dynamicBox = new b2CircleShape();
	dynamicBox->m_radius = 22 / common::met_to_pix;
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = dynamicBox;
	fixtureDef->density = 0.01f;
	fixtureDef->friction = 1.0f;

	bodyDef->position.Set(sprite.getPosition().x / common::met_to_pix, sprite.getPosition().y / common::met_to_pix);
	body = world.CreateBody(bodyDef);
	body->CreateFixture(fixtureDef);
	body->SetUserData(this);
}

void Pig::update()
{
	if (body)
	{
		sprite.setPosition(body->GetPosition().x * common::met_to_pix, body->GetPosition().y * common::met_to_pix);
		sprite.setRotation(body->GetAngle() / b2_pi * 180);
		if (clock() - this->time >= 1000 / 0.5f)
		{
			sprite.setTextureRect(sf::IntRect(num_frame_x*frame_width, num_frame_y*frame_height, frame_width, frame_height));
			num_frame_x = rand() % 3;
			this->time = clock();
		}
	}
}

void Pig::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void Pig::damage(int hp)
{
	Damagable::damage(hp);
	std::cout<<this->hp<<std::endl;
	if (this->hp < hp2 && this->hp > hp1)
		num_frame_y=1;
	if (this->hp < hp1)
		num_frame_y = 2;
}
 
Pig::~Pig()
{
	world.DestroyBody(body);
}