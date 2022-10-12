#include "VulkanDevice.h"
#include "VulkanDynamicRHI.h"

#include <utility>
#include <set>

VulkanDevice::VulkanDevice(VulkanDynamicRHI *inRHI, vk::raii::PhysicalDevice inHandle)
    : rhi_(inRHI)
    , physicalHandle(std::move(inHandle)) {
    ensure(nullptr != inRHI, "[VulkanDevice::VulkanDevice] RHI pointer should not be null");
}

void VulkanDevice::Init() {
    simple_queue_indices_ = DeviceQueueIndices::NewQueueIndices(physicalHandle, rhi_->GetSurface()->get());

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

    std::vector<const char*> layers, exts; // layers is ignored by up-to-date implementations
    CollectExtensions(exts);

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

void VulkanDevice::CollectExtensions(std::vector<const char*>& outExt) {
    outExt.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

bool VulkanDevice::CheckDevice(const vk::raii::PhysicalDevice& physicalDevice, vk::UniqueSurfaceKHR& surface) {
    // extensions device supported
    std::vector<vk::ExtensionProperties> deviceSupportedExts = physicalDevice.enumerateDeviceExtensionProperties();
    // extensions we needed
    std::vector<const char*> requiredExts;
    CollectExtensions(requiredExts);
    std::set<std::string> requiredExtsUnique(requiredExts.begin(), requiredExts.end());
    // check
    for (const auto& extProp : deviceSupportedExts) {
        requiredExtsUnique.erase(extProp.extensionName);
    }

    // check swapchain support
    std::vector<vk::SurfaceFormatKHR> formats = physicalDevice.getSurfaceFormatsKHR(surface.get());
    std::vector<vk::PresentModeKHR> presentModes = physicalDevice.getSurfacePresentModesKHR(surface.get());

    return requiredExtsUnique.empty() &&
        !formats.empty() && !presentModes.empty();
}

