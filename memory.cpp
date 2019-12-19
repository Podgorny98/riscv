
#include "memory.h"

#include <iostream>
#include <cassert>
#include <cstring>

void Memory::read(address_t address, void* dst, std::size_t nbyte)
{
    uint32_t real_addr = address & (0xF << 28);
    assert((real_addr < MEM_SIZE + nbyte) && "Memory read out of bounds");
    std::memcpy(dst, &memory_[real_addr], nbyte);
}

void Memory::write(address_t address, void* src, std::size_t nbyte)
{
    uint32_t real_addr = address & (0xF << 28);
    assert((real_addr < MEM_SIZE + nbyte) && "Memory write out of bounds");
    std::memcpy(&memory_[real_addr], src, nbyte);
}

