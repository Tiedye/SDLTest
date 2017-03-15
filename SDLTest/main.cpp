#include <SDL.h>
#include "RenderEngine.h"
#include "PhysicsEngine.h"

const int windowWidth{1280};
const int windowHeight{720};


int main(int argc, char* argv[]) 
{
	RenderEngine render_engine {windowWidth, windowHeight};
	PhysicsEngine physics_engine;
	physics_engine.g = {0, 1000};

	PhysicalRect rect {{100, 100}, {100, 100}, 1.0f, {1000, -200}, 1};
	PhysicalRect ground {{windowWidth / 2, windowHeight - 100}, {windowWidth - 100, 50}, 0.0f};
	ground.immovable = true;
	render_engine.addObject( rect );
	render_engine.addObject( ground );
	physics_engine.addObject( rect );
	physics_engine.addObject( ground );

	bool running {true};
	SDL_Event event;

	auto timerFreq {SDL_GetPerformanceFrequency()};
	auto last {SDL_GetPerformanceCounter()};

	while (running) {
		if (SDL_PollEvent( &event )) {
			switch(event.type) {
			case SDL_QUIT:
				running = false;
				break;
			default: break;
			}
		}
		auto current {SDL_GetPerformanceCounter()};
		float delta {static_cast<float>(current - last) / timerFreq};
		last = current;
		physics_engine.step( delta/10 );
		render_engine.draw();
	}

	return 0;
}
