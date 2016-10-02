#ifndef SOFP_SDL_H
#define SOFP_SDL_H

#include <iostream>
#include <memory>

namespace sofp {

namespace sdl {

enum struct GlSwapInterval {
	IMMEDIATE = 0, V_SYNC = 1
};

struct Exception;
struct Event;
struct IncorrectEventType;
struct MouseButtonEventData;
struct PossibleEvent;

class App;
class Window;
class GlContext;
class Renderer;

PossibleEvent pollForEvent();
bool setGlSwapInterval(GlSwapInterval interval);
void setGlVersion(const int majorVersion, const int minorVersion);
Event waitForEvent();

class App {

public:
	App();
	virtual ~App();
	virtual void run(int argc, char** argv) = 0;

};

struct MouseButtonEventData {

	int32_t x;
	int32_t y;

};

struct QuitEventData {
	uint32_t timeStamp;
};

struct Event {

public:
	enum struct Type {
		MOUSE_BUTTON_DOWN, QUIT, UNKNOWN
	};

	const Type type;
	const union {
		MouseButtonEventData mouseButtonEventData;
		QuitEventData quitEventData;
	};

	Event(Type type);
	Event(Type type, const MouseButtonEventData& mouseButtonEventData);
	Event(Type type, const QuitEventData& quitEventData);

};

struct Exception {
	const std::string message;

	Exception(const std::string& message);
};

struct IncorrectEventTypeException: Exception {
	IncorrectEventTypeException(const std::string& message);
};

struct PossibleEvent {

public:
	const bool exists;
	const Event event;

};

class Window {

protected:
	class Impl;
	std::shared_ptr<Impl> impl;

	Window(std::shared_ptr<Impl> impl);

public:
	Window(const std::string& title, const int width, const int height);
	GlContext createGlContext();
	Renderer createRenderer(const int index, const uint32_t flags);
	void swapGlWindow();
	friend class GlContext;
	friend class Renderer;

};

class OpenglWindow: public Window {

public:
	OpenglWindow(const std::string& title, const int width, const int height, const int glMajorVersion, const int glMinorVersion);

};

class GlContext {

private:
	class Impl;
	std::shared_ptr<Impl> impl;

	GlContext(std::shared_ptr<Impl> impl);
	friend class Window::Impl;

};

class Renderer {

private:
	class Impl;
	std::shared_ptr<Impl> impl;

	Renderer(std::shared_ptr<Impl> impl);

public:
	void setRenderDrawColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
	void clear();
	void present();
	friend class Window::Impl;

};

template<typename A>
int mainImpl(int argc, char** argv) {
	static_assert(std::is_base_of<App, A>::value, "A not derived from sdl::App");

	try {
		A().run(argc, argv);
	} catch (const Exception& exception) {
		std::cerr << "sdl::Exception: " << exception.message << std::endl;
		return EXIT_FAILURE;
	} catch (const std::exception& exception) {
		std::cerr << "Other exception: " << exception.what() << std::endl;
	}

	return EXIT_SUCCESS;
}

}

}

#define DEFINE_SOFP_SDL_APP__MAIN(A) int main(int argc, char** argv) { return sofp::sdl::mainImpl<A>(argc, argv); }

#endif
