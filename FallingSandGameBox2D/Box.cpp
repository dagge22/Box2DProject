#include "Box.h"

static constexpr int scale = 30;

Box::Box(b2World& world, const sf::Vector2f& pos, const sf::Vector2f& size, const b2BodyType& type)
{
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setOrigin(size.x * 0.5f, size.y * 0.5f);
	rectangle.setPosition(pos);
	rectangle.setSize(size);

	this->type = type;

	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(pos.x / scale, pos.y / scale);
	body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((size.x * 0.5) / scale, (size.y * 0.5) / scale);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	//body->ApplyForceToCenter(b2Vec2(20, 10), true);
	//body->ApplyAngularImpulse(100, true);
	rectangle.setPosition(body->GetPosition().x * scale, body->GetPosition().y * scale);
}

void Box::Update()
{
	if (type != b2BodyType::b2_staticBody)
	{
		rectangle.setPosition(body->GetPosition().x * scale, body->GetPosition().y * scale);
		rectangle.setRotation(body->GetAngle() * 180 / 3.1415f);
	}
}
