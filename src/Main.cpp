// Windows 10 Build Instructions
// ASM.js:
//   emcc Main.cpp -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="[""png""]" --preload-file assets -o build/release.html
// WASM:
//   emcc Main.cpp -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS="[""png""]" --preload-file assets -s WASM=1 -o build/release.html

#include <iostream>
#include <string>
#include <SDL.h>
//#undef main

#include <SDL_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif






/**
 * Loads the image located at 'fileName' and copies it to the
 * renderer 'renderer'
 */
int testImage(SDL_Renderer* renderer, const char* fileName)
{
	SDL_Surface *image = IMG_Load(fileName);
	if (!image)
	{
		printf("IMG_Load: %s\n", IMG_GetError());
		return 0;
	}
	int result = image->w;

	/**
	* position and size that you wish the image to be copied
	* to on the renderer:
	*/
	SDL_Rect dest = { 200, 100, 200, 200 };

	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, image);

	SDL_RenderCopy(renderer, tex, NULL, &dest);

	/**
	 * Now that the image data is in the renderer, we can free the memory
	 * used by the texture and the image surface
	 */
	SDL_DestroyTexture(tex);

	SDL_FreeSurface(image);

	return result;
}

//extern "C"
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

	int result = 0;

	/**
	 * Set up a white background
	 */
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	/**
	 * Load and copy the test image to the renderer
	 */
	result |= testImage(renderer, "assets/owl.png");

	/**
	 * Show what is in the renderer
	 */
	SDL_RenderPresent(renderer);

	printf("you should see an image.\n");
	std::string line;
	std::getline(std::cin, line);

	return 0;
}

