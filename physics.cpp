#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <vector>

#include "geometry.h"
#include "physics.h"

static const double F = 0.1;

Universe getSimpleOrbitUniverse() {
	Universe result;

	Ball centerBall;
	centerBall.location = {0.0, 0.0};
	centerBall.velocity = {0.0, 0.0};
	centerBall.radius = 100.0;

	Ball orbitingBall;
	orbitingBall.location = {0.0, 150.0};
	double r = orbitingBall.location.y;
	orbitingBall.velocity = {2.0 * M_PI * r * F, 0.0};
	orbitingBall.radius = 10.0;
	orbitingBall.massInKg = 1.0;

	centerBall.massInKg = 4.0 * pow(M_PI, 2.0) * pow(r, 3.0) * pow(F, 2.0) / G;

	result.balls.push_back(centerBall);
	result.balls.push_back(orbitingBall);

	return result;
}

void updateLocations(Universe* universe, double timeIncrement) {
	for (Ball& ball : universe->balls) {
		ball.location += ball.velocity * timeIncrement;
	}
}

void updateVelocities(Universe* universe, double timeIncrement) {
	for (auto iterator1 = universe->balls.begin(); iterator1 != universe->balls.end(); iterator1++) {
		for (auto iterator2 = iterator1 + 1; iterator2 != universe->balls.end(); iterator2++) {
			Vector velocityChange = calculateGravity(*iterator1, *iterator2) * timeIncrement;
			iterator1->velocity += velocityChange;
			iterator2->velocity -= velocityChange;
		}
	}
}

void Universe::update(double timeIncrement) {
	updateLocations(this, timeIncrement);
	updateVelocities(this, timeIncrement);
//	updateLocations(this, timeIncrement);
}

Vector calculateGravity(const Ball& ball0, const Ball& ball1) {
	double d2 = pow(ball0.location.distanceTo(ball1.location), 2.0);
	if (d2 == 0.0) {
		return Vector { 0.0, 0.0 };
	}

	double magnitude = G * ball1.massInKg / d2;

	return (ball1.location - ball0.location).unitVector() * magnitude;
}
