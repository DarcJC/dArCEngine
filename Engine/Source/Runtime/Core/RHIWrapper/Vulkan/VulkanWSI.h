#pragma once
#include "vulkan/vulkan_raii.hpp"
#include "../../Misc/Assert.h"

/** forward decl */
class VulkanDynamicRHI;

struct SwapchainSupport {
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> present_modes;
};

class VulkanDisplay {

private:
    VulkanDynamicRHI* rhi_;

public:
    explicit VulkanDisplay(VulkanDynamicRHI* rhi) : rhi_(rhi) {
        ensure(nullptr != rhi, "[VulkanDisplay] RHI object* should not be nullptr");
    }

    void Init();

};
