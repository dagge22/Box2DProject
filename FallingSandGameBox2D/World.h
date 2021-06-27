#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <box2d/box2d.h>
#include <iostream>

class Entity;
class PhysicsObject;

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};

class World
{
public:
	World(sf::RenderWindow* window = nullptr);
	~World();

	void Update();

	void CreateEntity(Entity* entity);
	void CreateRectangle(Entity* entity, const sf::Vector2f& position, const sf::Vector2f& size);
	void CreateCircle(Entity* entity, float radius);
	void CreateRectangle(Entity* entity, const sf::Vector2f& size);
	void CreateConvex(Entity* entity, const std::vector<sf::Vector2f>& points);

	static int SCALE;

	b2World* GetB2World() const { return b2world; }
	sf::RenderWindow* GetWindow() const { return window; }

	std::vector<class Entity*> disableList;
	void DeleteEntity(Entity* entity);

private:
	void CreateEntityInternal(Entity* entity);
	void DeleteEntity(Entity* entity, int index);
	sf::RenderWindow* window;

	std::vector<class Entity*> enteties;

	void DeleteEnteties();

	b2World* b2world;

	b2Vec2 gravity;

	const float fpsLimit = 60.f;
	float frameLimitTimer = 0.f;
	const float timeStep = 1.f / fpsLimit;

	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;

	sf::Clock clock;

protected:

	ContactListener listener;
};
