/*
 * main.c
 *
 *  Created on: Dec 5, 2018
 *      Author: hamed
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>


void moveCircle(SDL_Keycode key, double * movingCircle_x, double * movingCircle_y) {
	switch(key) {
		case SDLK_UP :
			*movingCircle_y -= 5;
			break;
		case SDLK_DOWN :
			*movingCircle_y += 5;
			break;
		case SDLK_RIGHT :
			*movingCircle_x += 5;
			break;
		case SDLK_LEFT :
			*movingCircle_x -= 5;
			break;
	}
}

bool hasEatenFood(double movingCircle_x, double movingCircle_y, double food_x, double food_y, double radius, double rx, double ry) {
	double distance = sqrt(pow((movingCircle_x - food_x), 2) + pow((movingCircle_y - food_y), 2));
	if(distance < radius + rx) {
		return true;
	} else {
		return false;
	}
}

void changeFoodLocation(double * food_x, double * food_y) {
	int random_x = rand() % 600 + 100;
	int random_y = rand() % 400 + 100;
	*food_x = random_x;
	*food_y = random_y;
}


int main() {
	double movingCircle_x = 100;
	double movingCircle_y = 100;
	double movingCircle_radius = 20;

	double food_x = 300;
	double food_y = 300;
	double food_rx = 15;
	double food_ry = 10;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window * window = SDL_CreateWindow("workshop", 20, 20, 800, 600, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Event event;
    while(1) {
    	if(SDL_PollEvent(&event)) {
    		if(event.type == SDL_QUIT)
    			return 0;
    		if(event.type == SDL_KEYDOWN) {
    			moveCircle(event.key.keysym.sym , &movingCircle_x, &movingCircle_y);
    		}
    	}
    	SDL_SetRenderDrawColor(renderer, 120, 0, 80, 255);

    	SDL_RenderClear(renderer);

    	if(hasEatenFood(movingCircle_x, movingCircle_y, food_x, food_y, movingCircle_radius, food_rx, food_ry)) {
    	   	printf("eat!!!\n");
    	   	movingCircle_radius += 2;
    	   	changeFoodLocation(&food_x, &food_y);
    	}

    	filledCircleRGBA(renderer, movingCircle_x, movingCircle_y, movingCircle_radius, 0, 100, 100, 255);
    	filledEllipseRGBA(renderer, food_x, food_y, food_rx, food_ry, 20, 150, 0, 255);


    	SDL_RenderPresent(renderer);
    }
	printf("hello world!!");
	return 0;
}
