#include "Player.h"



Player::Player()
{

	// Set up the sprite representing the Player tile
	sprite = new sf::RectangleShape(sf::Vector2f(40.0f, 20.0f));
	sprite->setFillColor(sf::Color::Green);

	speed = 0;

}

Player::~Player()
{

	if (sprite)
	{

		delete sprite;
		sprite = nullptr;

	}

}

void Player::Init(int PosX, int PosY)
{

	// Set the Player to their initial position (640, 357 by default)
	sprite->setPosition(PosX, PosY);

	// Output those variables to a struct
	position.x = PosX;
	position.y = PosY;

}

void Player::Update()
{

	position.y += speed;

	sprite->setPosition(position.x, position.y);

}

void Player::Render(sf::RenderWindow* window)
{

	// Render the shape
	window->draw(*sprite);

}

void Player::SetSpeed(float input)
{ 

	// Make sure that the speed isn't beyond the bounds of the FIS inputs
	if (speed < -30.0f)
	{

		speed = -30.0f;

	}
	else if (speed > 30.0f)
	{

		speed = 30.0f;

	}
	else
	{

		speed += input;

	}

}