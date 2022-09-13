#pragma once
#include <string>
#include <memory>
#include "SDL.h"

namespace darc {
    class IPlatformApplication {
    private:
        std::string name_;
        SDL_Window* main_window_ = nullptr;
        bool is_running = true;

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
