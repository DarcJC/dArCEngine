#include "VulkanDevice.h"
#include "../../Misc/Assert.h"

VulkanDevice::VulkanDevice(VulkanDynamicRHI *inRHI, vk::PhysicalDevice inHandle)
    : rhi(inRHI)
    , physicalHandle(inHandle) {
    ensure(nullptr != inRHI, "[VulkanDevice::VulkanDevice] RHI pointer should not be null");
}
