// Map Class uses fstream to load a 
// file of 1s and 0s. For each 1, a 
// brick is rendered on the corresponding
// location on the map

#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Global_Constants.h"

using namespace std;

class Map : public Global_Constants{
	public:
		// Map Constructor
		Map();

		// Non-default constructor
		Map(string);

		// Load the brick png file
		bool load_bricks();

		// Load coordinates of bricks into vector
		void get_coordinates();

		// Render the bricks on map
		void render_Bricks(int);

		// Returns whether is brick is there
		bool isBrick_down(int, int, int);

		// Check if a brick is up
		bool isBrick_up(int, int, int);
		
		// Check if a brick is to the right
		bool isBrick_right(int, int, int);

		// check left
		bool isBrick_left(int, int);
	
		// Return amount of space between location input 
		// and nearest brick down
		int space_brick_down(int, int);
	
		// Same, but for space up
		int space_brick_up(int, int, int);
	
		// Check if brick is contained there
		int get_BrickLocation(int, int);

		// Brick Rendering
		SDL_Rect BrickLocation;
		LTexture Brick;

		// 2-d vector to contain brick coordinates
		vector<vector<int> > BrickCoordinates;
	protected:
		string file;
		int gMapLocation_x;
};

#endif

Map::Map() 
{
	get_coordinates();
}

Map::Map(string f)
{
	// initialize name of file and load coordinates
	file = f;
	get_coordinates();
}

// load png file
bool Map::load_bricks()
{
	bool success = true;
	//Load sprite sheet texture
	if( !Brick.loadFromFile("Media/brick.png", "green" ) )
	{
		cout << "failed to load " << file << endl;
		success = false;
	}
	else
	{
		BrickLocation.x = 0;	
		BrickLocation.y = 0;
		BrickLocation.w = 32;
		BrickLocation.h = 32;
	}
	return success;
}

// load coordinate into a 2-d vector of ints;
// every element represents the 32 pixels on the
// screen since that is the height and width of brick
void Map::get_coordinates()
{
	ifstream map_file;
	map_file.open(file.c_str());
	vector<int> temp;
	int num;
	while (!map_file.eof()) {
		map_file >> num;
		if (num == -1) {
			BrickCoordinates.push_back(temp);
			break;
		}
		if (num != 2)
			temp.push_back(num);
		else {
			BrickCoordinates.push_back(temp);
			temp.clear();
		}
	}
}

// Render the bricks onto the screen
void Map::render_Bricks(int gLocation_x)
{
	SDL_Rect* currentMap = &BrickLocation;
	int location[2];
	location[X] = 0;
	location[Y] = 0;
	gMapLocation_x = gLocation_x;
	
	for (int i = 0; i < BrickCoordinates.size(); i++) {
		location[Y] = i*32;
		for (int j = 0; j < BrickCoordinates[i].size(); j++) {
				location[X] = j*32;
				if (BrickCoordinates[i][j] == 1) {
					currentMap = &BrickLocation;
					Brick.render( location[X] - gMapLocation_x, location[Y], currentMap );
				}	
		}
		location[Y] = i*32;
	}
}

// Check if Mario is on top of a brick
bool Map::isBrick_down(int xloc, int yloc, int yVel)
{
	int x_coord = xloc/BRICK_HEIGHT;
	int x_remainder = xloc % BRICK_HEIGHT;
	int y_coord = (yloc + LEP_HEIGHT- 3) / BRICK_HEIGHT;
	int y_remainder = (yloc + LEP_HEIGHT) % BRICK_HEIGHT;

	if (BrickCoordinates[y_coord][x_coord] == 1 && x_remainder < LEP_WIDTH- 5) {
		return true;
	}
	else {
		if (x_remainder > BRICK_WIDTH- LEP_WIDTH+ 5) {
			if (BrickCoordinates[y_coord][x_coord+1] == 1) {
				return true;
			}
		}
	}
	return false;
}

// Check if there is a brick above mario
bool Map::isBrick_up(int xloc, int yloc, int yVel)
{
	int x_coord = xloc/BRICK_HEIGHT;
	int x_remainder = xloc % BRICK_HEIGHT;
	int y_coord = (yloc + yVel - 6) / BRICK_HEIGHT;
	int y_remainder = (yloc) % BRICK_HEIGHT;
	if (yloc + yVel -6 <= 0) return true;
	if (BrickCoordinates[y_coord][x_coord] == 1 && x_remainder < LEP_WIDTH- 5) {
		return true;
	}
	else {
		if (x_remainder > BRICK_WIDTH- LEP_WIDTH+ 5) {
			if (BrickCoordinates[y_coord][x_coord+1] == 1) {
				return true;
			}
		}
	}
	return false;
}

// Check if there is a brick to the right of mario
bool Map::isBrick_right(int xloc, int yloc, int yVel)
{
	int x_coord = (xloc + LEP_WIDTH+ 2) / BRICK_HEIGHT;
	int x_remainder = (xloc + LEP_WIDTH) % BRICK_HEIGHT;
	int y_coord = (yloc) / BRICK_HEIGHT;
	int y_remainder = (yloc) % BRICK_HEIGHT;
	if (BrickCoordinates[y_coord][x_coord] == 1) {
		return true;
	}
	else if (BrickCoordinates[y_coord + 1][x_coord] == 1)
		return true;
	else {
			return false;
	}
}

// Check if there is a brick to the left
bool Map::isBrick_left(int xloc, int yloc)
{
	int x_coord = (xloc - 4) / BRICK_HEIGHT;
	int x_remainder = (xloc) % BRICK_HEIGHT;
	int y_coord = (yloc) / BRICK_HEIGHT;
	int y_remainder = (yloc) % BRICK_HEIGHT;
	if (BrickCoordinates[y_coord][x_coord] == 1) {
		return true;
	}
	else if (BrickCoordinates[y_coord + 1][x_coord] == 1)
		return true;
	else {
			return false;
	}
}

// Call is brick down until brick or bottom of screen
// is reached and return distance
int Map::space_brick_down(int xloc, int yloc) 
{
	int brick_space = 0;
	do					
	{
	++brick_space;
	if (brick_space + yloc + LEP_HEIGHT== SCREEN_HEIGHT) 
		break;
	} while (!isBrick_down(xloc, yloc + brick_space, 0) ); 
	
	return brick_space;
}

// Same as above, but for going up
int Map::space_brick_up(int xloc, int yloc, int yVel)
{
	int brick_space = 0;
	do					
	{
	++brick_space;
	if (yloc - brick_space == 0) 
		break;
	} while (!isBrick_up(xloc, yloc - brick_space, 0) ); 
	
	return brick_space;
}

// Check if brick is located there
int Map::get_BrickLocation(int x, int y)
{
	return BrickCoordinates[y/BRICK_WIDTH][x/BRICK_HEIGHT];
}
