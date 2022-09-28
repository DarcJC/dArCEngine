
#include "Engine.h"

Engine::Engine(SDL_Window* window) {
    rhi_ = new VulkanDynamicRHI(window);
    rhi_->PostInit();
    rhi_->Init();
}

void Engine::update(u32 deltaTime) {
    rhi_->Tick(deltaTime);
}
