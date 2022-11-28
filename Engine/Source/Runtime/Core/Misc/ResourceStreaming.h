#pragma once

#include "../LLAL/Platform.h"
#include <vector>
#include <fstream>

TRYINLINE std::vector<u8> ReadBinaryFile(const std::string& Filename) {
    std::ifstream File(Filename, std::ios::ate | std::ios::binary);

    if (File.is_open()) {
        i64 FileSize = File.tellg();
        std::vector<u8> Buffer(FileSize);
        File.seekg(0);
        File.read(reinterpret_cast<char*>(Buffer.data()), FileSize);
        File.close();

        return Buffer;
    }

    return {};
}
