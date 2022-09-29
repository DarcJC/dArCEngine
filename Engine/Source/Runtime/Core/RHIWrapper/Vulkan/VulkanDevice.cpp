#include "VulkanDevice.h"

#include <utility>
#include "../../Misc/Assert.h"

VulkanDevice::VulkanDevice(VulkanDynamicRHI *inRHI, vk::raii::PhysicalDevice inHandle)
    : rhi(inRHI)
    , physicalHandle(std::move(inHandle)) {
    ensure(nullptr != inRHI, "[VulkanDevice::VulkanDevice] RHI pointer should not be null");
}

void VulkanDevice::init() {
    simple_queue_indices_ = DeviceQueueIndices::NewQueueIndices(physicalHandle);

    float graphicPriority[] { 1.0f };
    vk::DeviceQueueCreateInfo graphicQueueCI{
        {},
        simple_queue_indices_->graphic.value(),
        1,
        graphicPriority
    };

    std::vector<vk::DeviceQueueCreateInfo> queues { graphicQueueCI };

    vk::DeviceCreateInfo {
        {},
        queues,
        {},
        {},
        {}
    };
}
