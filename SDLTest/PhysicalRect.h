#pragma once
#include <glm/vec2.hpp>

class PhysicalRect {
public:
	PhysicalRect();
	PhysicalRect( const glm::vec2 &pos, const glm::vec2 &size, float r );
	PhysicalRect( const glm::vec2 &pos, const glm::vec2 &size, float r, const glm::vec2 &vel, float w );
	~PhysicalRect();

	void updateAABB();

	glm::vec2 pos, size, vel;
	float r, w;

	bool immovable {false};

	glm::vec2 min, max;
};

