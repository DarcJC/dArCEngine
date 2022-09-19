#include "VulkanDynamicRHI.h"

VulkanDynamicRHI::~VulkanDynamicRHI() {
    ;
}

void VulkanDynamicRHI::Init() {
}

void VulkanDynamicRHI::PostInit() {
}

void VulkanDynamicRHI::Shutdown() {
}

void VulkanDynamicRHI::InitInstance() {
    try {
        // Create Vulkan instance
        {
            // : Binding of "global" func are not related to vkInstance, vkDevice etc.
            vk::raii::Context context;
            // : Current app info with names and version, also vk version required
            vk::ApplicationInfo applicationInfo(
                    "dArCRuntime", VK_MAKE_API_VERSION(0, 0, 1, 0),
                    "dArCEngine", VK_MAKE_API_VERSION(0, 0, 1, 0),
                    VK_API_VERSION_1_3
            );
            // : Instance options struct
            vk::InstanceCreateInfo instanceCreateInfo(
                    vk::InstanceCreateFlags(),
                    &applicationInfo,
                    0,
                    {},
                    0,
                    {}
            );
            // : Create vulkan instance
            instance_ = std::make_shared<vk::raii::Instance>(context, instanceCreateInfo);
        }
    } catch (vk::SystemError &err) {}
}
