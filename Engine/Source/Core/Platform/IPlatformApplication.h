#pragma once
#include <string>
#include <memory>
#include "SDL.h"
#include "Core/RHIWrapper/Vulkan/VulkanDynamicRHI.h"

namespace darc {
    class IPlatformApplication {
    private:
        std::string name_;
        SDL_Window* main_window_ = nullptr;
        bool is_running = true;
        VulkanDynamicRHI rhi;

    public:
        explicit IPlatformApplication(std::string&& name) : name_(name) {};

        virtual void start();

        virtual void tick();

        virtual void clean();

        virtual bool init_window();

        virtual void handle_window_input();

        static std::shared_ptr<IPlatformApplication> Get();
    };
}
