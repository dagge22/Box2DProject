#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "World.h"
#include <iostream>

class Entity
{
public:
	Entity(const sf::Vector2f& position = sf::Vector2f(0,0), bool usePhysics = false);
	Entity(bool usePhysics);
	virtual ~Entity();
	virtual void Init() { };

	virtual void Update();
	virtual void Draw(sf::RenderWindow* window) { window->draw(*shape); };

	void SetWorld(World* world) { this->world = world; }

	sf::Vector2f GetPosition() const { return position; }
	void SetSize(const sf::Vector2f& size) { this->size = size; }
	void SetPosition(const sf::Vector2f& position);

	void SetShape(sf::Shape* newShape);
	void SetFillColor(const sf::Color& newColor);
	sf::Shape* GetShape() const { return shape; }

	void EnablePhysics(bool enable);
	bool GetPhysicsEnabled() const { return physicsEnabled; }

	void SetCircle(float radius);
	void SetRectangle();
	void SetConvex(const std::vector<sf::Vector2f>& points);
	void SetFixtureDef(const b2FixtureDef& def);

	void Rotate(float angle);

	b2Body* GetBody() { return body; };
	b2BodyDef GetBodyDef() { return bodyDef; }
	b2FixtureDef GetFixtureDef() { return fixtureDef; }

	virtual void StartCollision(Entity* otherEntity) { };
	virtual void EndCollision(Entity* otherEntity) { };

	void Delete();
	bool IsMarkedForDeletion() const { return markedForDelete; }

	//void SetEnable(bool enable);
	void DisablePhysics();

	bool ShouldDraw() const { return draw; }
	void SetShouldDraw(bool b) { draw = b; }

protected:
	sf::Vector2f position;
	sf::Vector2f size;
	World* world = nullptr;

	sf::Shape* shape = nullptr;

	b2BodyDef bodyDef;
	b2Body* body = nullptr;
	b2FixtureDef fixtureDef;
	b2Fixture* fixture = nullptr;

	bool physicsEnabled = true;

	sf::Color color = sf::Color::Red;

	bool markedForDelete = false;

	bool draw = true;
};