#include <Window/Window.h>
#include<iostream>
#include<Windows.h>


/* WinProc function :  wndw hndl - mssgcode -   min-Maxed  - width/height(2 be bit-shifted) */
/* : Handles queued messages */
LRESULT CALLBACK WinProc(HWND wnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		/* Winodow Destruction */
		case WM_DESTROY: {
			PostQuitMessage(0);
			/* NULLify the flag */
			Window* window = (Window *) GetWindowLongPtr(wnd, GWLP_USERDATA);
			window->WindowClose();
			return NULL;
		}
		/* Window resize (equiv. to repaint) */
		case WM_PAINT: {
			PAINTSTRUCT ps = {};
			/* Handle (Device Context) to the window */
			HDC hdc = BeginPaint(wnd, &ps);

			/*  this handle <-- this rect <--  this color       */
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+2));
			EndPaint(wnd, &ps);

			return NULL;
		}
		default:
			return DefWindowProc(wnd, uMsg, wParam, lParam);
		}
	return NULL;
}


/* Constructor */
Window::Window() {
	const wchar_t CLSS_NAME[] = L"CLSS_WINDOW";

	WNDCLASS wc = {};			// List init., all NULL 

	wc.lpszClassName = CLSS_NAME;
	wc.lpfnWndProc = WinProc;

	RegisterClass(&wc);			// Class OS Registration 

	// <----------------------------------------------------------------------->

	wnd = CreateWindowExW(
		1,						// Op. Style
		CLSS_NAME,				// Window Class name
		L"Pi-Scape 1.0.0",		// Window Title
		WS_OVERLAPPEDWINDOW,	// Macro Style
		CW_USEDEFAULT,			// Top	
		CW_USEDEFAULT,			// Left
		CW_USEDEFAULT,			// Width
		CW_USEDEFAULT,			// Heigth	
		NULL,					// Parent wndw
		NULL,					// Menu	
		NULL,				    // Handle
		NULL					// -
	);

	/* Store the window instance via its handle, for the destroy mssg */
	SetWindowLongPtrW(wnd, GWLP_USERDATA, (LONG_PTR)this);

	/* As the name suggests :) */
	ShowWindow(wnd,SW_SHOW);
	
	/* Sends WM_PAINT to the message queue when requested */
	UpdateWindow(wnd);
}

/* Deconstructor */
Window::~Window() {
	DestroyWindow(wnd);
}

/* Window status flag */
bool Window::WindowStatus() {
	return w_flag;
}

/* Window closing method */
void Window::WindowClose() {
	w_flag = false;
}


