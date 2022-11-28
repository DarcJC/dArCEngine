#pragma once

#include "../../RHI/DynamicRHI.h"
#include "../../LLAL/Platform.h"
#include "../../Misc/Assert.h"
#include "VulkanDevice.h"
#include "VulkanWSI.h"

#include <vector>
#include <optional>
#include "SDL.h"
#include "vulkan/vulkan_raii.hpp"
#include "vulkan/vk_enum_string_helper.h"
#include "spdlog/spdlog.h"

class VulkanDynamicRHI : public DynamicRHI {

public:

    explicit VulkanDynamicRHI(SDL_Window* window);
    ~VulkanDynamicRHI() override;

    void Init() override;
    void PostInit() override;
    void Shutdown() override;

    void Tick(u32 deltaTime) override;

    /** Setup vulkan instance */
    void InitInstance();

    /** Select the physical device we use */
    VulkanDevice PickDevice();

    /** Collect layers need to be enabled */
    void CollectLayers(std::vector<const char*>& out_layers);

    /** Collect extensions need to be enabled */
    void CollectExtensions(std::vector<const char*>& out_exts);

    /** Create vulkan surface */
    void InitSurface();

    /** Init Vulkan display layer */
    void InitDisplay();

private:
    /** We only keep 1 vulkan instance per RHI instance */
    vk::raii::Instance instance_ = nullptr;

    /** wrapped device */
    static std::optional<VulkanDevice> device_;

    /** display wrapper */
    std::optional<VulkanDisplay> display_;

    /** keep debug messenger in lifetime */
    std::optional<vk::raii::DebugUtilsMessengerEXT> debug_utils_messenger_;

    /** SDL window */
    SDL_Window* sdl_window_;

    /**
     * Surface\n
     * Surface is creating by SDL library.\n
     * Releasing in by ourselves following RAII pattern.
     */
    vk::UniqueSurfaceKHR surface_;

    /** flags */
    bool use_validation_layer = false;

public:
    const vk::UniqueSurfaceKHR* GetSurface() { return &surface_; }

    static VulkanDevice& GetWrappedDevice() { return device_.value(); }

    VulkanDisplay& GetWrappedDisplay() { return display_.value(); }

    SDL_Window* GetSDLWindow() { return sdl_window_; }

private:

};
