#include <cmath>
#include <string>

#include <Windows.h>
#include <GL/glu.h>

#include "sofp_opengl.h"

using namespace std;

namespace sofp {

namespace opengl {

void checkForOpenglError() {
	int error = glGetError();
	if (error != GL_NO_ERROR) {
		throw Exception(std::string((char*) gluErrorString(error)));
	}
}

void clearColorBuffer() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void drawCircle(double x, double y, double r) {
	glBegin(GL_TRIANGLE_FAN);
	for (int vertexNumber = 0; vertexNumber <= CIRCLE_VERTEX_COUNT; vertexNumber++) {
		double angleInRadians = vertexNumber * RADIANS_PER_VERTEX;
		glVertex2d(x + r * cos(angleInRadians), y + r * sin(angleInRadians));
	}
	glEnd();
}

void resetProjectionMatrix() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	checkForOpenglError();
}

void resetModelviewMatrix() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	checkForOpenglError();
}

void setClearColor(const Color& color) {
	glClearColor(color.red, color.green, color.blue, color.alpha);
	checkForOpenglError();
}

Exception::Exception(const string& message) :
		message(message) {
}

}

}
