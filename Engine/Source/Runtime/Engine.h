#pragma once
#include "Core/Core.h"
#include <optional>
#include <SDL.h>

class Engine final {

private:
    DynamicRHI* rhi_;

public:

    Engine(SDL_Window* window);

    void update(u32 deltaTime);

};
