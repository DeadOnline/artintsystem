#include "_inc\Application.h"

using namespace APP;

int __stdcall WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int nCmdShow) 
	{
	//APPLICATION, which use DirectX. Template can be used for OpenGL as well, but 
	//graphic libraries are chosen namely by current application. We can create any
	//window we want before using libraries for interfering with system
	//APPLICATION Game("Game", FULLSCREEN);

	APPLICATION Game("Domino 3D", WINDOWED, 1980, 1080, GRAPHCORE::DirectX9);
	//////We are able to create a couple of applications using
	return Game.Run();
	};