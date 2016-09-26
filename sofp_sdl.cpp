#include <SDL2/SDL.h>

#include "sofp_sdl.h"

using namespace std;

namespace sofp {

namespace sdl {

Event getEvent(SDL_Event sdlEvent) {
	Event result;

	switch (sdlEvent.type) {

	case SDL_QUIT:
		result.type = Event::Type::QUIT;
		break;

	default:
		result.type = Event::Type::UNKNOWN;
	}

	return result;
}

PossibleEvent pollForEvent() {
	SDL_Event sdlEvent;
	bool exists = SDL_PollEvent(&sdlEvent) != 0;
	PossibleEvent result = { exists, getEvent(sdlEvent) };

	return result;
}

bool setGlSwapInterval(GlSwapInterval interval) {
	return SDL_GL_SetSwapInterval(static_cast<int>(interval)) == 0;
}

void setGlVersion(const int majorVersion, const int minorVersion) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
}

Event waitForEvent() {
	SDL_Event sdlEvent;
	if (!SDL_WaitEvent(&sdlEvent)) {
		throw Exception(string("Error while waiting for SDL event: ") + SDL_GetError());
	}

	return getEvent(sdlEvent);
}

App::App() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw Exception(string("Error while initializing SDL: ") + SDL_GetError());
	}
}

App::~App() {
	SDL_Quit();
}

Exception::Exception(const string& message) :
		message(message) {
}

class GlContext::Impl {

private:
	SDL_GLContext wrappedGlContext;

	Impl(SDL_GLContext wrappedGlContext);
	friend class GlContext;
	friend class Window::Impl;

public:
	~Impl();

};

GlContext::Impl::Impl(SDL_GLContext wrappedGlContext) :
		wrappedGlContext(wrappedGlContext) {
}

GlContext::Impl::~Impl() {
	SDL_GL_DeleteContext(wrappedGlContext);
}

GlContext::GlContext(shared_ptr<GlContext::Impl> impl) :
		impl(impl) {

}

class Renderer::Impl {

private:
	SDL_Renderer* wrappedRenderer;

	Impl(SDL_Renderer* wrappedRenderer);

public:
	~Impl();
	void setRenderDrawColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a);
	void clear();
	void present();
	friend class Renderer;
	friend class Window::Impl;
};

Renderer::Impl::Impl(SDL_Renderer* wrappedRenderer) :
		wrappedRenderer(wrappedRenderer) {
}

Renderer::Impl::~Impl() {
	SDL_DestroyRenderer(wrappedRenderer);
}

void Renderer::Impl::setRenderDrawColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
	if (SDL_SetRenderDrawColor(wrappedRenderer, r, g, b, a) != 0) {
		throw Exception(string("Error while setting renderer draw color: ") + SDL_GetError());
	}
}

void Renderer::Impl::clear() {
	if (SDL_SetRenderDrawColor(wrappedRenderer, 0x00, 0x00, 0x00, 0xFF) != 0) {
		throw Exception(string("Error while clearing renderer: ") + SDL_GetError());
	}
}

void Renderer::Impl::present() {
	SDL_RenderPresent(wrappedRenderer);
}

Renderer::Renderer(shared_ptr<Renderer::Impl> impl) :
		impl(impl) {

}

void Renderer::setRenderDrawColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
	impl->setRenderDrawColor(r, g, b, a);
}

void Renderer::clear() {
	impl->clear();
}

void Renderer::present() {
	impl->present();
}

class Window::Impl {

private:
	SDL_Window* wrappedWindow;

public:
	Impl(SDL_Window* wrappedWindow);
	Impl(const std::string& title, const int width, const int height, const uint32_t flags);
	~Impl();
	GlContext createGlContext();
	Renderer createRenderer(const int index, const uint32_t flags);
	void swapGlWindow();

};

Window::Impl::Impl(SDL_Window* wrappedWindow) :
		wrappedWindow(wrappedWindow) {
	if (wrappedWindow == NULL) {
		throw Exception(string("Error while creating window: ") + SDL_GetError());
	}
}

Window::Impl::Impl(const std::string& title, const int width, const int height, const uint32_t flags) :
		Impl(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags)) {
}

Window::Impl::~Impl() {
	SDL_DestroyWindow(wrappedWindow);
}

GlContext Window::Impl::createGlContext() {
	SDL_GLContext wrappedGlContext = SDL_GL_CreateContext(wrappedWindow);
	if (wrappedGlContext == NULL) {
		throw Exception(string("Error while creating OpenGL context: ") + SDL_GetError());
	}

	return GlContext(shared_ptr<GlContext::Impl>(new GlContext::Impl(wrappedGlContext)));
}

Renderer Window::Impl::createRenderer(const int index, const uint32_t flags) {
	SDL_Renderer* wrappedRenderer = SDL_CreateRenderer(wrappedWindow, index, flags);
	if (wrappedRenderer == NULL) {
		throw Exception(string("Error while creating renderer: ") + SDL_GetError());
	}

	return Renderer(shared_ptr<Renderer::Impl>(new Renderer::Impl(wrappedRenderer)));
}

void Window::Impl::swapGlWindow() {
	SDL_GL_SwapWindow(wrappedWindow);
}

Window::Window(shared_ptr<Impl> impl) :
		impl(impl) {
}

Window::Window(const std::string& title, const int width, const int height) :
		Window(shared_ptr<Impl>(new Impl(title, width, height, SDL_WINDOW_SHOWN))) {
}

GlContext Window::createGlContext() {
	return impl->createGlContext();
}

Renderer Window::createRenderer(const int index, const uint32_t flags) {
	return impl->createRenderer(index, flags);
}

void Window::swapGlWindow() {
	impl->swapGlWindow();
}

SDL_Window* initOpenglSdlWindow(const std::string& title, const int width, const int height, const int glMajorVersion, const int glMinorVersion) {
	setGlVersion(glMajorVersion, glMinorVersion);

	return SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
}

OpenglWindow::OpenglWindow(const std::string& title, const int width, const int height, const int glMajorVersion, const int glMinorVersion) :
		Window(shared_ptr<Impl>(new Impl(initOpenglSdlWindow(title, width, height, glMajorVersion, glMinorVersion)))) {
}

}

}
