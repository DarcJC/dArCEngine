#pragma once
#include "vulkan/vulkan_raii.hpp"
#include "../../Misc/Assert.h"

/** forward decl */
class VulkanDynamicRHI;

struct SwapchainSupport {
    vk::SurfaceCapabilitiesKHR capabilities;
    std::optional<std::vector<vk::SurfaceFormatKHR>> formats;
    std::optional<std::vector<vk::PresentModeKHR>> present_modes;
};

class VulkanDisplay {

private:
    VulkanDynamicRHI* rhi_;

    SwapchainSupport swapchainDetail;

public:
    explicit VulkanDisplay(VulkanDynamicRHI* rhi) : rhi_(rhi) {
        ensure(nullptr != rhi, "[VulkanDisplay] RHI object* should not be nullptr");
    }

    void Init();

};
