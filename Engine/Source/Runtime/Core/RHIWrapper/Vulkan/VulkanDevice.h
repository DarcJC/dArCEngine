#pragma once
#include "vulkan/vulkan_raii.hpp"

class VulkanDynamicRHI;

class VulkanDevice final {

public:
    VulkanDevice() = delete;
    VulkanDevice(VulkanDynamicRHI* rhi, vk::raii::PhysicalDevice physicalDevice);

private:
    VulkanDynamicRHI* rhi;
    vk::raii::PhysicalDevice physicalHandle;

};
