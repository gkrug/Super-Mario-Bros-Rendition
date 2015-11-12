// enemy is the base class and contains
// several virtual functions such that
// they can be overriden by child classes
// to perform the specific operations unique
// to the particular enemy

#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class Enemy: public Global_Constants {
	public:
		// Default Constructor
		Enemy();
		
		// Non-Default Constructor
		Enemy(int, int, int, int);

		// Deconstructor
		~Enemy();

		// Load media for the enemy
		virtual bool load_enemy(string, string);

		// Check if the enemy beats mario
		virtual bool mario_die(int, int);

		// Check if mario beats enemy
		virtual bool check_up(int, int, int);

		// set x coordinate of the enemy
		virtual void setxCoord(int);

		// render the enemy on the screen
		virtual void render_enemy(int);

		// check if enemy is on brick
		void check_bricks();

		// Compose object texture for right enemy
      LTexture gRightEnemyTexture;

		// Sprite sheet for enemy right
		SDL_Rect gRightEnemy[5];

		// Compose object texture for left enemy
		LTexture gLeftEnemyTexture;
		
		// Sprite sheet for enemy left
		SDL_Rect gLeftEnemy[5];

	// Data protected so it can be inherited
	protected:

		// Declare protected Data
		int Enemy_WIDTH;		
		int Enemy_HEIGHT;
		int enemy_xcoord;
		int enemy_ycoord;
		Map level1;
		Map level2;
		Map * mapPtr;
		int level;
		int right_step;
		int left_step;
		int enemy_yoriginal;
		int enemy_xoriginal;
		bool render_right = true;
		bool falling = false;
		bool alive = true;
};

#endif

Enemy::Enemy() {}

// Call Enemy constructor and inherit from Enemy
Enemy::Enemy(int xf, int yf, int num_map, int enemyID)
	: level1(gfile1), level2(gfile2)
{
	// Get Enemy Id so Generic Enemy dimensions 
	// can be specified
	if (enemyID == 2) {
		Enemy_HEIGHT = Goomba_HEIGHT;
		Enemy_WIDTH = Goomba_WIDTH;
	}
	else {
		Enemy_HEIGHT = FootballPlayer_HEIGHT;
		Enemy_WIDTH = FootballPlayer_WIDTH;
	}
	// initialize private data
	right_step = 2;
	left_step = 2;
	level = num_map;
	enemy_xcoord = BRICK_WIDTH * xf;
	enemy_ycoord = SCREEN_HEIGHT - yf*BRICK_HEIGHT - Enemy_HEIGHT;
	enemy_xoriginal = enemy_xcoord;
	enemy_yoriginal = enemy_ycoord;
	if (level == 1)
		mapPtr = &level1;
	else
		mapPtr = &level2;
	check_bricks();
}

Enemy::~Enemy()
{}

// load the enemy sprite sheet
bool Enemy::load_enemy(string left, string right)
{
	bool success = true;
	//Load enemy sprite sheet texture going right
	if( !gRightEnemyTexture.loadFromFile( right, "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gRightEnemy[ 0 ].x = 0;
		gRightEnemy[ 0 ].y = 0;
		gRightEnemy[ 0 ].w =  49;
		gRightEnemy[ 0 ].h = 51;

		gRightEnemy[ 1 ].x =  49;
		gRightEnemy[ 1 ].y =  0;
		gRightEnemy[ 1 ].w =  49;
		gRightEnemy[ 1 ].h = 51;
		
		gRightEnemy[ 2 ].x = 98;
		gRightEnemy[ 2 ].y = 0;
		gRightEnemy[ 2 ].w =  49;
		gRightEnemy[ 2 ].h = 51;

		gRightEnemy[ 3 ].x = 147;
		gRightEnemy[ 3 ].y = 0;
		gRightEnemy[ 3 ].w = 47;
		gRightEnemy[ 3 ].h = 51;
	}
	
	if( !gLeftEnemyTexture.loadFromFile( left, "white" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else {
		//Set sprite clips
		gLeftEnemy[ 0 ].x = 0;
		gLeftEnemy[ 0 ].y = 0;
		gLeftEnemy[ 0 ].w =  47;
		gLeftEnemy[ 0 ].h = 50;

		gLeftEnemy[ 1 ].x =  47;
		gLeftEnemy[ 1 ].y =  0;
		gLeftEnemy[ 1 ].w =  47;
		gLeftEnemy[ 1 ].h = 50;
		
		gLeftEnemy[ 2 ].x = 94;
		gLeftEnemy[ 2 ].y = 0;
		gLeftEnemy[ 2 ].w =  47;
		gLeftEnemy[ 2 ].h = 50;

		gLeftEnemy[ 3 ].x = 141;
		gLeftEnemy[ 3 ].y = 0;
		gLeftEnemy[ 3 ].w = 45;
		gLeftEnemy[ 3 ].h = 50;
	}
	return success;
}

// Generic collision detection for enemy
bool Enemy::mario_die(int mario_xcoord, int mario_ycoord) 
{

if(!(enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord +LEP_HEIGHT) > enemy_ycoord && !((enemy_ycoord - mario_ycoord) < 3))){
					if(enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord +LEP_HEIGHT) > enemy_ycoord){
						cout<< "Mario has collided while facing right :DIES" <<endl;
						return true;
					}
				}
return false;
}	

// generic collision detection to see if enemy beats mario
// Should be overridden
bool Enemy::check_up(int mario_xcoord, int mario_ycoord, int yVel) 
{
	if (!alive) return false;
	if(enemy_xcoord - (mario_xcoord+LEP_WIDTH) < 0 && (enemy_xcoord+34) -(mario_xcoord +LEP_WIDTH) > -34 && (mario_ycoord + LEP_HEIGHT) > enemy_ycoord+10 && !((enemy_ycoord - mario_ycoord) < 3)){
				cout<< "attacked from top: kill"<<endl;    
					falling = true;
					alive = false;
					return true;
				}
return false;
}

// Set X coordinate of the enemy
void Enemy::setxCoord(int x) 
{
	enemy_xcoord = x;
}

//Virtual function should be overriddden to render enemy
void Enemy::render_enemy(int gMapLocation_x)
{/*
	check_bricks();
	if (right_frame > 16) right_frame = 0;
	if (left_frame > 16) left_frame = 0;
	if (falling) {
		if (enemy_ycoord + 10 + Enemy_HEIGHT < SCREEN_HEIGHT) 
			enemy_ycoord += 10;
		else
			return;
	}
	
	if (render_right) {
		enemy_xcoord += right_step;
		SDL_Rect* currentEnemy = &gRightEnemy[right_frame % 4];
		gRightEnemyTexture.render(enemy_xcoord - gMapLocation_x, enemy_ycoord, currentEnemy);
		++right_frame;
	}
	else {
		enemy_xcoord -= left_step;
		SDL_Rect* currentEnemy = &gLeftEnemy[left_frame % 4];
		gLeftEnemyTexture.render( enemy_xcoord - gMapLocation_x, enemy_ycoord, currentEnemy);
		++left_frame;
	}*/
}	

// Set bounds for enemy walk. if there is a brick right or
// left or not a brick underneath, turn the opposite way
void Enemy::check_bricks()
{
	// check if brick on enemy bottom right
	if (mapPtr->get_BrickLocation(enemy_xcoord + right_step + Enemy_WIDTH,enemy_ycoord + Enemy_HEIGHT) == 0) {
		render_right = false;
		return;
	}
	// Check if brick on enemy bottom left
	if (mapPtr->get_BrickLocation(enemy_xcoord - left_step,enemy_ycoord + Enemy_HEIGHT) == 0) {
		render_right = true;
		return;
	}
	// Check if brick on enemy right up
	if (mapPtr->get_BrickLocation(enemy_xcoord + right_step + Enemy_WIDTH,enemy_ycoord) == 1) {
		render_right = false;
		return;
	}	
	// Check if brick on enemy left up
	if (mapPtr->get_BrickLocation(enemy_xcoord - left_step,enemy_ycoord) == 1) {
		render_right = true;
		return;
	}
	// Check if brick on enemy right midlevel
	if (mapPtr->get_BrickLocation(enemy_xcoord + right_step + Enemy_WIDTH,enemy_ycoord + BRICK_HEIGHT) == 1) {
		render_right = false;
		return;
	}	
	// Check if brick on enemy left midlevel
	if (mapPtr->get_BrickLocation(enemy_xcoord - left_step,enemy_ycoord + BRICK_HEIGHT) == 1) {
		render_right = true;
		return;
	}
}
