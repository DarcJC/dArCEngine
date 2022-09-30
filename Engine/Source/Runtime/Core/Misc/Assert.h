#pragma once

#include <csignal>
#include "spdlog/spdlog.h"
#include "debug-trap/debug-trap.h"

template<typename T, bool fatal>
struct AssertWrapper {
    typedef T type;
};

template<typename... Args>
TRYINLINE void fatal(spdlog::format_string_t<Args...> fmt, Args &&... args) {
    spdlog::critical(fmt, std::forward<Args>(args)...);
    psnip_trap();
    exit(SIGABRT);
}

template<typename... Args>
TRYINLINE void ensure(bool exp, spdlog::format_string_t<Args...> fmt, Args &&... args) {
    [[unlikely]]
    if (!exp) {
        fatal(fmt, std::forward<Args>(args)...);
    }
}
