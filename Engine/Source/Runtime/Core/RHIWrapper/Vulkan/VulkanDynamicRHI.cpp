#include "VulkanQueue.h"
#include "../../Misc/Assert.h"
#include "spdlog/spdlog.h"
#include "VulkanDynamicRHI.h"

/**
 * Vulkan debug message callback function
 */
static VKAPI_ATTR VkBool32 VKAPI_CALL debugMessageCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userdata) {
    ensure(nullptr != callbackData, "[debugMessageCallback] callback data must valid");

    if (messageSeverity <= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
        spdlog::debug("[{}] {}", string_VkDebugUtilsMessageTypeFlagsEXT(messageType), callbackData->pMessage);
    } else if (messageSeverity <= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
        spdlog::info("[{}] {}", string_VkDebugUtilsMessageTypeFlagsEXT(messageType), callbackData->pMessage);
    } else if (messageSeverity <= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        spdlog::warn("[{}] {}", string_VkDebugUtilsMessageTypeFlagsEXT(messageType), callbackData->pMessage);
    } else if (messageSeverity <= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
        spdlog::error("[{}] {}", string_VkDebugUtilsMessageTypeFlagsEXT(messageType), callbackData->pMessage);
    } else {
        spdlog::critical("[{}] {}", string_VkDebugUtilsMessageTypeFlagsEXT(messageType), callbackData->pMessage);
    }

    return VK_FALSE;
}

/** Create a new debug messenger create info */
vk::DebugUtilsMessengerCreateInfoEXT newDebugMessengerCreateInfo() {
    vk::DebugUtilsMessengerCreateInfoEXT info {
            vk::DebugUtilsMessengerCreateFlagsEXT(),
            vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
            vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
            debugMessageCallback,
            nullptr
    };

    return info;
}

VulkanDynamicRHI::VulkanDynamicRHI(SDL_Window* window) : sdl_window_(window) {
}

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

void VulkanDynamicRHI::Tick(u32 deltaTime) {
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
#ifdef ENABLE_VALIDATION_LAYER
        std::optional<vk::DebugUtilsMessengerCreateInfoEXT> debugMessengerCreateInfo; /** must in lifetime before create instance finished */
        if (use_validation_layer) {
            debugMessengerCreateInfo = newDebugMessengerCreateInfo();
            instanceCreateInfo.pNext = &debugMessengerCreateInfo.value();
        }
#endif // ENABLE_VALIDATION_LAYER
        // : Create vulkan instance
        instance_ = vk::raii::Instance(context, instanceCreateInfo);
    }
    // Setup validation layer
    {
#ifdef ENABLE_VALIDATION_LAYER
        auto createInfo = newDebugMessengerCreateInfo();
        debug_utils_messenger_ = instance_.createDebugUtilsMessengerEXT(createInfo);
#endif // ENABLE_VALIDATION_LAYER
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
