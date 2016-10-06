#include <cmath>

#include "geometry.h"

Point operator+(const Point& point, const Vector& vector) {
	return Point { point.x + vector.x, point.y + vector.y };
}

Vector operator-(const Point& point0, const Point& point1) {
	return Vector { point0.x - point1.x, point0.y - point1.y };
}

Point& Point::operator+=(const Vector& vector) {
	x += vector.x;
	y += vector.y;

	return *this;
}

double Point::distanceTo(const Point& point) const {
	return (point - *this).magnitude();
}

Vector operator+(const Vector& vector0, const Vector& vector1) {
	return Vector { vector0.x + vector1.x, vector0.y + vector1.y };
}

Vector operator-(const Vector& vector0, const Vector& vector1) {
	return Vector { vector0.x - vector1.x, vector0.y - vector1.y };
}

Vector operator*(double d, const Vector& vector) {
	return Vector { d * vector.x, d * vector.y };
}

Vector operator/(const Vector& vector, const double d) {
	return Vector { vector.x / d, vector.y / d };
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
