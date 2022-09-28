#include "VulkanDevice.h"

#include <utility>
#include "../../Misc/Assert.h"

VulkanDevice::VulkanDevice(VulkanDynamicRHI *inRHI, vk::raii::PhysicalDevice inHandle)
    : rhi(inRHI)
    , physicalHandle(std::move(inHandle)) {
    ensure(nullptr != inRHI, "[VulkanDevice::VulkanDevice] RHI pointer should not be null");
}
