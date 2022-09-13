#define SDL_MAIN_HANDLED
#include "spdlog/spdlog.h"
#include "Platform/IPlatformApplication.h"
#include "Engine.h"

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

    spdlog::info("test: {}", test());

    auto app = darc::IPlatformApplication::Get();

    app->start();

    return 0;
}
