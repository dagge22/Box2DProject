#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(const sf::Vector2f& position);

	void Init() override;

	virtual void StartCollision(Entity* otherEntity) override;
	void SetOwner(Entity* owner);

protected:
	float rotation = 0;
	Entity* owner = nullptr;
};