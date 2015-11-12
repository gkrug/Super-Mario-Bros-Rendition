#ifndef GLOBAL_CONSTANTS
#define GLOBAL_CONSTANTS

class Global_Constants {

		public:
			//Screen dimension constants
			const int SCREEN_WIDTH = 500;
			const int SCREEN_HEIGHT = 480;
			const int X = 0;
			const int Y = 1;
			const int BRICK_HEIGHT = 32;
			const int BRICK_WIDTH = 32;
			const int LEP_HEIGHT = 45;
			const int LEP_WIDTH = 27;
			const int FOOTBALL_WIDTH = 30;
			const int FOOTBALL_HEIGHT = 51;
			const int FootballPlayer_WIDTH = 49;
			const int FootballPlayer_HEIGHT = 51;
			const int Goomba_WIDTH = 35;
			const int Goomba_HEIGHT = 37;
			const string gfile1 = "bricks";
			const string gfile2 = "bricks2";

			//Key press surfaces constants
			enum KeyPressSurfaces
			{
    			KEY_PRESS_SURFACE_DEFAULT,
   			KEY_PRESS_SURFACE_UP,
    			KEY_PRESS_SURFACE_DOWN,
   			KEY_PRESS_SURFACE_LEFT,
    			KEY_PRESS_SURFACE_RIGHT,
   			KEY_PRESS_SURFACE_TOTAL
			};
};

#endif
