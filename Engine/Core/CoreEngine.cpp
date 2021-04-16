#include "CoreEngine.h"
#include "../Rendering/3D/GameObject.h"
#include "../Rendering/ShaderHandler.h"
#include "../Rendering/TextureHandler.h"
#include "../Rendering/SceneGraph.h"
#include "../Rendering/MaterialHandler.h"

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
    ShaderHandler::GetInstance()->CreateProgram("ColourShader", "Engine/Shaders/ColourShader_Vert.glsl", "Engine/Shaders/ColourShader_Frag.glsl");
    ShaderHandler::GetInstance()->CreateProgram("BasicShader", "Engine/Shaders/Shader_Vert.glsl", "Engine/Shaders/Shader_Frag.glsl");
    TextureHandler::GetInstance()->CreateTexture("Checkerboard", "Resources/CheckerboardTexture.png");
    MouseEventListener::RegisterEngine();
    SDL_WarpMouseInWindow(window->GetWindow(), _width / 2, _height / 2);
    timer = new Timer();
    timer->Start();
    Debug::LogInfo("Engine created successfully", __FILE__, __LINE__);
    return isRunning = true;
}

void CoreEngine::Run() {
    while (isRunning) {
        timer->Update();
        EventListener::HandleEvents();
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

void CoreEngine::MousePressed(const int button, const glm::ivec2 position) {}

void CoreEngine::MouseReleased(const int button, const glm::ivec2 position) {
    CollisionHandler::GetInstance()->Update(position, button);
}

void CoreEngine::MouseMoved(const glm::ivec2 position) {
    if (currentCamera) {
        currentCamera->MouseMovement(MouseEventListener::GetMouseOffset());
    }
}

void CoreEngine::MouseScrolled(const int amount) {
    if (currentCamera) {
        currentCamera->MouseScroll(amount);
    }
}

void CoreEngine::Update(const float dTime) {
    //std::cout << "D Time: " << dTime << std::endl;
    if (gameInstance) {
        gameInstance->Update(dTime);
    }
}

void CoreEngine::Render() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (gameInstance) {
        gameInstance->Render();
    }
    SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy() {
    CollisionHandler::GetInstance()->OnDestroy();
    SceneGraph::GetInstance()->OnDestroy();
    MaterialHandler::GetInstance()->OnDestroy();
    TextureHandler::GetInstance()->OnDestroy();
    ShaderHandler::GetInstance()->OnDestroy();
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

glm::vec2 CoreEngine::GetWindowSize() const
{
    return glm::vec2(window->GetWidth(), window->GetHeight());
}