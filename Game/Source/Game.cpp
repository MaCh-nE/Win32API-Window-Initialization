#include<Game.h>
#include<Windows.h>
#include <Window/Window.h>
#include<iostream>
/* Unique ptrs */
#include <memory>

Game::Game() {
	/* Allocating a new window (new equivalent for std::unique_ptr) */
	window_ = std::make_unique<Window>();
	/* Allocating a new OGL engine */
	engine_ = std::make_unique<Grfx_engine>();
}

Game::~Game() {
	/* No need, they are unique ptrs ! */
	// delete window_;
	// delete engine_;
}

void Game::run() {
	while (running && window_->WindowStatus()) {
		MSG msg = {};
		/* Message Queue Pulling into msg */
		if (GetMessage(&msg, NULL, 0, 0)) {
			if (msg.message == WM_QUIT) {
				running = false;
				continue;
			}
			else {
				/* Mesage translation to Macro */
				TranslateMessage(&msg);
				/* Message transfer to WinProc() */
				DispatchMessage(&msg);
			}
		}
		Sleep(1);
	}
}

void Game::quit() {
	running = false;
}
