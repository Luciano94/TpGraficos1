#include "SDL.h"
#include <stdio.h>
int main(int argc, char* argv[]) {
int xAxis = 0;								//posicion en X de la imagen
int yAxis = 0;								//posicion en Y de la imagen
int winWidth = 640;							//ancho de la ventana
int winHeight = 480;						//alto de la ventana
int imgWidth = 100;							//ancho de la imagen
int imgHeigth = 100;						//alto de la imagen
int speed = 5;								//velocidad en pixeles de la imagen
SDL_Window *window;							// Declare a pointer
	
	SDL_Init(SDL_INIT_VIDEO);				// Initialize SDL2
	
// Create an application window with the following settings:
	window = SDL_CreateWindow(
		"THIS IS A VENTANITA",				// window title
		SDL_WINDOWPOS_UNDEFINED,			// initial x position
		SDL_WINDOWPOS_UNDEFINED,			// initial y position
		winWidth,							// width, in pixels
		winHeight,							// height, in pixels
		0									// flags
	);
// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Surface * image = SDL_LoadBMP("image.bmp");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	int quit = 1;
	while (quit) {
		SDL_Event event;
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event)) {
			switch (event.type){
				case SDL_QUIT:
					quit = 0;
				break;
				case SDL_KEYDOWN:
					if (state[SDL_SCANCODE_RIGHT])
						if (xAxis + speed <= winWidth-imgWidth) xAxis+= speed;
					if (state[SDL_SCANCODE_LEFT])
						if (xAxis - speed >= 0) xAxis-=speed;
					if (state[SDL_SCANCODE_UP])
						if (yAxis - speed >= 0) yAxis-=speed;
					if (state[SDL_SCANCODE_DOWN])
						if (yAxis + speed <= winHeight-imgHeigth) yAxis+=speed;
				break;
			}
		}
		/* do some other stuff here -- draw your app, etc. */
		SDL_RenderClear(renderer);
		SDL_Rect dstrect = { xAxis, yAxis, imgWidth, imgHeigth};
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}