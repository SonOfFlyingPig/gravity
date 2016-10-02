#include <cmath>

#include "geometry.h"

Point Point::operator+(const Vector& vector) const {
	Point result = *this;
	result.x += vector.x;
	result.y += vector.y;

	return result;
}

Point& Point::operator+=(const Vector& vector) {
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector Point::operator-(const Point& point) const {
	return Vector { x - point.x, y - point.y };
}

double Point::distanceTo(const Point& point) const {
	return (point - *this).magnitude();
}

Vector Vector::operator*(double d) const {
	return Vector { d * x, d * y };
}

Vector& Vector::operator+=(const Vector& vector) {
	x += vector.x;
	y += vector.y;

	return *this;
}

Vector& Vector::operator-=(const Vector& vector) {
	x -= vector.x;
	y -= vector.y;

	return *this;
}

double Vector::magnitude() const {
	return sqrt(x * x + y * y);
}

Vector Vector::unitVector() const {
	double magnitude = this->magnitude();

	return {x / magnitude, y / magnitude};
}
