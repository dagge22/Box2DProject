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

	Entity rec(sf::Vector2f(300, 500));
	world.CreateRectangle(&rec, sf::Vector2f(50, 50));

	Entity circle(sf::Vector2f(200, 200), false);
	world.CreateCircle(&circle, 10);

	Entity circle2(sf::Vector2f(201, 0), true);
	world.CreateCircle(&circle2, 10);

	Entity circle3(sf::Vector2f(200, 30), true);
	world.CreateCircle(&circle3, 10);

	Terrain terrain;
	world.CreateEntity(&terrain);
	std::vector<sf::Vertex> ver;
	ver.push_back(sf::Vector2f(300, 300));
	ver.push_back(sf::Vector2f(350, 300));
	ver.push_back(sf::Vector2f(300, 350));

	terrain.SetPoints(ver);		// Not working

	Entity a(sf::Vector2f(100, 100), true);
	world.CreateCircle(&a, 10);

	Entity b(sf::Vector2f(120, 120), true);
	world.CreateCircle(&b, 10);

	Entity convex(true);
	std::vector<sf::Vector2f> points;
	points.push_back(sf::Vector2f(300, 300));
	points.push_back(sf::Vector2f(250, 350));
	points.push_back(sf::Vector2f(350, 350));
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
	}

	return 0;
}
