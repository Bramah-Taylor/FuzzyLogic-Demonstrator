# Fuzzy Logic Demonstrator

This is a simple application designed to demonstrate the usage of fuzzy logic as steering AI in a racetrack which is controlled by the user. This application was originally designed to fulfil a coursework brief concerning fuzzy logic. It is **not** designed to demonstrate best practices of AI implementation or steering in a racing game.

## Requirements

This application was built using SFML, and consequently requires the SFML binaries to run and SFML libraries to compile. The latest version of SFML can be downloaded [here](https://www.sfml-dev.org/download.php). The application also uses the Free Fuzzy Logic Library (FFLL) for fuzzy logic functionality, which can be downloaded [here](http://ffll.sourceforge.net/downloads.htm).

## Instructions for Use

The application has three settings, and the user will be prompted to choose one at the start.

The first mode is the input testing mode. As the name implies, this will take two inputs (speed and distance) and give an output (acceleration). The application will loop through one instance after inputs are received from the user, inputting the data into the fuzzy inference system and outputting the acceleration. The user will then be prompted to continue inputting test data, or to stop.

The second mode is the automated testing mode. This function will output a .csv file based on over 600 inputs covering distances ranging from -300 to 300 in increments of 30, and input speeds ranging from -30 to 30 in increments of 2. For each increment, the FIS will be tested and will get an output. These two inputs and the output will then be written to the .csv file named OutputData.csv. The testing will end once all of the possible inputs have been incremented through. The number of increments has been limited for ease of visualisation, for if the application incremented by 1 each time for both inputs, we would have over 36000 pieces of data to visualise.

The third mode is the actual steering simulation. In this mode, the user will first be prompted for an input time for the application run speed; this uses C++'s sleep_for function to sleep the thread for a specified number of milliseconds. In testing, 20 milliseconds works well for visualisation (running at 50 FPS), and 200 works well for testing (running at 5 FPS). The application will output speed, distance and acceleration to the console window, which remains open in the background.

This mode uses SFML to create a window in which the racetrack is visualised. The racecar will be shown "moving" horizontally along the racetrack (although it's actually the racetrack moving; the car only moves vertically). The user can then use the up arrow key and down arrow key to move the racetrack. The car will move towards the next piece of racetrack using the output from the fuzzy inference system. The FIS will take the car's speed and the distance between the car and the next piece of track as inputs, and get an acceleration accordingly. This runs every frame.
