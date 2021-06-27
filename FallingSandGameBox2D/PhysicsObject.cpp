#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(const sf::Vector2f& position, const sf::Vector2f& size)
{
	this->position = position;
	this->size = size;
}

void PhysicsObject::Init()
{
	//shape.setSize(size);
	//shape.setOrigin(size.x * 0.5f, size.y * 0.5f);
	//shape.setPosition(position);

	//bodyDef.type = b2BodyType::b2_dynamicBody;

	//bodyDef.position.Set(position.x / World::SCALE, position.y / World::SCALE);
	//body = world->GetB2World()->CreateBody(&bodyDef);

	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox((size.x * 0.5) / World::SCALE, (size.y * 0.5) / World::SCALE);

	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.7f;
	//fixtureDef.friction = 0.3f;

	//body->CreateFixture(&fixtureDef);
	//shape.setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	//shape.setRotation(body->GetAngle() * 180 / b2_pi);
	//position = shape.getPosition();
}

void PhysicsObject::Draw(sf::RenderWindow* window)
{
	window->draw(*shape);
}

void PhysicsObject::Update()
{
	if (bodyDef.type == b2BodyType::b2_staticBody)
		return;

	//shape.setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	//shape.setRotation(body->GetAngle() * 180 / b2_pi);
	//position = shape.getPosition();
}

void PhysicsObject::AddFixtureDef(b2FixtureDef* def)
{
	body->CreateFixture(def);
}

void PhysicsObject::Rotate(float radians)
{
	body->SetTransform(body->GetPosition(), radians);
}
