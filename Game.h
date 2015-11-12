//Game Class which stores the big play function 
//In this class we implement most of the image loading and rendering
//We also handle the events based on key input
//We also instantiate the enemies in this class
//We also do the level transitions in this class
//We also free the resources


#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "LTexture.h"
#include "Map.h"
#include "Global_Constants.h"
#include "FootballPlayer.h"
#include "Goomba.h"

using namespace std;

class Game : public Global_Constants {
	public:
		// constructor
		Game();

		// Deconstructor
		~Game();

		//Starts up SDL and creates window
		bool init();

		//Loads media
		bool loadMedia();

		// end of level transition
		int isPotCollide(int, int, int, int);
	
		// Game main while loop
		void play();

		//Frees media and shuts down SDL
		void close();

		//The window we'll be rendering to
		SDL_Window* gWindow;

		//Walking animation right
		int WALKING_ANIMATION_FRAMES;
		SDL_Rect * gRightSprite;
		LTexture gRightSpriteTexture;

		//Walking animation left
		SDL_Rect * gLeftSprite;
		LTexture gLeftSpriteTexture;

		// Map rendering
		SDL_Rect gMapLocation;
		LTexture gMap;
		
		//Shamrock Rendering
		SDL_Rect gShamrockLocation;
		LTexture gShamrock;

		// Brick Rendering
		Map level_one;
		Map level_two;
		Map * levelPtr;

		//Pot of Gold Rendering
		SDL_Rect gGoldLocation;
		LTexture gGold;

		//Level 2 Transition
		SDL_Rect gtransition_level2;
		LTexture gtransl2;

		//Render Lives
		SDL_Rect gThreeLivesLocation;
		LTexture gThreeLives;

		SDL_Rect gTwoLivesLocation;
		LTexture gTwoLives;

		SDL_Rect gOneLifeLocation;
		LTexture gOneLife;

		//Start Screen Rendering
		SDL_Rect gStartScreen3Location;
		LTexture gStartScreen3Texture;

		SDL_Rect gStartScreen2Location;
		LTexture gStartScreen2Texture;

		SDL_Rect gStartScreen1Location;
		LTexture gStartScreen1Texture;

		SDL_Rect gStartScreenGoLocation;
		LTexture gStartScreenGoTexture;

		//You Win
		SDL_Rect youWinLocation;
		LTexture youWinTexture;

		//You Lose: Game Over
		SDL_Rect gameOverLocation;
		LTexture gameOverTexture;
};

#endif

Game::Game()
	: level_one(gfile1), level_two(gfile2)
{
		//The window we'll be rendering to
		SDL_Window* gWindow = NULL;

		//Walking animation right
		Game::WALKING_ANIMATION_FRAMES = 5;
		gRightSprite = new SDL_Rect[ WALKING_ANIMATION_FRAMES ];
		LTexture gRightSpriteTexture;

		//Walking animation left
		gLeftSprite = new SDL_Rect[ WALKING_ANIMATION_FRAMES ];
		LTexture gLeftSpriteTexture;

		// Map rendering
		SDL_Rect gMapLocation;
		LTexture gMap;

		// Brick Rendering
		levelPtr = &level_one;

		//Pot of Gold Rendering
		SDL_Rect gGoldLocation;
		LTexture gGold;

		//Shamrock Rendering
		SDL_Rect gShamrockLocation;
		LTexture gShamrock;

		//Level 2 Transition
		SDL_Rect gtransition_level2;
		LTexture gtransl2;
}

Game::~Game()
{
	delete [] gRightSprite;
	delete [] gLeftSprite;
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Super Lep's World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture going right
	if( !gRightSpriteTexture.loadFromFile( "Media/right_lep.png", "white" ) )
	{
		printf( "Failed to load right walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gRightSprite[ 0 ].x = 0;
		gRightSprite[ 0 ].y = 0;
		gRightSprite[ 0 ].w =  27;
		gRightSprite[ 0 ].h = 43;

		gRightSprite[ 1 ].x =  27;
		gRightSprite[ 1 ].y =  0;
		gRightSprite[ 1 ].w =  27;
		gRightSprite[ 1 ].h = 43;
		
		gRightSprite[ 2 ].x = 54;
		gRightSprite[ 2 ].y = 0;
		gRightSprite[ 2 ].w =  27;
		gRightSprite[ 2 ].h = 43;

		gRightSprite[ 3 ].x = 81;
		gRightSprite[ 3 ].y = 0;
		gRightSprite[ 3 ].w = 27;
		gRightSprite[ 3 ].h = 43;

		gRightSprite[ 4 ].x = 108;
		gRightSprite[ 4 ].y = 0;
		gRightSprite[ 4 ].w = 27;
		gRightSprite[ 4 ].h = 43;
	}

	//Load sprite sheet texture going left
	if( !gLeftSpriteTexture.loadFromFile( "Media/left_lep.png", "white" ) )
	{
		printf( "Failed to load left walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		gLeftSprite[ 0 ].x = 108;
		gLeftSprite[ 0 ].y = 0;
		gLeftSprite[ 0 ].w =  27;
		gLeftSprite[ 0 ].h = 43;

		gLeftSprite[ 1 ].x =  81;
		gLeftSprite[ 1 ].y =  0;
		gLeftSprite[ 1 ].w =  27;
		gLeftSprite[ 1 ].h = 43;
		
		gLeftSprite[ 2 ].x = 54;
		gLeftSprite[ 2 ].y = 0;
		gLeftSprite[ 2 ].w =  27;
		gLeftSprite[ 2 ].h = 43;

		gLeftSprite[ 3 ].x = 27;
		gLeftSprite[ 3 ].y = 0;
		gLeftSprite[ 3 ].w = 27;
		gLeftSprite[ 3 ].h = 43;

		gLeftSprite[ 4 ].x = 27;
		gLeftSprite[ 4 ].y = 0;
		gLeftSprite[ 4 ].w = 27;
		gLeftSprite[ 4 ].h = 43;
	}
	//Load sprite sheet texture
	string backgroundName = "Media/background.png";
	if( !gMap.loadFromFile( backgroundName.c_str(), "white" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	else
	{
		gMapLocation.x = 0;	
		gMapLocation.y = 0;
		gMapLocation.w = SCREEN_WIDTH;
		gMapLocation.h = SCREEN_HEIGHT;
	}	
	//Load sprite sheet texture
	if( !gGold.loadFromFile( "Media/gold.png", "white" ) )
	{
		printf( "Failed to load gold texture!\n" );
		success = false;
	}
	else
	{
		gGoldLocation.x = 0;	
		gGoldLocation.y = 0;
		gGoldLocation.w = 200;
		gGoldLocation.h = 200;
	}

	if( !gShamrock.loadFromFile( "Media/shamrock.png", "white" ) ) 
	{
		printf( "Failed to load shamrock texture!\n" );
		success = false;
	}
	else
	{
		gShamrockLocation.x = 0;	
		gShamrockLocation.y = 0;
		gShamrockLocation.w = 48;
		gShamrockLocation.h = 48;
	}

	//Load Life Sheets
	if( !gThreeLives.loadFromFile( "Media/threelives.png", "green" ) )
	{
		printf( "Failed to load three lives texture!\n" );
		success = false;
	}
	else
	{
		gThreeLivesLocation.x = 0;	
		gThreeLivesLocation.y = 0;
		gThreeLivesLocation.w = 204;
		gThreeLivesLocation.h = 68;
	}	

	if( !gTwoLives.loadFromFile( "Media/twolives.png", "green" ) )
	{
		printf( "Failed to load two lives texture!\n" );
		success = false;
	}
	else
	{
		gTwoLivesLocation.x = 0;	
		gTwoLivesLocation.y = 0;
		gTwoLivesLocation.w = 204;
		gTwoLivesLocation.h = 68;
	}	

	if( !gOneLife.loadFromFile( "Media/onelife.png", "green" ) )
	{
		printf( "Failed to load one life texture!\n" );
		success = false;
	}
	else
	{
		gOneLifeLocation.x = 0;	
		gOneLifeLocation.y = 0;
		gOneLifeLocation.w = 204;
		gOneLifeLocation.h = 68;
	}
	
	//Load start Screens
	if( !gStartScreen3Texture.loadFromFile( "Media/startScreen3.png", "white" ) )
	{
		printf( "Failed to load start screen 3 texture!\n" );
		success = false;
	}
	else
	{
		gStartScreen3Location.x = 0;	
		gStartScreen3Location.y = 0;
		gStartScreen3Location.w = 500;
		gStartScreen3Location.h = 500;
	}

	if( !gStartScreen2Texture.loadFromFile( "Media/startScreen2.png", "white" ) )
	{
		printf( "Failed to load start screen 2 texture!\n" );
		success = false;
	}
	else
	{
		gStartScreen2Location.x = 0;	
		gStartScreen2Location.y = 0;
		gStartScreen2Location.w = 500;
		gStartScreen2Location.h = 500;
	}

	if( !gStartScreen1Texture.loadFromFile( "Media/startScreen1.png", "white" ) )
	{
		printf( "Failed to load start screen 1 texture!\n" );
		success = false;
	}
	else
	{
		gStartScreen1Location.x = 0;	
		gStartScreen1Location.y = 0;
		gStartScreen1Location.w = 500;
		gStartScreen1Location.h = 500;
	}

	if( !gStartScreenGoTexture.loadFromFile( "Media/startScreenGO.png", "white" ) )
	{
		printf( "Failed to load start screen go texture!\n" );
		success = false;
	}
	else
	{
		gStartScreenGoLocation.x = 0;	
		gStartScreenGoLocation.y = 0;
		gStartScreenGoLocation.w = 500;
		gStartScreenGoLocation.h = 500;
	}
	//Load transition
	if( !gtransl2.loadFromFile( "Media/level2screen.png", "green" ) )
	{
		printf( "Failed to load level 2 texture!\n" );
		success = false;
	}
	else
	{
		gtransition_level2.x = 0;	
		gtransition_level2.y = 0;
		gtransition_level2.w = 500;
		gtransition_level2.h = 500;
	}

	//You Win Screen
	if( !youWinTexture.loadFromFile( "Media/YouWin.png", "white" ) )
	{
		printf( "Failed to load you win texture!\n" );
		success = false;
	}
	else
	{
		youWinLocation.x = 80;	
		youWinLocation.y = 0;
		youWinLocation.w = 500;
		youWinLocation.h = 500;
	}

	//You Lose:Game Over
	if( !gameOverTexture.loadFromFile( "Media/gameOver.png", "white" ) )
	{
		printf( "Failed to load game over texture!\n" );
		success = false;
	}
	else
	{
		gameOverLocation.x = 0;	
		gameOverLocation.y = 0;
		gameOverLocation.w = 500;
		gameOverLocation.h = 500;
	}
	return success;
}

int Game::isPotCollide(int potLocX, int spriteX, int potLocY, int spriteY)
{
	if( spriteX - potLocX >= 1500 && spriteX - potLocX <= 1580 && spriteY >= 369) //check if coordinates match pot
		return 1;
	else
		return 0;
}

void Game::play()
{
	levelPtr->get_coordinates();
	int render_mario_yloc = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT); 
	int render_mario_xloc = SCREEN_WIDTH/2;
	int mario_xcoord = SCREEN_WIDTH/2;
	int mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
	bool jumping = false; //check if jumping
	bool mario_down = false;
	int jump_height = 0;
	int max_jump_height = 150;
	int mario_yVel= 0;
	int didShamrockCollide = 0; //check if coin has been collected
	int life_count = 3; //count lives remaining
	int num_players = 4;
	vector<Enemy *> map1Players(num_players); //store football player enemies
	vector<Enemy *> map2Players(num_players); //store goombas
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//create instances of enemies on map 1
		FootballPlayer player1(10,2,1);
		Goomba player2(29,8,1);
		FootballPlayer player3(25,6,1);
		Goomba player4(39,4,1);

		//create instances of enemies on map 2
		Goomba player1a(37,1,2);
		FootballPlayer player2a(17,4,2);
		FootballPlayer player3a(25,6,2);
		Goomba player4a(39,4,2);

		map1Players[0] = &player1;
		map1Players[1] = &player2;
		map1Players[2] = &player3;
		map1Players[3] = &player4;
	
		map2Players[0] = &player1a;
		map2Players[1] = &player2a;
		map2Players[2] = &player3a;
		map2Players[3] = &player4a;
		if (!levelPtr->load_bricks() )
		{
			printf("failed to load bricks map\n");
		}
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame_right = 0;
			int frame_left = 0;
			bool mario_right = true;

			//Load the Start Screens
			//***************************************************************
			SDL_Rect* startScreen3 = &gStartScreen3Location;
			gStartScreen3Texture.render( 0, 0, startScreen3 );
			SDL_RenderPresent( gRenderer ); //updates the screen
			usleep(500000);			

			SDL_Rect* startScreen2 = &gStartScreen2Location;
			gStartScreen2Texture.render( 0, 0, startScreen2 );
			SDL_RenderPresent( gRenderer );
			usleep(500000);

			SDL_Rect* startScreen1 = &gStartScreen1Location;
			gStartScreen1Texture.render( 0, 0, startScreen1 );
			SDL_RenderPresent( gRenderer );
			usleep(500000);

			SDL_Rect* startScreenGo = &gStartScreenGoLocation;
			gStartScreenGoTexture.render( 0, 0, startScreenGo );
			SDL_RenderPresent( gRenderer );
			usleep(500000);
			//***************************************************************
 			
			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
				
				//Different events based on key input pressed
            			const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

				//Up arrow key
				if( currentKeyStates[ SDL_SCANCODE_UP ] )
				{	
					if(levelPtr->isBrick_down(mario_xcoord, mario_ycoord, mario_yVel)){
						if (!jumping)
						{
  							jumping = true;
  							mario_yVel = 0;
						}
					}
					
				}
				//Left arrow key
				else if( currentKeyStates[ SDL_SCANCODE_LEFT ])
				{
					if ( gMapLocation.x > 2  && !levelPtr->isBrick_left(mario_xcoord, mario_ycoord) ) {
							frame_left++;
							gMapLocation.x -= 5;	
							mario_xcoord -= 5;
							mario_right = false;
					}
				}
				//Right arrow key
				else if( currentKeyStates[ SDL_SCANCODE_RIGHT ])
				{
					if ( gMapLocation.x <  2000 - 500 && !levelPtr->isBrick_right(mario_xcoord, mario_ycoord, mario_yVel) ) {
							frame_right++;
							gMapLocation.x += 5;		
							mario_xcoord += 5;
							mario_right = true;
					}
					
				}
				
				//jumping for mario
				if (jumping == true)
				{
					if (!levelPtr->isBrick_up(mario_xcoord, mario_ycoord, mario_yVel)) {
							mario_yVel -= 6;
					mario_ycoord = mario_ycoord + mario_yVel;
					}
					else {
						int brick_space_up = levelPtr->space_brick_up(mario_xcoord, mario_ycoord, 0);
						mario_yVel = -1*brick_space_up;
						mario_ycoord = mario_ycoord + mario_yVel - 20;
						jumping = false;
					}
					if (mario_yVel <= -60)
					{
						mario_yVel = 0;
						jumping = false;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render current Map Frame
				SDL_Rect* currentMap = &gMapLocation;
				gMap.render( 0, 0, currentMap );
	
				// Render Bricks on map
				levelPtr->render_Bricks(gMapLocation.x);
				
				//Render pot of Gold
				SDL_Rect* potOfGold = &gGoldLocation;
				gGold.render(1670- gMapLocation.x, 330, potOfGold);
				isPotCollide(1670- gMapLocation.x, mario_xcoord, 330, mario_ycoord + 27);

				if (!levelPtr->isBrick_down(mario_xcoord, mario_ycoord, mario_yVel)) {
					int brick_space_down = levelPtr->space_brick_down(mario_xcoord, mario_ycoord);
					if (brick_space_down > 20)
						mario_ycoord += 20;
					else
						mario_ycoord += brick_space_down;
				}

				//Setting up level one
				if (levelPtr == &level_one) {
					for (int j = 0; j < num_players; j++) {
						if (map1Players[j]->check_up(mario_xcoord, mario_ycoord, mario_yVel) ){
							 mario_ycoord -= 85;
						}
						//respawn to starting position
						if(map1Players[j]->mario_die(mario_xcoord, mario_ycoord) ) { 
							
								gMapLocation.x = 0;
								mario_xcoord = SCREEN_WIDTH/2;
								mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
								mario_yVel = 0;
								life_count--;
							
						}
						map1Players[j]->render_enemy(gMapLocation.x);
					}
				}

				//Setting up level two
				else {
					for (int j = 0; j < num_players; j++) {
						if (map2Players[j]->check_up(mario_xcoord, mario_ycoord, mario_yVel) ){
							mario_ycoord -= 85;
						}
						//respawn to starting position
						if(map2Players[j]->mario_die(mario_xcoord, mario_ycoord) ) {
							
								gMapLocation.x = 0;
								mario_xcoord = SCREEN_WIDTH/2;
								mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
								mario_yVel = 0;
								life_count--;
						}
						map2Players[j]->render_enemy(gMapLocation.x);
					}
				}

				if (mario_right) {
					SDL_Rect* currentClip = &gRightSprite[ frame_right % 5 ];
					gRightSpriteTexture.render( render_mario_xloc, mario_ycoord, currentClip );
				}
				else {
					SDL_Rect* currentClipLeft = &gLeftSprite[ frame_left % 5 ];
					gLeftSpriteTexture.render( render_mario_xloc, mario_ycoord, currentClipLeft );
				}
			

				//Render shamrock
				if (life_count < 3) {
				if(!(mario_xcoord > 1205 && mario_xcoord < 1250 && (mario_ycoord + 27) == 431) && didShamrockCollide == 0 ){
					SDL_Rect * shamrock = &gShamrockLocation;
					gShamrock.render(1228 - gMapLocation.x, 395, shamrock);
				} //render only if mario doesn't collide

				if(mario_xcoord > 1205 && mario_xcoord < 1250 && (mario_ycoord + 27) == 433 && didShamrockCollide == 0){
						didShamrockCollide = 1;
						life_count++;
				}
				}
	
				//Render lives
				//*******************************************************
				if(life_count ==3){
					SDL_Rect* life_count = &gThreeLivesLocation;
					gThreeLives.render(0, 0, life_count);
				}
				if(life_count ==2){
					SDL_Rect* life_count = &gTwoLivesLocation;
					gTwoLives.render(0,0, life_count);
				}
				if(life_count ==1){
					SDL_Rect* life_count = &gOneLifeLocation;
					gOneLife.render(0,0, life_count);
				}
				if(life_count ==0){
					SDL_Rect* gameOverScreen = &gameOverLocation;
					gameOverTexture.render(0, 0, gameOverScreen);
					SDL_RenderPresent( gRenderer );
					usleep(3000000);
					quit = true;
				}
				//*******************************************************

				//Update screen
				SDL_RenderPresent( gRenderer );

				//Cycle animation
				if( frame_right / 5 >= WALKING_ANIMATION_FRAMES )
				{
					frame_right = 0;
				}
				//Cycle animation
				if( frame_left / 5 >= WALKING_ANIMATION_FRAMES )
				{
					frame_left = 0;
				}

				// Transisiton to next level. NEED TO KNOW EXACT POINT OF gMapLocation.x
				// ************************************************************
				if ( isPotCollide(1670- gMapLocation.x, mario_xcoord, 330, mario_ycoord + 27)) {
					if (levelPtr == &level_one) {
						gMapLocation.x = 0;
						mario_xcoord = SCREEN_WIDTH/2;
						mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);
						levelPtr = &level_two;
						if (!levelPtr->load_bricks() ) quit = true;
					}
				//****************************************************************
					// YOU WIN IF COLLIDE WITH SECOND POT
					else {
						SDL_Rect* youWinScreen = &youWinLocation;
						youWinTexture.render(0, 0, youWinScreen);
						SDL_RenderPresent( gRenderer );
						usleep(3000000);
						quit = true;
					}
	
					//Level two transition
					if (!quit) {
						//Render current Map Frame
						SDL_Rect* l2 = &gtransition_level2;
						gtransl2.render( 0, 0, l2 );
						//Update screen
						SDL_RenderPresent( gRenderer );
						do {
							SDL_PollEvent(&e);
						}
						while( e.type == SDL_KEYUP );
					}
				}
				
				//if mario falls of a ledge
				if (SCREEN_HEIGHT - mario_ycoord <= 46){
					if (levelPtr == &level_one) { //take care of level one
						gMapLocation.x = 0;
						mario_xcoord = SCREEN_WIDTH/2;
						mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);;
						life_count--;
					}
					if (levelPtr == &level_two) { //take care of level two
						gMapLocation.x = 0;
						mario_xcoord = SCREEN_WIDTH/2;
						mario_ycoord = 480-(2*BRICK_HEIGHT)-(LEP_HEIGHT);;
						life_count--;
					}
				}
			}
		}
	}
	
	//Free resources and close SDL
	close();

}

void Game::close()
{
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
