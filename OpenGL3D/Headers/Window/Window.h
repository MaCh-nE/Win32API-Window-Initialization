#ifndef WINDOW_H
#define WINDOW_H
#include<Windows.h>

class Window {
	public :
		/* Constr - Destr */
		Window();
		~Window();
		/* Methods to close & check the window flag (private attribute) */
		void WindowClose();
		bool WindowStatus();
	private :
		/* The returned handle */
		HWND wnd;
		bool w_flag = true;
};

#endif

