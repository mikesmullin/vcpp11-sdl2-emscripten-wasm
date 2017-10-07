//#include <stdio.h>
//#include <SDL.h>
//
//#ifdef __EMSCRIPTEN__
//#include <emscripten.h>
//#endif
//
//extern "C"
//int main(int argc, char** argv)
//{
//	printf("main()");
//
//	// Screen dimension constants
//	const int SCREEN_WIDTH = 640;
//	const int SCREEN_HEIGHT = 480;
//
//	// Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) < 0)
//	{
//		fprintf(stderr, "SDL_Init Fail: %s\n", SDL_GetError());
//	}
//	else
//	{
//		// Create window
//		const SDL_Window * const window = SDL_CreateWindow("Demo",
//			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
//			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		if (window == NULL)
//		{
//			fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
//		}
//		else
//		{
//			// Get window surface
//			const SDL_Surface * const screenSurface = SDL_GetWindowSurface(const_cast<SDL_Window *>(window));
//
//			// Fill the surface with color
//			SDL_FillRect(const_cast<SDL_Surface *>(screenSurface), NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0x00, 0xFF));
//
//			const SDL_Surface * const helloWorld = SDL_LoadBMP("assets/hello_world.bmp");
//			if (helloWorld == NULL) {
//				fprintf(stderr, "Failed to load image.");
//			}
//			else {
//				SDL_BlitSurface(const_cast<SDL_Surface *>(helloWorld), NULL, const_cast<SDL_Surface *>(screenSurface), NULL);
//			}
//
//			// Update the surface
//			SDL_UpdateWindowSurface(const_cast<SDL_Window *>(window));
//
//			// Wait two seconds
//			SDL_Delay(16000);
//
//			// Destroy window
//			SDL_DestroyWindow(const_cast<SDL_Window *>(window));
//		}
//
//	}
//
//	// Quit SDL subsystems
//	SDL_Quit();
//
//	return 0;
//}