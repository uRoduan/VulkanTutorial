//
// Created by Roduan on 2023/2/21.
//

#ifndef VULKANTUTORIAL_MEMORYBLOCK_HPP
#define VULKANTUTORIAL_MEMORYBLOCK_HPP

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace MyMemoryManager
{
    struct Block
    {
        VkDeviceMemory memory;
        VkDeviceSize offset;
        VkDeviceSize size;
        bool free;
        void* ptr = nullptr;

        bool operator==(Block const& block);
    };

    bool Block::operator==(const Block &block) {
        return (memory == block.memory &&
                offset == block.offset &&
                size == block.size &&
                free == block.free &&
                ptr == block.ptr);
    }
}

#endif //VULKANTUTORIAL_MEMORYBLOCK_HPP
