#include "PlayerProjectile.h"
#include "Player.h"

PlayerProjectile::PlayerProjectile(const sf::Vector2f& position)
	: Projectile(position)
{
}

void PlayerProjectile::StartCollision(Entity* otherEntity)
{
	DisablePhysics();
}
