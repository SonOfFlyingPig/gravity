#include <chrono>
#include <vector>

#include "sofp_opengl.h"
#include "sofp_sdl.h"

#include "physics.h"

using namespace std;
using namespace std::chrono;

using namespace sofp::opengl;
using namespace sofp::sdl;

class SecondsTimer {

private:
	high_resolution_clock::time_point lastTickTimePoint = high_resolution_clock::now();

public:
	double click() {
		high_resolution_clock::time_point thisTickTimePoint = high_resolution_clock::now();
		duration<double> elapsedTime = thisTickTimePoint - lastTickTimePoint;
		double result = elapsedTime.count();
		lastTickTimePoint = thisTickTimePoint;

		return result;
	}

};

class SdlOpenglGravityRenderer {

private:
	OpenglWindow window = OpenglWindow("Gravity", 400, 400, 2, 1);
	GlContext glContext = window.createGlContext();

public:
	SdlOpenglGravityRenderer() {
		if (!setGlSwapInterval(GlSwapInterval::V_SYNC)) {
			cerr << "Warning: could not set vsync" << endl;
		}
		resetProjectionMatrix();
		multiplyOrthoMatrix(-200.0, 200.0, -200.0, 200.0, -1.0, 1.0);
		resetModelviewMatrix();
		setClearColor(BLACK);
	}

	void render(Universe& universe) {
		clearColorBuffer();
		for (Ball ball : universe.balls) {
			drawCircle(ball.location.x, ball.location.y, ball.radius);
		}
		window.swapGlWindow();
	}

	Point getPointFromPixel(int32_t x, int32_t y) {
		return sofp::opengl::getPointFromPixel(x, y);
	}

};

class GravitySdlApp: App {

public:
	void run(int argc, char* argv[]) override;
};

void GravitySdlApp::run(int argc, char* argv[]) {
	if (argc != 1) {
		throw invalid_argument("argc");
	}
	if (argv == NULL) {
		throw invalid_argument("argv");
	}

	SecondsTimer timer;
//	Universe universe = getSimpleOrbitUniverse();
	Universe universe;
	SdlOpenglGravityRenderer renderer;
	for (;;) {
		PossibleEvent possibleEvent = pollForEvent();
		if (possibleEvent.exists) {
			Event event = possibleEvent.event;
			if (event.type == Event::Type::QUIT) {
				break;
			} else if (event.type == Event::Type::MOUSE_BUTTON_DOWN) {
				Ball newBall;
				newBall.location = renderer.getPointFromPixel(event.mouseButtonEventData.x, event.mouseButtonEventData.y);
				newBall.velocity = {0.0, 0.0};
				newBall.radius = 10.0;
				newBall.massInKg = 1000.0 * 1000.0 * 1000.0 * 1000.0 * 1000.0;
				universe.balls.push_back(newBall);
			}
		}
		universe.update(timer.click());
		renderer.render(universe);
	}
}

DEFINE_SOFP_SDL_APP__MAIN(GravitySdlApp)
