#pragma once
#include "Entity.h"

class PhysicsObject : public Entity
{
public:
	PhysicsObject() { }
	PhysicsObject(const sf::Vector2f& position, const sf::Vector2f& size);
	//virtual ~PhysicsObject() { std::cout << "Destroyed physics object!!\n"; };

	virtual void Init();

	void Draw(sf::RenderWindow* window) override;
	void Update() override;

	b2Body* GetBody() const { return body; }

	void AddFixtureDef(b2FixtureDef* def);

	void Rotate(float radians);

	b2Body* GetBody() { return body; }
	b2BodyDef* GetBodyDef() { return &bodyDef; }

protected:
	b2BodyDef bodyDef;
	b2Body* body = nullptr;
	b2FixtureDef fixtureDef;

	//sf::RectangleShape shape;
	//sf::Shape* shape = nullptr;
};