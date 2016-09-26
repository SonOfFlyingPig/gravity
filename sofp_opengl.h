#ifndef SOFP_OPENGL_H
#define SOFP_OPENGL_H

#include <string>

namespace sofp {

namespace opengl {

static const int CIRCLE_VERTEX_COUNT = 60;
static const double PI = 3.14159;
static const double RADIANS_PER_VERTEX = 2.0 * PI / CIRCLE_VERTEX_COUNT;

struct Color;
struct Exception;

void clearColorBuffer();
void drawCircle(double x, double y, double r);
void resetProjectionMatrix();
void resetModelviewMatrix();
void setClearColor(const Color& color);

struct Color {
	float red;
	float green;
	float blue;
	float alpha;
};
static const Color BLACK = {0.0f, 0.0f, 0.0f, 1.0f};

struct Exception {
	const std::string message;

	Exception(const std::string& message);
};

}

}

#endif
