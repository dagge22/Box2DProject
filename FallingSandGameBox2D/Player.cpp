#include "Player.h"
#include <iostream>
#include "Projectile.h"
#include "PlayerProjectile.h"

Player::Player(const sf::Vector2f& position, const sf::Vector2f& size) 
	: Entity(position, true)
{
}

void Player::Update()
{
	Entity::Update();
	Input();
	Move();
	if (ropeOut)
	{
		UpdateRopePosition();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		Jump();
	}
	if (direction.x == 0)
	{
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
	}
}

void Player::Draw(sf::RenderWindow* window)
{
	window->draw(*shape);
	if (ropeOut)
	{
		window->draw(&rope[0], rope.size(), sf::LinesStrip);
	}
}

void Player::Init()
{
	body->SetGravityScale(15.f);
	body->SetFixedRotation(true);

	projectile = new PlayerProjectile(sf::Vector2f(position.x, position.y - size.x - 10));
	world->CreateRectangle(projectile, sf::Vector2f(4, 4));
	projectile->GetBody()->SetBullet(true);
	projectile->GetShape()->setFillColor(sf::Color::Green);
	projectile->SetOwner(this);
	projectile->SetShouldDraw(false);
	projectile->DisablePhysics();
	projectile->GetBody()->SetGravityScale(0);
}

void Player::StartCollision(Entity* otherEntity)
{
}

void Player::EndCollision(Entity* otherEntity)
{
}

void Player::Input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
		direction.x -= 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
		direction.x += 1;
	}
	else
		direction = b2Vec2(0, body->GetLinearVelocity().y);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clock.getElapsedTime().asSeconds() >= cooldown)
	{
		ShootLine();
		clock.restart();
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		RemoveRope();
	}
}

void Player::Move()
{
	b2Vec2 vel = body->GetLinearVelocity();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction.x = -10;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction.x = 10;
	}
	else
		direction.x = 0;

	if (ropeOut)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			sf::Vector2f ropeDirection = rope[1].position - rope[0].position;
			const float length = std::sqrtf(ropeDirection.x * ropeDirection.x + ropeDirection.y * ropeDirection.y);
			ropeDirection.x /= length;
			ropeDirection.y /= length;

			ropeDirection.x * ropeReelSpeed;
			ropeDirection.y * ropeReelSpeed;

			direction.x = ropeDirection.x * ropeReelSpeed;
			direction.y = ropeDirection.y * ropeReelSpeed; 

			//SetPosition(position + ropeDirection);
		}
	}

	//float velChange = direction.x - vel.x;
	//float impulse = body->GetMass() * velChange;
	//body->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);

	const float velChangeX = direction.x - vel.x;
	const float velChangeY = direction.y - vel.y;
	const float impulseX = body->GetMass() * velChangeX;
	const float impulseY = body->GetMass() * velChangeY;
	body->ApplyLinearImpulseToCenter(b2Vec2(impulseX, impulseY), true);
}

void Player::RemoveRope()
{
	rope.clear();
	ropeOut = false;
	projectile->SetShouldDraw(false);
}

void Player::Jump()
{
	if (body->GetLinearVelocity().y <= 0.01f && body->GetLinearVelocity().y >= -0.01f)
	{
		body->ApplyLinearImpulseToCenter(b2Vec2(0, -300.f), true);
	}
}

void Player::ShootLine()
{
	rope.clear();
	ropeOut = true;

	const sf::Vector2i mousePos = sf::Mouse::getPosition(*world->GetWindow());
	const sf::Vector2f spawnPosition(position.x, position.y - size.x - 10);
	sf::Vector2f direction(mousePos.x - spawnPosition.x, mousePos.y - spawnPosition.y);
	//const float angle = std::atan2(direction.x, direction.y);

	//projectile->GetBody()->SetAngularVelocity(0);
	projectile->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	projectile->SetPosition(spawnPosition);
	projectile->SetShouldDraw(true);
	projectile->GetBody()->SetEnabled(true);

	const float length = std::sqrtf(direction.x * direction.x + direction.y * direction.y);

	direction.x /= length;
	direction.y /= length;

	const b2Vec2 impulse(direction.x * 8, direction.y * 8);
	projectile->GetBody()->ApplyLinearImpulseToCenter(impulse, true);

	rope.push_back(position);
	rope.push_back(projectile->GetPosition());
	rope[0].color = sf::Color(138, 68, 15);
	rope[1].color = sf::Color(138, 68, 15);
}

void Player::UpdateRopePosition()
{
	rope[0].position = position;
	rope[1].position = projectile->GetPosition();
}
