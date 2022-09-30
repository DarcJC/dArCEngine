#pragma once

#include <optional>
#include "vulkan/vulkan_raii.hpp"
#include "VulkanQueue.h"

class VulkanDynamicRHI;

class VulkanDevice final {

public:
    VulkanDevice() = delete;
    VulkanDevice(VulkanDynamicRHI* rhi, vk::raii::PhysicalDevice physicalDevice);

    void Init();

    static void CollectExtensions(std::vector<const char*>& outExt);

    static bool CheckDevice(const vk::raii::PhysicalDevice& physicalDevice);

private:
    /**
     * Handles
     */
    VulkanDynamicRHI* rhi_;
    /** Vulkan handle of GPU */
    vk::raii::PhysicalDevice physicalHandle;
    /** Logical device in vulkan */
    std::optional<vk::raii::Device> device_;

    /**
     * Queue related
     */
    std::optional<DeviceQueueIndices> simple_queue_indices_;
    std::optional<vk::raii::Queue> graphicQueue;
    std::optional<vk::raii::Queue> presentQueue;

};
