#include "VulkanDynamicRHI.h"
#include "spdlog/spdlog.h"
#include "../../Misc/Assert.h"

void VulkanDynamicRHI::CollectLayers(std::vector<const char*>& out_layers) {
#ifdef ENABLE_VALIDATION_LAYER
    out_layers.push_back("VK_LAYER_KHRONOS_validation");
    use_validation_layer = true;
#endif // ENABLE_VALIDATION_LAYER

    // Check layers
    {
        u32 layers_count;

        auto res = vk::enumerateInstanceLayerProperties(&layers_count, nullptr);
        ensure(res != vk::Result::eSuccess && res != vk::Result::eIncomplete, "[VulkanDynamicRHI::CollectLayers] enumerateInstanceLayerProperties failed");

        std::vector<vk::LayerProperties> available_layers(layers_count);
        res = vk::enumerateInstanceLayerProperties(&layers_count, available_layers.data());
        ensure(res != vk::Result::eSuccess && res != vk::Result::eIncomplete, "[VulkanDynamicRHI::CollectLayers] enumerateInstanceLayerProperties failed");

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
}
