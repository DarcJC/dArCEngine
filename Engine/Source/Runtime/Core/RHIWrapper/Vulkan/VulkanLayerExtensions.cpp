#include "VulkanDynamicRHI.h"
#include "spdlog/spdlog.h"

void VulkanDynamicRHI::CollectLayers(std::vector<const char*>& out_layers) {
#ifdef ENABLE_VALIDATION_LAYER
    out_layers.push_back("VK_LAYER_KHRONOS_validation");
    use_validation_layer = true;
#endif // ENABLE_VALIDATION_LAYER

    // Check layers
    {
        u32 layers_count;

        auto res = vk::enumerateInstanceLayerProperties(&layers_count, nullptr);
        if (res != vk::Result::eSuccess && res != vk::Result::eIncomplete)
            throw std::runtime_error("[VulkanDynamicRHI::CollectLayers] enumerateInstanceLayerProperties failed");

        std::vector<vk::LayerProperties> available_layers(layers_count);
        res = vk::enumerateInstanceLayerProperties(&layers_count, available_layers.data());
        if (res != vk::Result::eSuccess && res != vk::Result::eIncomplete)
            throw std::runtime_error("[VulkanDynamicRHI::CollectLayers] enumerateInstanceLayerProperties failed");

        for (auto layer : out_layers) {
            bool flag = false;

            for (auto al : available_layers) {
                if (strcmp(layer, al.layerName) == 0) {
                    flag = true;
                    break;
                }
            }

            if (!flag) throw std::runtime_error("[VulkanDynamicRHI::CollectLayers] Unsupported layer");
        }
    }
}

void VulkanDynamicRHI::CollectExtensions(std::vector<const char*>& out_exts) {
}
