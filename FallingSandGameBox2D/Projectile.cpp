#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position) :
	Entity(position, true)
{
}

void Projectile::Init()
{
}

void Projectile::StartCollision(Entity* otherEntity)
{
}

void Projectile::SetOwner(Entity* owner)
{
	this->owner = owner;
}
