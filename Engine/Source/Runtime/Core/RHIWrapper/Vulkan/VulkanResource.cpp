#include "VulkanResource.h"
#include "../../Misc/ResourceStreaming.h"

SpirVCode SpirVCode::LoadSpirVCodeFromFile(const std::string &InFilePath) {
    return SpirVCode(ReadBinaryFile(InFilePath));
}
