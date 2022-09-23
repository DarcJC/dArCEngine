#pragma once
#include "vulkan/vulkan_raii.hpp"

class VulkanDynamicRHI;

class VulkanDevice final {

public:
    VulkanDevice(VulkanDynamicRHI* rhi, vk::PhysicalDevice physicalDevice);

private:
    VulkanDynamicRHI* rhi;
    vk::PhysicalDevice physicalHandle;

};
