#pragma once
#include "../../RHI/DynamicRHI.h"

class VulkanDynamicRHI : public DynamicRHI {

public:

    ~VulkanDynamicRHI() override;

    void Init() override;
    void PostInit() override;
    void Shutdown() override;

    /** Setup vulkan instance */
    void InitInstance();

private:
    /** We only keep 1 vulkan instance per RHI instance */
    std::shared_ptr<vk::raii::Instance> instance_ = nullptr;

};
