#include "PhysicsEngine.h"
#include <SDL.h>
#include <algorithm>
#include <functional>

PhysicsEngine::PhysicsEngine() {}


PhysicsEngine::~PhysicsEngine() {}


void PhysicsEngine::addObject(PhysicalRect& object) {
	objects_.push_back( object );
	auto original_end {bounds_.end()};
	bounds_.push_back( {Bound::BEGIN, object} );
	bounds_.push_back( {Bound::END, object} );
	std::inplace_merge( bounds_.begin(), bounds_.end()-2, bounds_.end() );
}

template<class Iter>
static void insertion_sort( Iter first, Iter last ) {
	if(first == last) return;
	auto back_iter {first};
	auto cur_iter {++first};
	while(cur_iter != last) {
		back_iter = cur_iter;
		while(back_iter > first && *back_iter < *(back_iter - 1)) {
			//std::iter_swap( back_iter, back_iter - 1 );
			--back_iter;
		}
		++cur_iter;
	}
}

void PhysicsEngine::step(float t) const {
	insertion_sort( bounds_.begin(), bounds_.end() );
	for(PhysicalRect &object:objects_) {
		object.updateAABB();
		if(!object.immovable) {
			object.pos += object.vel*t;
			object.r += object.w*t;
			SDL_Log( "r: %f", object.r );
			object.vel += g*t;
		}
	}
}
