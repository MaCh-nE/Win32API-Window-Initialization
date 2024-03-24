#ifndef GAME_H
#define GAME_H
#include <Window/Window.h>
#include <Grfx/Grfx_engine.h>
#include<iostream>

class Game {
	public :
		Game();
		~Game();
		void run();
		void quit();

	protected :
		/* Game Flag */
		bool running = true;
		/* Window Ptr */
		std::unique_ptr<Window> window_ = nullptr;
		/* Engine Ptr */
		std::unique_ptr<Grfx_engine> engine_ = nullptr;
};

#endif
