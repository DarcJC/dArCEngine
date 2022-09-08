#pragma once
#include "IPlatformApplication.h"

class windows_application : public platform_application
{
public:
    windows_application(const std::string& name): platform_application(name) {}

private:
};
