// Class for the racecar/player to indicate where they are in the steering simulation

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <SFML/Graphics.hpp>

class Player
{
private:

	// Position struct used for the player tile's position
	struct Position {

		int x;
		int y;

	};

public:

	Player();
	~Player();

	// Initialise the player with a position
	void Init(int posX, int posY);
	// Update the player based on relevant data
	void Update();
	// Render the SFML sprite
	void Render(sf::RenderWindow* window);

	// Getters
	inline int GetXPos() { return position.x; };
	inline int GetYPos() { return position.y; };
	inline int GetSpeed() { return speed; };

	// Setters
	inline void SetPosition(int x, int y) { position.x = x; position.y = y; };
	void SetSpeed(float input);

private:

	sf::RectangleShape* sprite;

	Position position;
	float speed;

};

#endif // !_PLAYER_H_