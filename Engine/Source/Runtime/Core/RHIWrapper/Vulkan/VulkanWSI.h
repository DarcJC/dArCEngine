#pragma once
#include "vulkan/vulkan_raii.hpp"
#include "SDL_vulkan.h"
#include "../../Misc/Assert.h"

/** forward decl */
class VulkanDynamicRHI;

struct SwapchainSupport {
    vk::SurfaceCapabilitiesKHR capabilities;
    std::optional<std::vector<vk::SurfaceFormatKHR>> formats;
    std::optional<std::vector<vk::PresentModeKHR>> present_modes;
};

class VulkanDisplay {

private:
    VulkanDynamicRHI* rhi_;

    SwapchainSupport swapchainDetail;

    vk::raii::SwapchainKHR swapchain_ = VK_NULL_HANDLE;

    std::optional<std::vector<VkImage>> swapchainImages;

    vk::Extent2D swapchainExtent;
    vk::SurfaceFormatKHR surfaceFormat;

    std::vector<vk::raii::ImageView> swapchainImageViews;

public:
    explicit VulkanDisplay(VulkanDynamicRHI* rhi) : rhi_(rhi) {
        ensure(nullptr != rhi, "[VulkanDisplay] RHI object* should not be nullptr");
    }

    void Init();

    /**
     * select most suitable surface format
     * return nullopt if formats is empty
     * @param formats available formats(vkGetPhysicalDeviceSurfaceFormatsKHR)
     * @return selected format
     */
    static std::optional<vk::SurfaceFormatKHR> PickSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats);

    /**
     * select most suitable present mode
     * return nullopt if present modes if empty
     * @param presentModes available present modes
     * @return selected present mode
     */
    static std::optional<vk::PresentModeKHR> PickPresentMode(const std::vector<vk::PresentModeKHR>& presentModes);

    /**
     * get extent that swapchain should in
     * @param capabilities
     * @param window
     * @return Extent2D
     */
    static vk::Extent2D FetchSwapchainExtent(const vk::SurfaceCapabilitiesKHR& capabilities, SDL_Window* window);

private:

public:

};
