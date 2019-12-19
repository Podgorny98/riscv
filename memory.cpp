
#include "memory.h"

#include <iostream>
#include <cassert>
#include <cstring>

void Memory::read(address_t address, void* dst, std::size_t nbyte)
{
    uint32_t real_addr = address & ~(0xF << REAL_ADDR_LEN);
    assert((real_addr < MEM_SIZE + nbyte) && "Memory read out of bounds");
    std::memcpy(dst, &memory_[real_addr], nbyte);
}

void Memory::write(address_t address, void* src, std::size_t nbyte)
{
    uint32_t real_addr = address & ~(0xF << REAL_ADDR_LEN);
    assert((real_addr < MEM_SIZE + nbyte) && "Memory write out of bounds");
    std::memcpy(&memory_[real_addr], src, nbyte);
}

tag_t Memory::getTag(address_t address)
{
  uint32_t real_addr = address & ~(0xF << REAL_ADDR_LEN);
  uint32_t tag_num = (real_addr % 16) ? (real_addr / 16) : (real_addr / 16 + 1);
  return tags.at(tag_num);
}

void Memory::setTag(address_t address, tag_t tag)
{
  uint32_t real_addr = address & ~(0xF << REAL_ADDR_LEN);
  uint32_t tag_num = (real_addr % 16) ? (real_addr / 16) : (real_addr / 16 + 1);
  tags.at(tag_num) = tag;
}
