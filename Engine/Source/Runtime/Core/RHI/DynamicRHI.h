#pragma once

#include "vulkan/vulkan_raii.hpp"

class DynamicRHI {

public:
    /** trivial deconstructor */
    virtual ~DynamicRHI() = default;
    virtual void Init() = 0;
    virtual void PostInit() {};
    virtual void Shutdown() = 0;

};

