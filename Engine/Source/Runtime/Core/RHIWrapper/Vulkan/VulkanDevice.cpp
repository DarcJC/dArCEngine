#include "VulkanDevice.h"

#include <utility>
#include <set>
#include "../../Misc/Assert.h"
#include "../../LLAL/Platform.h"

VulkanDevice::VulkanDevice(VulkanDynamicRHI *inRHI, vk::raii::PhysicalDevice inHandle)
    : rhi(inRHI)
    , physicalHandle(std::move(inHandle)) {
    ensure(nullptr != inRHI, "[VulkanDevice::VulkanDevice] RHI pointer should not be null");
}

void VulkanDevice::init() {
    simple_queue_indices_ = DeviceQueueIndices::NewQueueIndices(physicalHandle);

    std::set<u32> uniqueQueueFamilies { simple_queue_indices_->graphic.value(), simple_queue_indices_->present.value() };
    std::vector<vk::DeviceQueueCreateInfo> queues;

    float graphicPriority[] { 1.0f };
    for (u32 family : uniqueQueueFamilies) {
        queues.push_back(
            vk::DeviceQueueCreateInfo {
                {},
                family,
                1,
                graphicPriority
            });
    }

    std::vector<const char*> layers, exts;

    vk::PhysicalDeviceFeatures features;
    features.setGeometryShader(true);
    features.setDepthBiasClamp(true);
    features.setDepthClamp(true);
    features.setDrawIndirectFirstInstance(true);
    features.setFillModeNonSolid(true);
    features.setFragmentStoresAndAtomics(true);
    features.setFullDrawIndexUint32(true);
    features.setLargePoints(true);
    features.setLogicOp(true);
    features.setOcclusionQueryPrecise(true);
    features.setRobustBufferAccess(true);
    features.setSamplerAnisotropy(true);
    features.setShaderClipDistance(true);
    features.setShaderCullDistance(true);
    features.setShaderImageGatherExtended(true);
    features.setShaderStorageImageExtendedFormats(true);

    vk::DeviceCreateInfo deviceCreateInfo {
        {},
        queues,
        layers,
        exts,
        &features
    };

    device_ = physicalHandle.createDevice(deviceCreateInfo);

    graphicQueue = device_->getQueue(simple_queue_indices_->graphic.value(), 0);
    presentQueue = device_->getQueue(simple_queue_indices_->present.value(), 0);

}
