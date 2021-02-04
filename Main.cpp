#include "Engine/Core/CoreEngine.h"
#include "Game/GameSample.h"

int main(int argc, char* argv[]) {
    CoreEngine::SetGameInstance(new GameSample);

    if (!CoreEngine::GetInstance()->OnCreate("Game258 Engine", 800, 600)) {
        return 0;
    }
    CoreEngine::GetInstance()->Run();
    return 0;
}