#include "VulkanDynamicRHI.h"
#include "../../Misc/Assert.h"
#include "spdlog/spdlog.h"
#include "SDL_vulkan.h"

void VulkanDynamicRHI::CollectLayers(std::vector<const char*>& out_layers) {
#ifdef ENABLE_VALIDATION_LAYER
    out_layers.push_back("VK_LAYER_KHRONOS_validation");
    use_validation_layer = true;
#endif // ENABLE_VALIDATION_LAYER

    // Check layers
    {
        u32 layers_count;

        auto res = vk::enumerateInstanceLayerProperties(&layers_count, nullptr);
        ensure(res == vk::Result::eSuccess || res == vk::Result::eIncomplete, "[VulkanDynamicRHI::CollectLayers] enumerateInstanceLayerProperties failed.");

        std::vector<vk::LayerProperties> available_layers(layers_count);
        res = vk::enumerateInstanceLayerProperties(&layers_count, available_layers.data());
        ensure(res == vk::Result::eSuccess || res == vk::Result::eIncomplete, "[VulkanDynamicRHI::CollectLayers] enumerateInstanceLayerProperties failed.");

        for (auto layer : out_layers) {
            bool flag = false;

            for (auto al : available_layers) {
                if (strcmp(layer, al.layerName) == 0) {
                    flag = true;
                    break;
                }
            }

            ensure(flag, "[VulkanDynamicRHI::CollectLayers] Unsupported layer");
        }
    }
}

void VulkanDynamicRHI::CollectExtensions(std::vector<const char*>& out_exts) {
#ifdef ENABLE_VALIDATION_LAYER
    out_exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // ENABLE_VALIDATION_LAYER

    // get sdl required
    u32 current_count = out_exts.size();
    u32 sdl_ext_count;
    ensure(SDL_Vulkan_GetInstanceExtensions(sdl_window_, &sdl_ext_count, nullptr) == SDL_TRUE, "[VulkanDynamicRHI::CollectExtensions] failed to get vulkan extension for sdl.");
    out_exts.resize(current_count + sdl_ext_count);
    ensure(SDL_Vulkan_GetInstanceExtensions(sdl_window_, &sdl_ext_count, out_exts.data() + current_count) == SDL_TRUE, "[VulkanDynamicRHI::CollectExtensions] failed to get vulkan extension for sdl.");
}
