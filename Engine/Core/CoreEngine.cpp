#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine() : window(nullptr), isRunning(false), timer(nullptr), fps(60), gameInstance(nullptr), currentScene(0) {}

CoreEngine::~CoreEngine() {}

bool CoreEngine::OnCreate(std::string _name, int _width, int _height) {
    Debug::OnCreate();
	window = new Window();
    if (!window->OnCreate(_name, _width, _height)) {
        Debug::LogFatal("Window failed to create", __FILE__, __LINE__);
        OnDestroy();
        return isRunning = false;
    }
    if (gameInstance) {
        if (!gameInstance->OnCreate()) {
            Debug::LogFatal("Game Instance failed to create", __FILE__, __LINE__);
            OnDestroy();
            return isRunning = false;
        }
    }
    timer = new Timer();
    timer->Start();
    Debug::LogInfo("Engine created successfully", __FILE__, __LINE__);
    return isRunning = true;
}

void CoreEngine::Run() {
    while (isRunning) {
        timer->Update();
        HandleEvents();
        Update(timer->GetDeltaTime());
        Render();
        SDL_Delay(timer->GetSleepTime(fps));
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

void CoreEngine::SetGameInstance(GameInterface* _gameInstance) {
    GetInstance()->gameInstance = _gameInstance;
}

void CoreEngine::HandleEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        }
    }
}

void CoreEngine::Update(const float dTime) {
    //std::cout << "D Time: " << dTime << std::endl;
    if (gameInstance) {
        gameInstance->Update(dTime);
    }
}

void CoreEngine::Render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (gameInstance) {
        gameInstance->Render();
    }
    SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy() {
    if (gameInstance) {
        delete gameInstance;
        gameInstance = nullptr;
    }
    if (timer) {
        delete timer;
        timer = nullptr;
    }
    if (window) {
        delete window;
        window = nullptr;
    }
    SDL_Quit();
    exit(0);
}

void CoreEngine::Exit() {
    isRunning = false;
}