#pragma once
#include "Projectile.h"

class PlayerProjectile : public Projectile
{
public:
	PlayerProjectile(const sf::Vector2f& position);

	void StartCollision(Entity* otherEntity) override;
};
