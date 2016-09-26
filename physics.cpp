#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "geometry.h"
#include "physics.h"

static const double F = 0.1;

Universe::Universe() {
	Ball centerBall;
	centerBall.location = {0.0, 0.0};
	centerBall.velocity = {0.0, 0.0};
	centerBall.radius = 0.5;

	Ball orbitingBall;
	orbitingBall.location = {0.0, 0.75};
	double r = 0.75;
	orbitingBall.velocity = {2.0 * M_PI * r * F, 0.0};
	orbitingBall.radius = 0.05;
	orbitingBall.massInKg = 1.0;

	centerBall.massInKg = 4.0 * pow(M_PI, 2.0) * pow(r, 3.0) * pow(F, 2.0) / G;

	balls.push_back(centerBall);
	balls.push_back(orbitingBall);
}

void Universe::update(double timeIncrement) {
	for (Ball& ball : balls) {
		ball.location += ball.velocity * timeIncrement;
	}
	for(Ball& ball0 : balls) {
		for(Ball& ball1 : balls) {
			ball0.velocity += calculateGravity(ball0, ball1) * timeIncrement;
		}
	}
}

Vector calculateGravity(const Ball& ball0, const Ball& ball1) {
	double d2 = pow(ball0.location.distanceTo(ball1.location), 2.0);
	if(d2 == 0.0) {
		return Vector{0.0, 0.0};
	}

	double magnitude = G * ball1.massInKg / d2;

	return (ball1.location - ball0.location).unitVector() * magnitude;
}
