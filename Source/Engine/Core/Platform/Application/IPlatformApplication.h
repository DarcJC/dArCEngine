#pragma once
#include <string>

class platform_application
{
public:
    explicit platform_application(const std::string name = "dArCEngine"): name_(name) {}
    virtual ~platform_application() = default;

protected:
    std::string name_;
};
