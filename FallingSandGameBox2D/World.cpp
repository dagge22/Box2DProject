#include "World.h"
#include <box2d/box2d.h>
#include "Entity.h"
#include <iostream>
#include "Box.h"
#include <SFML/Graphics.hpp>
#include "PhysicsObject.h"
#include "Player.h"
#include "Terrain.h"

int World::SCALE = 30;

World::World(sf::RenderWindow* window)
{
	this->window = window;
	gravity.x = 0;
	gravity.y = 10;

	b2world = new b2World(gravity);
	srand(time(NULL));

	b2world->SetContactListener(&listener);
}

World::~World()
{
	delete b2world;
}

void World::Update()
{
	frameLimitTimer += clock.restart().asSeconds();
	if (frameLimitTimer >= timeStep)
	{
		window->display();
		window->clear();

		b2world->Step(timeStep, velocityIterations, positionIterations);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			b2Vec2 vec(mousePos.x / World::SCALE, mousePos.y / World::SCALE);

			std::cout << "mousePos " << "x: " << mousePos.x << " : y " << mousePos.y << "\n";
			std::cout << "mousePos " << "x: " << mousePos.x / World::SCALE << " : y " << mousePos.y / World::SCALE << "\n";
		}

		for (int i = 0; i < enteties.size(); i++)
		{
			enteties[i]->Update();
			if (enteties[i]->ShouldDraw())
			{
				enteties[i]->Draw(window);
			}
		}

		int counter = 0;
		for (Entity* entity : disableList)
		{
			entity->GetBody()->SetEnabled(false);
			disableList.erase(disableList.begin() + counter);
			++counter;
		}

		DeleteEnteties();

		frameLimitTimer = 0;
	}
}

void World::CreateEntityInternal(Entity* entity)
{
	entity->SetWorld(this);
	enteties.push_back(entity);
}

void World::DeleteEnteties()
{
	int counter = 0;
	for (Entity* e : enteties)
	{
		if (e->IsMarkedForDeletion())
		{
			enteties.erase(enteties.begin() + counter);
			delete e;
		}
		++counter;
	}
}

void World::CreateEntity(Entity* entity)
{
	CreateEntityInternal(entity);
}

void World::CreatePhysicsObject(PhysicsObject* object)
{
	object->SetWorld(this);
	enteties.push_back(object);
	object->Init();
}

void World::CreateRectangle(Entity* entity, const sf::Vector2f& position, const sf::Vector2f& size)
{
	sf::RectangleShape* rec = new sf::RectangleShape(size);
	rec->setPosition(position);
	rec->setFillColor(sf::Color::White);

	CreateEntity(entity);

	entity->SetShape(rec);
	entity->Init();
}

void World::CreateCircle(Entity* entity, float radius)
{
	sf::CircleShape* cirlce = new sf::CircleShape(radius);
	cirlce->setPosition(entity->GetPosition());
	cirlce->setFillColor(sf::Color::White);

	CreateEntity(entity);

	entity->SetShape(cirlce);
	entity->SetCircle(radius);
	entity->Init();
}

void World::CreateRectangle(Entity* entity, const sf::Vector2f& size)
{
	sf::RectangleShape* rec = new sf::RectangleShape(size);
	rec->setPosition(entity->GetPosition());
	rec->setFillColor(sf::Color::Red);

	CreateEntity(entity);

	entity->SetSize(size);
	entity->SetShape(rec);
	entity->SetRectangle();
	entity->Init();
}

void World::CreateConvex(Entity* entity, const std::vector<sf::Vector2f>& points)
{
	sf::ConvexShape* convex = new sf::ConvexShape();
	convex->setPosition(entity->GetPosition());
	convex->setFillColor(sf::Color::Blue);
	convex->setPointCount(points.size());

	for (int i = 0; i < points.size(); i++)
	{
		convex->setPoint(i, points[i]);
	}

	CreateEntity(entity);

	entity->SetShape(convex);
	entity->SetConvex(points);
	entity->Init();
}

//void World::Explosion(const b2Vec2& position, float radius, float force)
//{
//	b2Body* itr = b2world->GetBodyList();
//	
//	while (itr != nullptr)
//	{
//		b2Vec2 vec(itr->GetPosition() - position);
//		if (vec.LengthSquared() < radius * radius)
//		{
//			vec.Normalize();
//			vec.x *= force;
//			vec.y *= force;
//			itr->ApplyLinearImpulseToCenter(vec, true);
//		}
//
//		itr = itr->GetNext();
//	}
//}

// ------------------------ Collision ---------------------------
void ContactListener::ContactListener::BeginContact(b2Contact* contact)
{
	//b2Fixture* defA = contact->GetFixtureA();
	//b2Fixture* defB = contact->GetFixtureB();

	//b2BodyUserData userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	//b2BodyUserData userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	b2FixtureUserData dataA = contact->GetFixtureA()->GetUserData();
	b2FixtureUserData dataB = contact->GetFixtureB()->GetUserData();

	Entity* ent = reinterpret_cast<Entity*>(dataB.pointer);
	Entity* ent2 = reinterpret_cast<Entity*>(dataA.pointer);

	if (ent)
	{
		ent->StartCollision(ent2);
	}
	if (ent2)
	{
		ent2->StartCollision(ent);
	}

	std::cout << "Collision\n";
}

void ContactListener::ContactListener::EndContact(b2Contact* contact)
{
	b2FixtureUserData dataA = contact->GetFixtureA()->GetUserData();
	b2FixtureUserData dataB = contact->GetFixtureA()->GetUserData();

	Entity* ent = reinterpret_cast<Entity*>(dataB.pointer);
	Entity* ent2 = reinterpret_cast<Entity*>(dataA.pointer);

	if (ent)
	{
		ent->EndCollision(ent2);
	}
	if (ent2)
	{
		ent2->EndCollision(ent);
	}
}
