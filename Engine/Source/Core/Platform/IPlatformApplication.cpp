
#include "IPlatformApplication.h"
#include "spdlog/spdlog.h"
#include "ApplicationStaticRegister.h"

bool darc::IPlatformApplication::init_window() {
    auto init_sdl = []() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            spdlog::error("Failed to initialize SDL: %s\n", SDL_GetError());
            return false;
        }
        return true;
    };

    auto create_window = [this](){
        // TODO: Dynamic check graphic api support
        int windowFlag = SDL_WindowFlags::SDL_WINDOW_VULKAN
                | SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI;

        auto window = SDL_CreateWindow(name_.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 760, windowFlag);

        if (!window) {
            spdlog::error("Failed to create window: {}\n", SDL_GetError());
            return false;
        }

        main_window_ = window;

        return true;
    };

    return init_sdl() && create_window();
}

std::shared_ptr<darc::IPlatformApplication> darc::IPlatformApplication::Get() {
    static std::shared_ptr<darc::IPlatformApplication> ptr_;

    if (nullptr == ptr_) {
        ptr_ = std::make_shared<darc::EngineCoreApplication>("dArCEngine");
    }

    return ptr_;
}

void darc::IPlatformApplication::start() {
    // try init sdl window
    if (!init_window()) {
        return;
    }

    SDL_SetMainReady();

    // try init engine
    engine_ = Engine(main_window_);

    // do tick
    while (is_running) {
        tick();
        engine_->update(0); // TODO calc delta time
    }

    // do clean
    clean();
}

void darc::IPlatformApplication::tick() {
    handle_window_input();
    SDL_Delay(17);
}

void darc::IPlatformApplication::handle_window_input() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                is_running = false;
                break;
            default:
                break;
        }
    }
}

void darc::IPlatformApplication::clean() {
    spdlog::info("Clearing...");
}
