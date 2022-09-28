#include "VulkanDynamicRHI.h"
#include "VulkanQueue.h"
#include "../../Misc/Assert.h"
#include "spdlog/spdlog.h"

VulkanDynamicRHI::~VulkanDynamicRHI() {
    ;
}

void VulkanDynamicRHI::Init() {
    InitInstance();
    device_ = PickDevice();
}

void VulkanDynamicRHI::PostInit() {
}

void VulkanDynamicRHI::Shutdown() {
}

void VulkanDynamicRHI::InitInstance() {
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
        // : Collect layers and extensions to enable
        std::vector<const char*> layers, extensions;
        CollectLayers(layers);
        CollectExtensions(extensions);
        // : Instance options struct
        vk::InstanceCreateInfo instanceCreateInfo(
                vk::InstanceCreateFlags(),
                &applicationInfo,
                layers.size(),
                layers.data(),
                extensions.size(),
                extensions.data()
        );
        // : Create vulkan instance
        instance_ = vk::raii::Instance(context, instanceCreateInfo);
    }
}

VulkanDevice VulkanDynamicRHI::PickDevice() {
    vk::raii::PhysicalDevices physicalDevices(instance_);
    spdlog::info("[VulkanRHI] Found {} devices.", physicalDevices.size());
    std::optional<vk::raii::PhysicalDevice> selectedDevice;

    for (const vk::raii::PhysicalDevice& pDevice : physicalDevices) {
        vk::PhysicalDeviceProperties prop = pDevice.getProperties();
        // don't select cpu
        if (prop.deviceType == vk::PhysicalDeviceType::eOther || prop.deviceType == vk::PhysicalDeviceType::eCpu)
            continue;
        // TODO: check limits
        if (!DeviceQueueIndices::NewQueueIndices(pDevice).IsValid()) {
            continue;
        }

        selectedDevice = pDevice;
    }

    ensure(selectedDevice.has_value(), "[VulkanDynamicRHI::PickDevice] No compatible device was found.");
    return {this, selectedDevice.value()};
}
