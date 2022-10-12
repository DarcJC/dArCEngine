#include "vulkan/vulkan_raii.hpp"
#include "VulkanDynamicRHI.h"
#include "VulkanWSI.h"

void VulkanDisplay::Init() {
    vk::SurfaceCapabilitiesKHR capabilities;
    VkPhysicalDevice rawPhysicalDevice = *rhi_->GetWrappedDevice().GetPhysicalDevice();
    auto rawSurface = (*const_cast<vk::UniqueSurfaceKHR *>(rhi_->GetSurface()))->operator VkSurfaceKHR();
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(rawPhysicalDevice, rawSurface, &swapchainDetail.capabilities.operator VkSurfaceCapabilitiesKHR &());

    auto& physicalDevice = rhi_->GetWrappedDevice().GetPhysicalDevice();
    auto* surface = const_cast<vk::UniqueSurfaceKHR *>(rhi_->GetSurface());

    swapchainDetail.formats = physicalDevice.getSurfaceFormatsKHR(surface->get());
    swapchainDetail.present_modes = physicalDevice.getSurfacePresentModesKHR(surface->get());
}
