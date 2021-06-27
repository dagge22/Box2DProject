#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "Shape.h"

class Box : public Shape
{
public:
	Box(b2World& world, const sf::Vector2f& pos, const sf::Vector2f& size, const b2BodyType& type);

	void Update() override;
	sf::RectangleShape GetRectangle() const { return rectangle; }

private:
	sf::RectangleShape rectangle;

	sf::Vector2f position;
	sf::Vector2f size;
	b2Body* body = nullptr;

	b2BodyType type;
};