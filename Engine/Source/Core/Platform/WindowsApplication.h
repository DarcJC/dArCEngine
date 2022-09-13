#pragma once

#include "IPlatformApplication.h"

namespace darc {

    class WindowsApplication : public IPlatformApplication {

    public:
        explicit WindowsApplication(std::string&& name) : IPlatformApplication(std::move(name)) {}
    };
}

