#include <Windows.h>
#include <Grfx/Grfx_engine.h>
/* Normal OpenGL fcts */
#include <glad/glad.h>
/* Definition of OpenGL windows fcts */
#include <glad/glad_wgl.h>



Grfx_engine::Grfx_engine() {
	/* Simulated window for OpenGL initialization */
	const wchar_t CLSS_NAME[] = L"OGL3D_CLSS_WINDOW";

	WNDCLASS wc = {};			// List init., all NULL 

	wc.lpszClassName = CLSS_NAME;
	wc.lpfnWndProc = DefWindowProc;
	wc.style = CS_OWNDC;

	RegisterClass(&wc);			// Class OS Registration 

	/* <--------------------------------------------------------------------------> */

	HWND sim_wnd = CreateWindowExW(
		1,						// Op. Style
		CLSS_NAME,				// Window Class name
		L"OpenGL3D",		    // Window Title
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

	/* Handle to the Device context of the window */
	HDC simwnd_dc = GetDC(sim_wnd);

	/* Description of the DC via PIXELFORMATDESCRIPTION struct */
	PIXELFORMATDESCRIPTOR pfd = {};

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;

	/* Pixel format handle */
	auto pf = ChoosePixelFormat(simwnd_dc,&pfd);
	/* Pixel format to HDC association */
	SetPixelFormat(simwnd_dc, pf, &pfd);

	/* <-----------------------------------------------------------------------> */
	/* Create OpenGL context */
	auto sim_dc = wglCreateContext(simwnd_dc);

	/* Set the context as current */
	wglMakeCurrent(simwnd_dc, sim_dc);

	/* Potential driver errors when loading OpenGL */
	if (!gladLoadWGL(simwnd_dc) || !gladLoadGL()) {
		throw "Grfx_engine ERROR <gladLoad (or gladLoadW) failed>.";
	}

	/* Reset the simulated window after OpenGL load */
	wglMakeCurrent(simwnd_dc, 0);
	wglDeleteContext(sim_dc);
	ReleaseDC(sim_wnd, simwnd_dc);
	DestroyWindow(sim_wnd);

}

Grfx_engine::~Grfx_engine() {

}
