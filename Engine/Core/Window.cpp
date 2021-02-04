#include "Window.h"
#include "Debug.h"

Window::Window() {
	window = nullptr;
	glContext = nullptr;
}

Window::~Window() {
	OnDestroy();
}

bool Window::OnCreate(std::string _name, int _width, int _height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { 
		Debug::LogError("Failed to init SDL", __FILE__, __LINE__);
		return false; 
	}
	width = _width;
	height = _height;
	PreWindowConfig();
	window = SDL_CreateWindow(_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (window == NULL) { 
		Debug::LogError("Failed to create window", __FILE__, __LINE__);
		return false; 
	}
	glContext = SDL_GL_CreateContext(window);
	PostWindowConfig();
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Debug::LogError("Failed to initialise GLEW", __FILE__, __LINE__);
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	return true;
}

void Window::OnDestroy() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	window = nullptr;
}

void Window::PreWindowConfig() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::PostWindowConfig() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}