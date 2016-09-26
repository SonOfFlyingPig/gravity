#ifndef SOFP_GRAVITY_GEOMETRY_H
#define SOFP_GRAVITY_GEOMETRY_H

struct Point;
struct Vector;

struct Point {
	double x;
	double y;

	Point operator+(const Vector& vector) const;
	Point& operator+=(const Vector& vector);
	Vector operator-(const Point& point) const;

	double distanceTo(const Point& point) const;
};

struct Vector {
	double x;
	double y;

	Vector operator*(double d) const;
	Vector& operator+=(const Vector& vector);

	double magnitude() const;
	Vector unitVector() const;
};

#endif
