#ifndef SOFP_GRAVITY_GEOMETRY_H
#define SOFP_GRAVITY_GEOMETRY_H

struct Point;
struct Vector;

Point operator+(const Point& point, const Vector& vector);
Vector operator-(const Point& point0, const Point& point1);

struct Point {
	double x;
	double y;

	Point& operator+=(const Vector& vector);

	double distanceTo(const Point& point) const;
};

Vector operator+(const Vector& vector0, const Vector& vector1);
Vector operator-(const Vector& vector0, const Vector& vector1);
Vector operator*(const double d, const Vector& vector);
Vector operator/(const Vector& vector, const double d);

struct Vector {
	double x;
	double y;

	Vector& operator+=(const Vector& vector);
	Vector& operator-=(const Vector& vector);

	double magnitude() const;
	Vector unitVector() const;
};

#endif
