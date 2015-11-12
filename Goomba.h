// Goomba inherits protected data and
// public functions from Enemy Class.
// Contains several virtual functions
// that override the ones defined in the
// enemy class

#ifndef GOOMBA_H
#define GOOMBA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>

using namespace std;

class Goomba : public Enemy {
	public:
		// Constructor
		Goomba();

		// Deconstructor
		~Goomba();

		// non-default constructor
		Goomba(int, int, int);

		// load enemy virtual function
		virtual bool load_enemy(string, string);

		// check if enemy beats mario
		virtual bool mario_die(int, int);

		// check if mario beats enemy
		virtual bool check_up(int, int, int);

		// set the x coordinate
		virtual void setxCoord(int);
	
		// render the enemy
		virtual void render_enemy(int);

	private:
		// Name of the png files for sprite sheets
		string playerpngLeft = "Media/goomba_left.png";
		string playerpngRight = "Media/goomba_right.png";
};

#endif


static int r_frame = 0;
static int l_frame = 0;


Goomba::Goomba() {}

// Call Goomba constructor and inherit from Enemy
Goomba::Goomba(int xf, int yf, int num_map)
	: Enemy(xf, yf, num_map, 2)
{
	if (!load_enemy(playerpngLeft, playerpngRight))
		throw invalid_argument("Failed to Load Goomba");
	if (Enemy::mapPtr->get_BrickLocation(Enemy::enemy_xcoord,Enemy::enemy_ycoord + Goomba_HEIGHT) == 0 || !Enemy::render_right) {
		cout << "For " << xf << " and " << yf << endl;
		cout << "For " << Enemy::enemy_xcoord << " and " << Enemy::enemy_ycoord << endl;
		if (!Enemy::render_right) cout << "cant render right\n";
		throw invalid_argument("Footaball player must be placed on a brick");
	}
}

Goomba::~Goomba()
{}

bool Goomba::load_enemy(string left, string right)
{
	bool success = true;
	//Load enemy sprite sheet texture going right
	if( !Enemy::gRightEnemyTexture.loadFromFile( right, "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		Enemy::gRightEnemy[ 0 ].x = 0;
		Enemy::gRightEnemy[ 0 ].y = 0;
		Enemy::gRightEnemy[ 0 ].w =  35;
		Enemy::gRightEnemy[ 0 ].h = 37;

		Enemy::gRightEnemy[ 1 ].x =  35;
		Enemy::gRightEnemy[ 1 ].y =  0;
		Enemy::gRightEnemy[ 1 ].w =  35;
		Enemy::gRightEnemy[ 1 ].h = 37;
		
		Enemy::gRightEnemy[ 2 ].x = 70;
		Enemy::gRightEnemy[ 2 ].y = 0;
		Enemy::gRightEnemy[ 2 ].w =  35;
		Enemy::gRightEnemy[ 2 ].h = 37;

		Enemy::gRightEnemy[ 3 ].x = 105;
		Enemy::gRightEnemy[ 3 ].y = 0;
		Enemy::gRightEnemy[ 3 ].w = 35;
		Enemy::gRightEnemy[ 3 ].h = 37;
	}

	if( !Enemy::gLeftEnemyTexture.loadFromFile( left, "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		Enemy::gLeftEnemy[ 0 ].x = 0;
		Enemy::gLeftEnemy[ 0 ].y = 0;
		Enemy::gLeftEnemy[ 0 ].w =  35;
		Enemy::gLeftEnemy[ 0 ].h = 37;

		Enemy::gLeftEnemy[ 1 ].x =  35;
		Enemy::gLeftEnemy[ 1 ].y =  0;
		Enemy::gLeftEnemy[ 1 ].w =  35;
		Enemy::gLeftEnemy[ 1 ].h = 37;
		
		Enemy::gLeftEnemy[ 2 ].x = 70;
		Enemy::gLeftEnemy[ 2 ].y = 0;
		Enemy::gLeftEnemy[ 2 ].w =  35;
		Enemy::gLeftEnemy[ 2 ].h = 37;

		Enemy::gLeftEnemy[ 3 ].x = 105;
		Enemy::gLeftEnemy[ 3 ].y = 0;
		Enemy::gLeftEnemy[ 3 ].w = 35;
		Enemy::gLeftEnemy[ 3 ].h = 37;
	}
	return success;
}

// Check if enemy beats mario
bool Goomba::mario_die(int mario_xcoord, int mario_ycoord) 
{
	if (!Enemy::alive) return false;
	if ( (mario_xcoord - Enemy::enemy_xcoord) < Goomba_WIDTH &&(Enemy::enemy_xcoord - mario_xcoord) < LEP_WIDTH ) {
		if (Enemy::enemy_ycoord - (mario_ycoord + LEP_HEIGHT) < 21  && Enemy::enemy_ycoord - (mario_ycoord + LEP_HEIGHT) > -5) {	
			return false;
		}
		else if (Enemy::enemy_ycoord - mario_ycoord >= 0) {
			if (Enemy::enemy_ycoord - (mario_ycoord + LEP_HEIGHT) <= -5  && Enemy::enemy_ycoord - (mario_ycoord + LEP_HEIGHT) >= -1*LEP_HEIGHT) {
			return true;
			}
		}
	}

return false;
}	

// Check if there is a collision and enemy beats mario
// This function overrides the one defined in the enemy class.
bool Goomba::check_up(int mario_xcoord, int mario_ycoord, int yVel) 
{
	if (!Enemy::alive) return false;
	if ( fabs(mario_xcoord - Enemy::enemy_xcoord) < Goomba_WIDTH && fabs(Enemy::enemy_xcoord - mario_xcoord) < LEP_WIDTH ) {
		if (Enemy::enemy_ycoord - (mario_ycoord + LEP_HEIGHT) < 21  && Enemy::enemy_ycoord - (mario_ycoord + LEP_HEIGHT) > -5) {	
			Enemy::falling = true;
			Enemy::alive = false;
			return true;
		}
	}
return false;
}

// set the x coordinate
void Goomba::setxCoord(int x) 
{
	Enemy::enemy_xcoord = x;
}

// render enemy on the screen
void Goomba::render_enemy(int gMapLocation_x)
{
	// Check bricks function call determines direction
	check_bricks();
	if (r_frame > 16) r_frame = 0;
	if (l_frame > 16) l_frame = 0;

	// Enemy falls of screen if mario beats it
	if (Enemy::falling) {
		if (Enemy::enemy_ycoord + 10 + Goomba_HEIGHT < SCREEN_HEIGHT) 
			Enemy::enemy_ycoord += 10;
		else
			return;
	}
	
	// render enemy to the right
	if (Enemy::render_right) {
		Enemy::enemy_xcoord += Enemy::right_step;
		SDL_Rect* currentEnemy = &Enemy::gRightEnemy[r_frame % 4];
		Enemy::gRightEnemyTexture.render(Enemy::enemy_xcoord - gMapLocation_x, Enemy::enemy_ycoord, currentEnemy);
		++r_frame;
	}
	
	// Render to the left
	else {
		Enemy::enemy_xcoord -= Enemy::left_step;
		SDL_Rect* currentEnemy = &Enemy::gLeftEnemy[l_frame % 4];
		Enemy::gLeftEnemyTexture.render( Enemy::enemy_xcoord - gMapLocation_x, Enemy::enemy_ycoord, currentEnemy);
		++l_frame;
	}
}	
