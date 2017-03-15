#include "PhysicalRect.h"
#include <array>
#include <algorithm>
#include <glm/mat2x2.hpp>

using namespace glm;

PhysicalRect::PhysicalRect() : PhysicalRect {{0, 0}, {10, 10}, 0, {0, 0}, 0} {}

PhysicalRect::PhysicalRect( const glm::vec2 & pos, const glm::vec2 & size, float r ) : PhysicalRect {pos, size, r, {0, 0}, 0} {}

PhysicalRect::PhysicalRect( const glm::vec2 & pos, const glm::vec2 & size, float r, const glm::vec2 & vel, float w ) : pos (pos), size (size), vel (vel), r {r}, w {w} {}

PhysicalRect::~PhysicalRect() {}

void PhysicalRect::updateAABB() {
	mat2x2 rotm {cos( r ), -sin( r ), sin( r ), cos( r )};
	std::array<vec2, 4> points {0.5f * size * rotm + pos, -0.5f * size * rotm + pos, vec2{0.5f * size.x, -0.5f * size.y} * rotm + pos, vec2{-0.5f * size.x, 0.5f * size.y} * rotm + pos};
	min = {FLT_MAX, FLT_MAX};
	max = {FLT_MIN, FLT_MIN};
	for (auto point : points) {
		min.x = std::min( point.x, min.x );
		max.x = std::max( point.x, max.x );
		min.y = std::min( point.y, min.y );
		max.y = std::max( point.y, max.y );
	}
}
