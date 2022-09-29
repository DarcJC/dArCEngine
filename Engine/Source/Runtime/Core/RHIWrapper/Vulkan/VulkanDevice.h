#pragma once

#include <optional>
#include "vulkan/vulkan_raii.hpp"
#include "VulkanQueue.h"

class VulkanDynamicRHI;

class VulkanDevice final {

public:
    VulkanDevice() = delete;
    VulkanDevice(VulkanDynamicRHI* rhi, vk::raii::PhysicalDevice physicalDevice);

    void init();

private:
    VulkanDynamicRHI* rhi;
    vk::raii::PhysicalDevice physicalHandle;
    std::optional<vk::raii::Device> device_;
    std::optional<DeviceQueueIndices> simple_queue_indices_;

};
