#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false) {}

CoreEngine::~CoreEngine() {}

bool CoreEngine::OnCreate(std::string _name, int _width, int _height) {
	window = new Window();
    if (!window->OnCreate(_name, _width, _height)) {
        std::cout << "Error: Window failed to create" << std::endl;
        delete window;
        window = nullptr;
        OnDestroy();
        return isRunning = false;
    }
    return isRunning = true;
}

void CoreEngine::Run() {
    while (isRunning) {
        Update(0.016f);
        Render();
    }
    OnDestroy();
}

CoreEngine* CoreEngine::GetInstance()
{
    if (engineInstance.get() == nullptr) {
        engineInstance.reset(new CoreEngine);
    }
    return engineInstance.get();
}

void CoreEngine::HandleEvents() {}

void CoreEngine::Update(const float dTime) {}

void CoreEngine::Render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy() {
    delete window;
    window = nullptr;
    SDL_Quit();
    exit(0);
}