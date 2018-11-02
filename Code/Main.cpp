// Basic C++ application demonstrating the usage of fuzzy logic to steer an AI-controlled car towards a player-defined road
// Uses FFLL (Free Fuzzy Logic Library) to define the fuzzy inference system in a fuzzy control language script
// Available at: http://ffll.sourceforge.net/index.html
// Uses SFML's graphics library to do window handling, sprite and text rendering
// SFML (Simple and Fast Multimedia Library) - Copyright (c) Laurent Gomila
// Available at: https://www.sfml-dev.org/index.php

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "FFLLAPI.h"
#include "Road.h"
#include "Player.h"

// Function for loading the FCL file that contains the fuzzy logic for FFLL
int LoadFCLFile(int model)
{

	int result = (int)ffll_load_fcl_file(model, "FCLSteering.fcl");

	// If the file isn't found, end the program
	if (result < 0)
	{
		std::cout << "Error Opening FCLSteering.fcl";
		return 0;
	}

	return 1;

}

// Function for running a visual simulation based on the fuzzy inference system
void RunSimulation(int model, int child)
{

	// Pre-simulation input, allowing the user to control the speed of the simulation
	std::cout << "Please enter a simulation speed (time to sleep for in milliseconds): ";

	int simulationTime = 0;

	std::cin >> simulationTime;

	// Create the render window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Fuzzy Logic Racer");

	int roadPosition = 357;
	int playerStartPosX = 640;

	// Initialise the roadTiles, which will indicate to us where the road is
	const int roadSize = 20;
	Road* roadTiles = new Road[roadSize];

	for (int i = 0; i < roadSize; i++)
	{

		roadTiles[i].Init(i * 70, roadPosition);

	}

	// Create a tile for input - this will be the tile whose position we want the player to steer towards
	Road* nextRoadTile;

	// Initialise the player
	Player* player = new Player();
	player->Init(playerStartPosX, roadPosition);

	// Main simulation loop
	while (window.isOpen())
	{

		// SFML event handling
		sf::Event event;

		// Currently only expecting to handle the Closed event
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{

				window.close();

			}

		}

		// Handle user input and make sure that the road position stays within the bounds of the FIS distance input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && roadPosition > 207)
		{

			roadPosition -= 30;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && roadPosition < 507)
		{

			roadPosition += 30;

		}

		// Update the road tiles' positions for a consistent visualisation
		for (int i = 0; i < roadSize; i++)
		{

			// When road tiles go offscreen to the left, update their position to be to the right of the screen
			if (roadTiles[i].GetXPos() < -50)
			{

				roadTiles[i].SetPosition(((roadSize - 1) * 70) + 10, roadPosition);

			}

			if (roadTiles[i].GetXPos() > playerStartPosX && roadTiles[i].GetXPos() < playerStartPosX + 70)
			{

				nextRoadTile = &roadTiles[i];

			}

			roadTiles[i].Update();

		}

		// Update the player position based on output from FIS
		float speed = player->GetSpeed();
		float distance = (nextRoadTile->GetYPos() - player->GetYPos());

		// Get inputs for FIS
		ffll_set_value(model, child, 0, speed);			// speed is the first variable expected by the FCL script, so var_idx = 0
		ffll_set_value(model, child, 1, distance);		// while distance is the second variable expected by the FCL script, so var_idx = 1

		// Get defuzzified output from FIS
		float output = ffll_get_output_value(model, child);

		std::cout << "Output: " << output << "\n";

		// Change the speed according to the output acceleration
		player->SetSpeed(output);

		std::cout << "Player position/speed: (" << player->GetXPos() << "," << player->GetYPos() << ") and " << speed << "\n";
		std::cout << "Distance to travel: " << distance << "\n\n";

		// Update the player's position based on the new speed
		player->Update();

		window.clear();

		// Render the road tiles
		for (int i = 0; i < roadSize; i++)
		{

			roadTiles[i].Render(&window);

		}

		// Render the player
		player->Render(&window);

		window.display();

		// Sleep for the inputted amount of time
		std::this_thread::sleep_for(std::chrono::milliseconds(simulationTime));

	}

	window.close();

	// Release objects now that the simulation's over
	delete[] roadTiles;
	delete player;

	return;

}

// Function for testing inputs individually from user input
void TestInputs(int model, int child)
{

	// Initialise variables for fuzzy input
	int speed = 0;
	int distance = 0;
	// Allow the user to input as many times as they like
	char continueInput = 'Y';

	// Run while the user wants to test inputs
	while (continueInput != 'N')
	{

		// Get the speed
		std::cout << "Enter an integer to represent the speed (ranges -30 to 30): ";

		std::cin >> speed;

		// Make sure the speed is valid
		if (speed > 30 || speed < -30)
		{

			std::cout << "That is not a valid input.\n";

		}
		else
		{

			// Get the distance
			std::cout << "\nEnter an integer to represent the distance (ranges 300 to -300): ";

			std::cin >> distance;

			// Make sure the distance is valid
			if (distance > 300 || distance < -300)
			{

				std::cout << "That is not a valid input.\n";

			}
			else
			{

				// Input variables into the FIS
				ffll_set_value(model, child, 0, speed);			// speed is the first variable expected by the FCL script, so var_idx = 0
				ffll_set_value(model, child, 1, distance);		// while distance is the second variable expected by the FCL script, so var_idx = 1

				// Get defuzzified output from FIS
				float output = ffll_get_output_value(model, child);

				std::cout << "Output speed is: " << output << " m/s.";

			}

		}

		// Prompt user on whether they wish to continue inputting data
		std::cout << "\nContinue inputting data (Y/N)? ";

		std::cin >> continueInput;

	}

}

// Function for testing a specified set of inputs for the fuzzy inference system; outputs to a .csv file
void AutoTest(int model, int child)
{

	std::ofstream dataFile;
	dataFile.open("outputData.csv");

	for (int speed = -30; speed <= 30; speed += 2)
	{

		for (int distance = -300; distance <= 300; distance += 30)
		{

			// Input variables into the FIS
			ffll_set_value(model, child, 0, speed);			// speed is the first variable expected by the FCL script, so var_idx = 0
			ffll_set_value(model, child, 1, distance);		// while distance is the second variable expected by the FCL script, so var_idx = 1

			// Get defuzzified output from FIS
			float output = ffll_get_output_value(model, child);

			dataFile << speed << "," << distance << "," << output << "\n";

		}

	}

	dataFile.close();

	std::cout << "\nTesting complete. Data will be stored in outputData.csv.\n\n";

}

int main()
{

	// Get the FIS from the fuzzy control language file
	int model = ffll_new_model();

	// Load the FCL file and make sure it's valid
	if (LoadFCLFile(model) == 0)
	{

		std::cout << "\n\nFCL File not found\n\n";
		return 0;

	}

	int child = ffll_new_child(model);

	// Run until the user ends the program
	while (true)
	{

		// Get user input
		std::cout << "\nSelect what mode you want the program to run in (0 for simulation, 1 for test data input, 2 for automated data testing, 3 to quit)\n";

		int modeInt = 0;

		std::cin >> modeInt;

		// Run the racing simulation
		if (modeInt == 0)
		{

			RunSimulation(model, child);

		}
		// Get input data from the user
		else if (modeInt == 1)
		{

			TestInputs(model, child);

		}
		// Run through a pre-specified set of data
		else if (modeInt == 2)
		{

			AutoTest(model, child);

		}
		// Quit
		else if (modeInt == 3)
		{

			// End the program
			return 0;

		}
		else
		{

			std::cout << "That is not a valid input.\n\n";

		}

	}

}