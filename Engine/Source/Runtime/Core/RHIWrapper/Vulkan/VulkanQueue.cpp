#include "VulkanQueue.h"

DeviceQueueIndices DeviceQueueIndices::NewQueueIndices(const vk::raii::PhysicalDevice& device) {
    DeviceQueueIndices indices;

    auto queueProps = device.getQueueFamilyProperties();
    for (auto it = queueProps.begin(); it != queueProps.end(); ++it) {
        if (it->queueFlags & vk::QueueFlagBits::eGraphics) {
            indices.graphic = std::distance(queueProps.begin(), it);

            if (it->queueFlags & vk::QueueFlagBits::eProtected) {
                indices.protect = std::distance(queueProps.begin(), it);
            } else if (it->queueFlags & vk::QueueFlagBits::eSparseBinding) {
                indices.sparse_binding = std::distance(queueProps.begin(), it);
            } else if (it->queueFlags & vk::QueueFlagBits::eTransfer) {
                indices.transfer = std::distance(queueProps.begin(), it);
            }
        } else if (it->queueFlags & vk::QueueFlagBits::eCompute) {
            indices.compute = std::distance(queueProps.begin(), it);
        }
    }

    return indices;
}

bool DeviceQueueIndices::IsValid() const {
    return graphic.has_value() && present.has_value();
}

DeviceQueueIndices
DeviceQueueIndices::NewQueueIndices(const vk::raii::PhysicalDevice &device, const vk::SurfaceKHR& surface) {
    DeviceQueueIndices indices = NewQueueIndices(device);

    auto queueProps = device.getQueueFamilyProperties();
    for (auto it = queueProps.begin(); it <= queueProps.end(); ++it) {
        if ( VK_TRUE == device.getSurfaceSupportKHR(std::distance(queueProps.begin(), it), surface) ) {
            indices.present = std::distance(queueProps.begin(), it);
            break;
        }
    }

    return indices;
}
