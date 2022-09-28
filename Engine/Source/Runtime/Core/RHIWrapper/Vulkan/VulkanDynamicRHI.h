#pragma once
#include "../../RHI/DynamicRHI.h"
#include "../../LLAL/Platform.h"
#include "VulkanDevice.h"

#include <vector>
#include <optional>
#include "SDL.h"

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

private:
    /** We only keep 1 vulkan instance per RHI instance */
    vk::raii::Instance instance_ = nullptr;

    /** wrapped device */
    std::optional<VulkanDevice> device_;

    /** SDL window */
    SDL_Window* sdl_window_;

    /** flags */
    bool use_validation_layer = false;

public:

private:

};
