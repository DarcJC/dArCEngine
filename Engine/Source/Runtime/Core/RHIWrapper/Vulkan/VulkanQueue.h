#pragma once
#include "vulkan/vulkan_raii.hpp"
#include <optional>
#include "../../LLAL/Platform.h"

struct DeviceQueueIndices {

    static DeviceQueueIndices NewQueueIndices(const vk::raii::PhysicalDevice& device);
    static DeviceQueueIndices NewQueueIndices(
            const vk::raii::PhysicalDevice& device,
            const vk::SurfaceKHR& surface);

    std::optional<u32> graphic;
    std::optional<u32> compute;
    std::optional<u32> transfer;
    std::optional<u32> sparse_binding;
    std::optional<u32> protect;

    std::optional<u32> present;

    [[nodiscard]] bool IsValid() const;
};
