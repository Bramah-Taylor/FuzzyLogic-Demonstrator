#include "Road.h"



Road::Road()
{

	// Set up the sprite representing the road tile
	sprite = new sf::RectangleShape(sf::Vector2f(50.0f, 5.0f));
	sprite->setFillColor(sf::Color::White);

}

Road::~Road()
{

	if (sprite)
	{

		delete sprite;
		sprite = nullptr;

	}

}

void Road::Init(int PosX, int PosY)
{

	// Set the road to their initial position (0, 357 by default)
	sprite->setPosition(PosX, PosY);

	// Output those variables to a struct
	position.x = PosX;
	position.y = PosY;

}

void Road::Update()
{

	position.x -= 10;

	sprite->setPosition(position.x, position.y);

}

void Road::Render(sf::RenderWindow* window)
{

	// Render the shape
	window->draw(*sprite);

}