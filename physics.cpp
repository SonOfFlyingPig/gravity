#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <cmath>
#include <iostream>
#include <vector>

#include "geometry.h"
#include "physics.h"

using namespace std;

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

vector<Vector> getAccelerationsDueToGravity(vector<Ball> balls) {
	vector<Vector> result(balls.size(), Vector { 0.0, 0.0 });
	for (size_t i = 0; i < balls.size(); i++) {
		for (size_t j = 0; j < balls.size(); j++) {
			if (i == j) {
				continue;
			}
			result[i] += calculateGravity(balls[i], balls[j]);
		}
	}

	return result;
}

void Universe::update(double timeIncrement) {
	for (Ball& ball : balls) {
		ball.location += timeIncrement * ball.velocity;
	}
	for (auto ballIterator0 = balls.begin(); ballIterator0 != balls.end(); ballIterator0++) {
		for (auto ballIterator1 = ballIterator0 + 1; ballIterator1 != balls.end(); ballIterator1++) {
			Vector gravity = timeIncrement * calculateGravity(*ballIterator0, *ballIterator1);
			ballIterator0->velocity += gravity / ballIterator0->massInKg;
			ballIterator1->velocity -= gravity / ballIterator1->massInKg;
		}
	}
//	vector<Vector> accelerations = getAccelerationsDueToGravity(balls);
//	for(size_t ballIndex = 0; ballIndex < balls.size(); ballIndex++) {
//		balls[ballIndex].location += timeIncrement * balls[ballIndex].velocity;
//		balls[ballIndex].velocity += timeIncrement * accelerations[ballIndex];
//	}

//	for (size_t i = 0; i < balls.size(); i++) {
//		balls[i].location += timeIncrement * (balls[i].velocity + timeIncrement * accelerations[i] / 2.0);
//	}
//	vector<Vector> newAccelerations = getAccelerationsDueToGravity(balls);
//	for (size_t i = 0; i < balls.size(); i++) {
//		balls[i].velocity += timeIncrement * (accelerations[i] + newAccelerations[i]) / 2.0;
//	}
	// http://gamedev.stackexchange.com/questions/15708/how-can-i-implement-gravity
}

Vector calculateGravity(const Ball& ball0, const Ball& ball1, const double softeningLength) {
	double d = ball0.location.distanceTo(ball1.location);
	if (d == 0.0) {
		return Vector { 0.0, 0.0 };
	}

//	double magnitude = G * ball0.massInKg * ball1.massInKg / (d * d);
	// http://www.scholarpedia.org/article/N-body_simulations_(gravitational)
	double magnitude = G * ball0.massInKg * ball1.massInKg * d / pow(d * d + softeningLength * softeningLength, 1.5);

	return magnitude * (ball1.location - ball0.location).unitVector();
}
