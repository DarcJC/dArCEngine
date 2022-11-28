#pragma once

#include "../../LLAL/Platform.h"
#include "vulkan/vulkan_raii.hpp"
#include <vector>
#include <span>
#include <string>

class SpirVCode {
    explicit SpirVCode(std::vector<u8>&& InUncompressCode) : UncompressCode(InUncompressCode) {
        CodeView = std::span<u32>( reinterpret_cast<u32*>(UncompressCode.data()), UncompressCode.size() / (sizeof(u32) / sizeof(u8)) );
    }

    explicit SpirVCode(std::vector<u32>&& InUncompressCode) : CodeView(InUncompressCode) {
    }

    std::span<u32> CodeView;
    std::vector<u8> UncompressCode;

public:
    TRYINLINE [[nodiscard]] std::span<u32> GetCodeView() const { return CodeView; }

#pragma region Construction
public:
    TRYINLINE static SpirVCode LoadSpirVCodeFromFile(const std::string& InFilePath);
#pragma endregion Construction
};

class VulkanShader {
public:
    static vk::raii::ShaderModule CreateShaderModule(const SpirVCode& Code, vk::ShaderModuleCreateFlags Flags = {});
};
