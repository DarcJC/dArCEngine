#pragma once

#include "vulkan/vulkan_raii.hpp"
#include "../LLAL/Platform.h"

class DynamicRHI {

public:
    /** trivial deconstructor */
    virtual ~DynamicRHI() = default;
    virtual void Init() = 0;
    virtual void PostInit() {};
    virtual void Shutdown() = 0;

    virtual void Tick(u32 deltaTime) = 0;

};

