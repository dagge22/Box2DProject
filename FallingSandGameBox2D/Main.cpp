#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <box2d/box2d.h>
#include <array>
#include "Box.h"
#include "World.h"
#include "Shape.h"
#include "PhysicsObject.h"
#include "Player.h"
#include "Terrain.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Falling sand");

	sf::Event evnt;

	srand(time(NULL));

	World world(&window);

	Entity wall(sf::Vector2f(10, 300));
	world.CreateRectangle(&wall, sf::Vector2f(20, 600));
	wall.SetFillColor(sf::Color::Red);

	Entity wall2(sf::Vector2f(590, 300));
	world.CreateRectangle(&wall2, sf::Vector2f(20, 600));
	wall2.SetFillColor(sf::Color::Red);

	Entity ground(sf::Vector2f(300, 590));
	world.CreateRectangle(&ground, sf::Vector2f(600, 20));
	ground.SetFillColor(sf::Color::Red);

	Entity roof(sf::Vector2f(300, 10));
	world.CreateRectangle(&roof, sf::Vector2f(600, 20));
	roof.SetFillColor(sf::Color::Red);

	Player player(sf::Vector2f(200, 300), sf::Vector2f(20, 30));
	world.CreateRectangle(&player, sf::Vector2f(20, 40));

	std::vector<sf::Vertex> lines;
	sf::Vertex v1(sf::Vector2f(300, 300), sf::Color::Red);
	lines.push_back(v1);
	sf::Vertex v2(sf::Vector2f(400, 300), sf::Color::Red);
	lines.push_back(v2);
	sf::Vertex v3(sf::Vector2f(500, 400), sf::Color::Red);
	lines.push_back(v3);
	sf::Vertex v4(sf::Vector2f(595, 300), sf::Color::Red);
	lines.push_back(v4);


	Entity rec(sf::Vector2f(300, 500));
	world.CreateRectangle(&rec, sf::Vector2f(50, 50));

	Entity circle(sf::Vector2f(200, 200), false);
	world.CreateCircle(&circle, 10);

	Entity circle2(sf::Vector2f(201, 0), true);
	world.CreateCircle(&circle2, 10);

	Entity circle3(sf::Vector2f(200, 30), true);
	world.CreateCircle(&circle3, 10);

	//Terrain terrain(sf::Vector2f(200, 200));
	//world.CreateEntity(&terrain);
	//terrain.SetPoints(lines);

	//b2Vec2* b2Lines = new b2Vec2[lines.size()];

	//for (int i = 0; i < lines.size(); i++)
	//{
	//	sf::Vertex* v = new sf::Vertex(lines[i].position, lines[i].color);
	//	//b2Lines.push_back(*v);

	//	//b2Lines[i] = b2Vec2(points[i].position.x / World::SCALE, points[i].position.y / World::SCALE);
	//	lines[i].position.x = lines[i].position.x / World::SCALE;
	//	lines[i].position.y = lines[i].position.y / World::SCALE;
	//}

	//b2ChainShape chain;
	//chain.CreateChain(b2Lines, lines.size(), b2Lines[0], b2Lines[lines.size()]);

	

	//Entity rec(sf::Vector2f(300, 300));
	//world.CreateRectangle(&rec, sf::Vector2f(50, 50));

	Terrain terrain;
	world.CreateEntity(&terrain);
	
	std::vector<sf::Vertex> ver;
	ver.push_back(sf::Vector2f(300, 300));
	ver.push_back(sf::Vector2f(350, 300));
	ver.push_back(sf::Vector2f(300, 350));
	//ver.push_back(sf::Vector2f(300, 300));

	//ver.push_back(sf::Vector2f(100, 100));
	//ver.push_back(sf::Vector2f(150, 100));
	//ver.push_back(sf::Vector2f(150, 150));


	terrain.SetPoints(ver);

	Entity a(sf::Vector2f(100, 100), true);
	world.CreateCircle(&a, 10);

	Entity b(sf::Vector2f(120, 120), true);
	world.CreateCircle(&b, 10);

	//b.GetBody()->ApplyAngularImpulse(10, true);

	//b2MouseJointDef jointDef;
	//b2MouseJoint* joint;

	//jointDef.bodyA = a.GetBody();
	//jointDef.bodyB = b.GetBody();
	//jointDef.collideConnected = true;

	//jointDef.damping = 0.01;
	//jointDef.stiffness = 0.01f;
	//jointDef.type = b2JointType::e_mouseJoint;
	//jointDef.maxForce = 100;

	//joint = (b2MouseJoint*)world.GetB2World()->CreateJoint(&jointDef);


	//b2RevoluteJointDef jointDef;
	//b2RevoluteJoint* joint;

	//jointDef.bodyA = a.GetBody();
	//jointDef.bodyB = b.GetBody();

	//jointDef.collideConnected = true;

	//world.GetB2World()->CreateJoint(&jointDef);
	

	Entity convex(true);

	std::vector<sf::Vector2f> points;
	points.push_back(sf::Vector2f(300, 300));
	points.push_back(sf::Vector2f(250, 350));
	points.push_back(sf::Vector2f(350, 350));

	//points.push_back(sf::Vector2f(280, 208))
	world.CreateConvex(&convex, points);

	while (window.isOpen())
	{
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		world.Update();

		//b.GetBody()->ApplyLinearImpulseToCenter(b2Vec2(0.000001f,0.000001f), true);
		//world.GetWindow()->draw(c, ver, 2, sf::TriangleStrip);

		//for (int i = 0; i < 4; i++)
		//{
		//	sf::CircleShape circle;
		//	circle.setPosition(sf::Vector2f(vs[i].x * World::SCALE, vs[i].y * World::SCALE));
		//	circle.setFillColor(sf::Color::Green);
		//	circle.setRadius(2);
		//	window.draw(circle);
		//}
	}

	return 0;
}
