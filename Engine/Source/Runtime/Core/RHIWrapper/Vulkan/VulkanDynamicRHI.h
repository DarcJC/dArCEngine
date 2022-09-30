#pragma once

#include "../../RHI/DynamicRHI.h"
#include "../../LLAL/Platform.h"
#include "../../Misc/Assert.h"
#include "VulkanDevice.h"

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

private:
    /** We only keep 1 vulkan instance per RHI instance */
    vk::raii::Instance instance_ = nullptr;

    /** wrapped device */
    std::optional<VulkanDevice> device_;

    /** keep debug messenger in lifetime */
    std::optional<vk::raii::DebugUtilsMessengerEXT> debug_utils_messenger_;

    /** SDL window */
    SDL_Window* sdl_window_;

    /**
     * Surface\n
     * Surface is creating by SDL library.\n
     * Releasing in by ourselves following RAII pattern.
     */
    std::optional<vk::SurfaceKHR> surface_;

    /** flags */
    bool use_validation_layer = false;

public:

private:

};
