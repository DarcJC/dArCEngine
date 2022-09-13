#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "spdlog/spdlog.h"
#include "Platform/IPlatformApplication.h"

int main() {
    spdlog::info(R"(
    ###     ##                ####   #######                      ##
     ##    ####              ##  ##   ##   #
     ##   ##  ##   ######   ##        ## #    #####     ### ##   ###     #####     ####
  #####   ##  ##    ##  ##  ##        ####    ##  ##   ##  ##     ##     ##  ##   ##  ##
 ##  ##   ######    ##      ##        ## #    ##  ##   ##  ##     ##     ##  ##   ######
 ##  ##   ##  ##    ##       ##  ##   ##   #  ##  ##    #####     ##     ##  ##   ##
  ######  ##  ##   ####       ####   #######  ##  ##       ##    ####    ##  ##    #####
                                                       #####
    )");

    auto app = darc::IPlatformApplication::Get();

    app->start();

    return 0;
}
