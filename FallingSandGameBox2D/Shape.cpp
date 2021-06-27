#include "Shape.h"
#include <iostream>
#include <time.h>

Shape::Shape(const sf::Vector2f& position)
{
	this->position = position;
	
}

void Shape::Update()
{
	if (bodyDef.type == b2BodyType::b2_staticBody)
		return;

	shape->setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	shape->setRotation(body->GetAngle() * 180 / b2_pi);
	//std::cout << shape->getPosition().x << " " << shape->getPosition().y << "\n";
	//std::cout << "Body: " << body->GetPosition().x << " " << body->GetPosition().y << "\n";
	position = shape->getPosition();
}

void Shape::Draw(sf::RenderWindow* window)
{
	window->draw(*shape);
}

void Shape::SetRectangle(const sf::Vector2f& size, bool dynamic /*= true */)
{
	srand(time(NULL));
	shape = new sf::RectangleShape(size);
	shape->setOrigin(size.x * 0.5f, size.y * 0.5f);
	shape->setPosition(position);
	sf::Color color;
	color.r = rand() % 256;
	color.g = rand() % 256;
	color.b = rand() % 256;
	shape->setFillColor(color);

	bodyDef.type = b2BodyType::b2_dynamicBody;

	if (!dynamic) bodyDef.type = b2BodyType::b2_staticBody;

	bodyDef.position.Set(position.x / World::SCALE, position.y / World::SCALE);
	body = world->GetB2World()->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((size.x * 0.5) / World::SCALE, (size.y * 0.5) / World::SCALE);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
	shape->setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	shape->setRotation(body->GetAngle() * 180 / b2_pi);
	position = shape->getPosition();
}

void Shape::SetCircle(const sf::Vector2f& size, bool dynamic)
{

}
