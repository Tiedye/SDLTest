#pragma once
#include "PhysicalRect.h"
#include <vector>

class PhysicsEngine {
public:
	PhysicsEngine();
	~PhysicsEngine();
	
	void addObject( PhysicalRect &object );

	void step( float t ) const;

	glm::vec2 g;

private:

	struct Bound {
		enum Type {
			BEGIN,
			END
		};

		Bound( Type type, PhysicalRect& object ) : value {type == BEGIN ? object.min.x : object.max.x}, type {type}, object {object} {}

		float value;
		Type type;
		std::reference_wrapper<PhysicalRect> object;

		bool operator<(const Bound& other) const {
			return value < other.value;
		}
	};

	glm::vec2 size_;

	std::vector<std::reference_wrapper<PhysicalRect>> objects_;

	std::vector<Bound> bounds_;
};
