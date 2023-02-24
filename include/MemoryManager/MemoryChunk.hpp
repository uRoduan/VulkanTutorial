//
// Created by Roduan on 2023/2/21.
//

#ifndef VULKANTUTORIAL_MEMORYCHUNK_HPP
#define VULKANTUTORIAL_MEMORYCHUNK_HPP

#include "MemoryBlock.hpp"
#include <vector>

namespace MyMemoryManager
{
    class Chunk
    {
    public:
        Chunk(VkDevice &device, VkDeviceSize size, int memoryTypeIndex);

        bool allocate(VkDeviceSize size, Block& block);
        bool isIn(Block const& block) const;
        void deallocate(Block const& block);
        int memoryTypeIndex() const;

        ~Chunk();

    protected:
        VkDevice mDeivce;
        VkDeviceMemory  mSize;
        int mMemoryTypeIndex;
        std::vector<Block> mBlocks;
        void* mPtr = nullptr;
    };

    Chunk::Chunk(VkDevice &device, VkDeviceSize size, int memoryTypeIndex) {

    }

    bool Chunk::allocate(VkDeviceSize size, Block &block) {
        return false;
    }

    bool Chunk::isIn(const Block &block) const {
        return false;
    }

    void Chunk::deallocate(const Block &block) {

    }

    int Chunk::memoryTypeIndex() const {
        return 0;
    }
}


#endif //VULKANTUTORIAL_MEMORYCHUNK_HPP
