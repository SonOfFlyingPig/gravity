#ifndef SOFP_GRAVITY_PHYSICS_H
#define SOFP_GRAVITY_PHYSICS_H

#include "geometry.h"

static const double G = 6.67408E-11;

struct Ball;

class Universe;

Universe getSimpleOrbitUniverse();

struct Ball {
	Point location;
	Vector velocity;
	double radius;
	double massInKg;
};

class Universe {

public:
	std::vector<Ball> balls;
	void update(double timeIncrement);

};

Vector calculateGravity(const Ball& ball0, const Ball& ball1, const double softeningLength = 10.0);

#endif
