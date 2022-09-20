#pragma once
#include "../../RHI/DynamicRHI.h"
#include "../../LLAL/Platform.h"

#include <vector>

class VulkanDynamicRHI : public DynamicRHI {

public:

    ~VulkanDynamicRHI() override;

    void Init() override;
    void PostInit() override;
    void Shutdown() override;

    /** Setup vulkan instance */
    void InitInstance();

    /** Collect layers need to be enabled */
    void CollectLayers(std::vector<const char*>& out_layers);

    /** Collect extensions need to be enabled */
    void CollectExtensions(std::vector<const char*>& out_exts);

private:
    /** We only keep 1 vulkan instance per RHI instance */
    std::shared_ptr<vk::raii::Instance> instance_ = nullptr;

    /** flags */
    bool use_validation_layer = false;

public:

private:

};
