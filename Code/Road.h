// Class for road tile sprites to indicate where the road is in the game

#ifndef _ROAD_H_
#define _ROAD_H_

#include <SFML/Graphics.hpp>

class Road
{
private:

	// Position struct used for the road tile's position
	struct Position {

		int x;
		int y;

	};

public:

	Road();
	~Road();
	
	// Initialise the player with a position
	void Init(int posX, int posY);
	// Update the player based on relevant data
	void Update();
	// Render the SFML sprite
	void Render(sf::RenderWindow* window);

	// Get position
	inline int GetXPos() { return position.x; };
	inline int GetYPos() { return position.y; };

	// Set position
	inline void SetPosition(int x, int y) { position.x = x; position.y = y; };

private:

	sf::RectangleShape* sprite;

	Position position;

};

#endif // !_ROAD_H_