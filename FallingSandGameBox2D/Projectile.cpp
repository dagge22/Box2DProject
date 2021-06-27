#include "Projectile.h"

Projectile::Projectile(const sf::Vector2f& position) :
	Entity(position, true)
{
	this->position = position;
	//this->rotation = rotation;
}

void Projectile::Init()
{
	Rotate(rotation);
}

void Projectile::StartCollision(Entity* otherEntity)
{
	//physicsEnabled = false;
	//body->SetLinearVelocity(b2Vec2(0, 0));
	//body->SetAngularVelocity(0);
	//bodyDef.type = b2BodyType::b2_staticBody;
	//EnablePhysics(false);

	//world->DeleteEntity(this);

	//markedForDelete = true;

	//body->SetEnabled(false);
	//world->disableList.push_back(this);
}

void Projectile::SetOwner(Entity* owner)
{
	this->owner = owner;
}
