#pragma once
#include "Entity.h"

class Terrain : public Entity
{
public:
	Terrain();

	void Draw(sf::RenderWindow* window);

	void SetPoints(const std::vector<sf::Vertex>& points);

private:
	sf::Sprite sprite;
	sf::Image image;
	sf::Texture texture;

	std::vector<sf::RectangleShape*> shapes;
	std::vector<sf::Vertex> lines;
	//std::vector<b2Vec2> b2Lines;
	b2Vec2* b2Lines;
	b2ChainShape chain;
};