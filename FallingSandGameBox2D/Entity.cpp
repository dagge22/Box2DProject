#include "Entity.h"
#include <array>

Entity::Entity(const sf::Vector2f& position, bool usePhysics)
{
	this->position = position;
	physicsEnabled = usePhysics;
	bodyDef.type = physicsEnabled ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody;
}

Entity::Entity(bool usePhysics)
{
	physicsEnabled = usePhysics;
	bodyDef.type = physicsEnabled ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody;
}

Entity::~Entity()
{
	body->DestroyFixture(fixture);
	std::cout << "Destroyed\n";
}

void Entity::Update()
{
	if (!physicsEnabled)
		return;

	shape->setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	shape->setRotation(body->GetAngle() * 180 / b2_pi);
	position = shape->getPosition();
}

// Only works for dynamic b2 bodies (?)
void Entity::SetPosition(const sf::Vector2f& position)
{
	this->position = position;
	GetBody()->SetTransform(b2Vec2(position.x / (float)World::SCALE, position.y / (float)World::SCALE), body->GetAngle());
}

void Entity::SetShape(sf::Shape* newShape)
{
	shape = newShape;
}

void Entity::SetFillColor(const sf::Color& newColor)
{
	shape->setFillColor(newColor);
}

void Entity::EnablePhysics(bool enable)
{
	if (enable)
	{
		bodyDef.type = b2BodyType::b2_dynamicBody;
	}

	physicsEnabled = enable;
}

// This could all be cleaned up and fixed. But not today :)
void Entity::SetCircle(float radius)
{
	bodyDef.type = physicsEnabled ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody;
	shape->setOrigin(radius, radius);

	bodyDef.position.Set(position.x / World::SCALE, position.y / World::SCALE);
	body = world->GetB2World()->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = radius / (float)World::SCALE;

	fixtureDef.shape = &circle;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.1f;

	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	fixture = body->CreateFixture(&fixtureDef);

	shape->setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	shape->setRotation(body->GetAngle() * 180 / b2_pi);
	position = shape->getPosition();
}

void Entity::SetRectangle()
{
	bodyDef.type = physicsEnabled ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody;
	shape->setOrigin(size.x * 0.5f, size.y * 0.5f);

	bodyDef.position.Set(position.x / World::SCALE, position.y / World::SCALE);
	body = world->GetB2World()->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((size.x * 0.5) / World::SCALE, (size.y * 0.5) / World::SCALE);

	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 11.f;
	fixtureDef.friction = 0.3f;

	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	//bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	fixture = body->CreateFixture(&fixtureDef);

	shape->setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	shape->setRotation(body->GetAngle() * 180 / b2_pi);
	position = shape->getPosition();
}

void Entity::SetConvex(const std::vector<sf::Vector2f>& points)
{
	bodyDef.type = physicsEnabled ? b2BodyType::b2_dynamicBody : b2BodyType::b2_staticBody;
	//shape->setOrigin(size.x * 0.5f, size.y * 0.5f);

	bodyDef.position.Set(position.x / World::SCALE, position.y / World::SCALE);
	body = world->GetB2World()->CreateBody(&bodyDef);

	b2PolygonShape poly;
	b2Vec2* b2Points = new b2Vec2[points.size()];

	for (int i = 0; i < points.size(); i++)
	{
		b2Points[i].x = points[i].x / World::SCALE;
		b2Points[i].y = points[i].y / World::SCALE;
	}

	poly.Set(b2Points, points.size());

	fixtureDef.shape = &poly;
	fixtureDef.density = 11.f;
	fixtureDef.friction = 0.3f;

	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

	fixture = body->CreateFixture(&fixtureDef);

	shape->setPosition(body->GetPosition().x * (float)World::SCALE, body->GetPosition().y * (float)World::SCALE);
	shape->setRotation(body->GetAngle() * 180 / b2_pi);
	position = shape->getPosition();

	delete[] b2Points;
}

void Entity::SetFixtureDef(const b2FixtureDef& def)
{
	fixtureDef = def;
}

void Entity::Rotate(float angle)
{
	body->SetTransform(body->GetPosition(), angle);
	angle *= 180 / b2_pi;
	std::cout << "angle: " << angle << "\n";
	shape->setRotation(angle);
}

void Entity::Delete()
{
	markedForDelete = true;
}

// Disable collision and physics movement
void Entity::DisablePhysics()
{
	world->disableList.push_back(this);
}

// Disable physics and dont draw it
//void Entity::SetEnable(bool enable)
//{
//	world->disableList.push_back(this);
//	draw = enable;
//}
