#include "vulkan/vulkan_raii.hpp"
#include "VulkanDynamicRHI.h"
#include "VulkanWSI.h"

void VulkanDisplay::Init() {
    // create swapchain image
    {
        // prepare data
        vk::SurfaceCapabilitiesKHR capabilities;
        VkPhysicalDevice rawPhysicalDevice = *rhi_->GetWrappedDevice().GetPhysicalDevice();
        auto rawSurface = (*const_cast<vk::UniqueSurfaceKHR *>(rhi_->GetSurface()))->operator VkSurfaceKHR();
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(rawPhysicalDevice, rawSurface,
                                                  &swapchainDetail.capabilities.operator VkSurfaceCapabilitiesKHR &());

        auto &physicalDevice = rhi_->GetWrappedDevice().GetPhysicalDevice();
        auto *surface = const_cast<vk::UniqueSurfaceKHR *>(rhi_->GetSurface());

        swapchainDetail.formats = physicalDevice.getSurfaceFormatsKHR(surface->get());
        swapchainDetail.present_modes = physicalDevice.getSurfacePresentModesKHR(surface->get());

        surfaceFormat = PickSurfaceFormat(swapchainDetail.formats.value()).value();
        vk::PresentModeKHR presentMode = PickPresentMode(swapchainDetail.present_modes.value()).value();
        swapchainExtent = FetchSwapchainExtent(swapchainDetail.capabilities, rhi_->GetSDLWindow());
        u32 imageCnt = swapchainDetail.capabilities.minImageCount + 1;
        if (swapchainDetail.capabilities.maxImageCount > 0 && imageCnt > swapchainDetail.capabilities.maxImageCount) {
            imageCnt = swapchainDetail.capabilities.maxImageCount;
        }

        // create info
        vk::SwapchainCreateFlagsKHR flags;
        vk::SwapchainCreateInfoKHR createInfo{
                flags,
                surface->get(),
                imageCnt,
                surfaceFormat.format,
                surfaceFormat.colorSpace,
                swapchainExtent,
                1,
                vk::ImageUsageFlagBits::eColorAttachment
        };

        // set to concurrent sharing mode
        DeviceQueueIndices queueIndices = DeviceQueueIndices::NewQueueIndices(physicalDevice, surface->get());
        u32 queueFamilyIndices[] = {queueIndices.graphic.value(), queueIndices.present.value()};

        if (queueIndices.graphic != queueIndices.present) {
            createInfo.setImageSharingMode(vk::SharingMode::eConcurrent);
            createInfo.setQueueFamilyIndexCount(2);
            createInfo.setPQueueFamilyIndices(queueFamilyIndices);
        } else {
            createInfo.setImageSharingMode(vk::SharingMode::eExclusive);
            createInfo.setQueueFamilyIndexCount(0);
            createInfo.setPQueueFamilyIndices(nullptr);
        }

        createInfo.setPreTransform(swapchainDetail.capabilities.currentTransform);
        createInfo.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
        createInfo.setPresentMode(presentMode);
        createInfo.setClipped(VK_TRUE);

        // TODO: recreate swapchain when window resized
        createInfo.setOldSwapchain(VK_NULL_HANDLE);

        auto &device = rhi_->GetWrappedDevice().GetLogicalDevice();
        swapchain_ = device.createSwapchainKHR(createInfo);

        swapchainImages = std::make_optional(swapchain_.getImages());
    }

    // create image view using image as texture
    {
        auto& device = rhi_->GetWrappedDevice().GetLogicalDevice();
        for (const vk::Image& i : *swapchainImages) {
            vk::ImageViewCreateInfo createInfo {
                    vk::ImageViewCreateFlags(),
                    i,
                    vk::ImageViewType::e2D,
                    surfaceFormat.format,
                    vk::ComponentMapping {
                        vk::ComponentSwizzle::eIdentity,
                        vk::ComponentSwizzle::eIdentity,
                        vk::ComponentSwizzle::eIdentity,
                        vk::ComponentSwizzle::eIdentity
                    },
                    vk::ImageSubresourceRange {
                        vk::ImageAspectFlagBits::eColor,
                        0,
                        1,
                        0,
                        1,
                    },
            };
            swapchainImageViews.push_back(device.createImageView(createInfo));
        }
    }
}

std::optional<vk::SurfaceFormatKHR> VulkanDisplay::PickSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats) {
    if (formats.empty()) return std::nullopt;

    for (const auto& format : formats) {
        if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return std::make_optional(format);
        }
    }

    return std::make_optional(formats[0]);
}

std::optional<vk::PresentModeKHR> VulkanDisplay::PickPresentMode(const std::vector<vk::PresentModeKHR> &presentModes) {
    if (presentModes.empty()) return std::nullopt;

    for (const auto& presentMode : presentModes) {
        if (presentMode == vk::PresentModeKHR::eMailbox) {
            return std::make_optional(presentMode);
        }
    }

    return std::make_optional(vk::PresentModeKHR::eFifo);
}

vk::Extent2D VulkanDisplay::FetchSwapchainExtent(const vk::SurfaceCapabilitiesKHR& capabilities, SDL_Window* window) {
    if (std::numeric_limits<u32>::max() != capabilities.currentExtent.width) {
        return capabilities.currentExtent;
    } else {
        u32 width, height;
        SDL_Vulkan_GetDrawableSize(window, reinterpret_cast<int *>(&width), reinterpret_cast<int *>(&height));

        vk::Extent2D extent = {width, height};

        extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return extent;
    }
}
