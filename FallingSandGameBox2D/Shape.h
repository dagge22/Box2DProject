#pragma once
#include "Entity.h"


class Shape : public Entity
{
public:
	Shape(const sf::Vector2f& position = sf::Vector2f(0,0));

	void Update() override;
	void Draw(sf::RenderWindow* window) override;

	void SetRectangle(const sf::Vector2f& size, bool dynamic = true);
	void SetCircle(const sf::Vector2f& size, bool dynamic = true);

	b2Body* GetBody() const { return body; }
	sf::Vector2f GetSize() const { return size; }

protected:
	sf::Shape* shape = nullptr;
	b2Body* body = nullptr;

	b2BodyDef bodyDef;
};