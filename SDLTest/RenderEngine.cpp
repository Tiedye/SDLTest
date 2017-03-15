#include "RenderEngine.h"
#include <iostream>
#include <SDL.h>
#include <array>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

RenderEngine::RenderEngine() : RenderEngine( 1280, 720 ) {}

RenderEngine::RenderEngine( int width, int height ) : width {width}, height {height} {
	if(SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer)) {
		std::cerr << "Error on SDL_CreateWindowAndRenderer" << std::endl;
		// TODO error
	} else {
		std::cout << "Window and Renderer created" << std::endl;
	}
}


RenderEngine::~RenderEngine() {
	SDL_Quit();
}

void RenderEngine::addObject( PhysicalRect & object ) {
	objects.push_back( object );
}

void RenderEngine::draw() const {
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );
	SDL_SetRenderDrawColor( renderer, 255, 0, 0, 200 );
	for(PhysicalRect &object:objects) {
		std::array<vec2, 5> points;
		mat2x2 rott {cos( object.r ), -sin( object.r ), sin( object.r ), cos( object.r )};
		points[0] = {object.size.x * 0.5f, object.size.y * 0.5f};
		points[1] = {-object.size.x * 0.5f, object.size.y * 0.5f};
		points[2] = {-object.size.x * 0.5f, -object.size.y * 0.5f};
		points[3] = {object.size.x * 0.5f, -object.size.y * 0.5f};
		for(auto i {0}; i < 4; ++i) points[i] = points[i] * rott + object.pos;
		points[4] = points[0];
		std::array<SDL_Point, 5> sdlPoints;
		for(auto i {0}; i < 5; ++i) sdlPoints[i] = {static_cast<int>(points[i].x), static_cast<int>(points[i].y)};
		SDL_RenderDrawLines( renderer, sdlPoints._Elems, sdlPoints.size() );
	}
	SDL_SetRenderDrawColor( renderer, 0, 255, 0, 128 );
	for(PhysicalRect &object : objects) {
		std::array<SDL_Point, 5> sdlPoints;
		sdlPoints[0] = {static_cast<int>(object.min.x), static_cast<int>(object.min.y)};
		sdlPoints[1] = {static_cast<int>(object.min.x), static_cast<int>(object.max.y)};
		sdlPoints[2] = {static_cast<int>(object.max.x), static_cast<int>(object.max.y)};
		sdlPoints[3] = {static_cast<int>(object.max.x), static_cast<int>(object.min.y)};
		sdlPoints[4] = sdlPoints[0];
		SDL_RenderDrawLines( renderer, sdlPoints._Elems, sdlPoints.size() );
	}
	SDL_RenderPresent( renderer );
}
