#include <cmath>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif
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

void multiplyOrthoMatrix(double left, double right, double bottom, double top, double front, double back) {
	glOrtho(left, right, bottom, top, front, back);
	checkForOpenglError();
}

Point getPointFromPixel(int32_t x, int32_t y) {
	double windowZ;
	glReadPixels(x, (int) y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &windowZ);

	GLdouble modelViewMatrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix); // errors?

	GLdouble projectionMatrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);

	GLint viewPort[4];
	glGetIntegerv(GL_VIEWPORT, viewPort); // errors?

	Point result;
	double dummyObjZ = 0.0;

	if (gluUnProject(x, viewPort[3] - y, windowZ, modelViewMatrix, projectionMatrix, viewPort, &result.x, &result.y, &dummyObjZ) == GLU_TRUE) {
		return result;
	} else {
		throw Exception("");
	}
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
