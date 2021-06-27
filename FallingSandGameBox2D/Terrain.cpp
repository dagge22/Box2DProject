#include "Terrain.h"

Terrain::Terrain()
{
}

void Terrain::Draw(sf::RenderWindow* window)
{
	lines[0].color = sf::Color::Red;
	lines[1].color = sf::Color::Blue;
	lines[2].color = sf::Color::Green;

	window->draw(&lines[0], lines.size(), sf::LinesStrip);
}

void Terrain::SetPoints(const std::vector<sf::Vertex>& points)
{
	b2Lines = new b2Vec2[points.size()];
	for (int i = 0; i < points.size(); i++)
	{
		sf::Vertex* v = new sf::Vertex(points[i].position, points[i].color);
		lines.push_back(*v);
		b2Lines[i].x = points[i].position.x / World::SCALE;
		b2Lines[i].y = points[i].position.y / World::SCALE;

		std::cout << b2Lines[i].x << " " << b2Lines[i].y << "\n";
	}
	//chain.CreateChain(b2Lines, points.size(), b2Lines[0], b2Lines[points.size()]);
	chain.CreateLoop(b2Lines, points.size());



	//b2Lines = new b2Vec2[points.size()];
	//for (int i = 0; i < points.size(); i++)
	//{
	//	sf::Vertex* v = new sf::Vertex(points[i].position, points[i].color);
	//	lines.push_back(*v);
	//	b2Lines[i].x = points[i].position.x * World::SCALE;
	//	b2Lines[i].y = points[i].position.y * World::SCALE;

	//	std::cout << b2Lines[i].x << " " << b2Lines[i].y << "\n";
	//}
	////edge.SetTwoSided(v1, v2);

	//chain.SetTwoSided(b2Lines[0], b2Lines[1]);
}
