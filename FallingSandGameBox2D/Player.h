#pragma once
#include "Entity.h"
#include "Shape.h"
#include "PhysicsObject.h"

class Player : public Entity
{
public:
	Player(const sf::Vector2f& position, const sf::Vector2f& size);

	virtual void Update() override;
	virtual void Draw(sf::RenderWindow* window) override;

	void Init() override;

private:
	void Input();
	b2Vec2 direction;

	void StartCollision(Entity* otherEntity) override;
	void EndCollision(Entity* otherEntity) override;

	void Move();

	void RemoveRope();

	const float speed = 10.f;

	void Jump();

	void ShootLine();

	float timer = 0;
	const float cooldown = 0.2f;
	sf::Clock clock;

	b2MouseJointDef jointDef;
	b2MouseJoint* joint;

	class PlayerProjectile* projectile = nullptr;

	std::vector<sf::Vertex> rope;

	bool ropeOut = false;

	void UpdateRopePosition();

	float ropeReelSpeed = 10;

};