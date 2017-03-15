#pragma once
#include <vector>
#include "PhysicalRect.h"
#include <SDL_render.h>

class RenderEngine {
public:
	RenderEngine();
	RenderEngine( int width, int height );
	~RenderEngine();

	void addObject( PhysicalRect &object );

	void draw() const;
private:
	SDL_Renderer *renderer {nullptr};
	SDL_Window *window {nullptr};

	const int width;
	const int height;

	std::vector<std::reference_wrapper<PhysicalRect>> objects;
};

