#include "VulkanDevice.h"
#include "VulkanResource.h"
#include "VulkanDynamicRHI.h"

vk::raii::ShaderModule VulkanShader::CreateShaderModule(const SpirVCode& Code, vk::ShaderModuleCreateFlags Flags) {
    vk::ShaderModuleCreateInfo CreateInfo { Flags, Code.GetCodeView().size(), Code.GetCodeView().data() };
    VulkanDevice& Device = VulkanDynamicRHI::GetWrappedDevice();
    return Device.GetLogicalDevice().createShaderModule(CreateInfo);
}

