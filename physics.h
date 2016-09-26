#ifndef SOFP_GRAVITY_PHYSICS_H
#define SOFP_GRAVITY_PHYSICS_H

#include "geometry.h"

static const double G = 6.67408E-11;

struct Ball;

class Universe;

struct Ball {
	Point location;
	Vector velocity;
	double radius;
	double massInKg;
};

class Universe {

//private:
//	std::chrono::high_resolution_clock::time_point lastTickTimePoint;

public:
	std::vector<Ball> balls;
	Universe();
//	void update();
	void update(double timeIncrement);

};

Vector calculateGravity(const Ball& ball0, const Ball& ball1);

#endif
