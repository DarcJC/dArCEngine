#define SDL_MAIN_HANDLED
#include "spdlog/spdlog.h"
#include "Platform/IPlatformApplication.h"

int main(int argc, char* argv[]) {
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
