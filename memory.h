
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <array>
#include <cstddef>
#include <cstdint>

using address_t = uint32_t;
using tag_t = uint8_t;

enum { REAL_ADDR_LEN = 28 };
enum { MEM_SIZE = 0x1 << (REAL_ADDR_LEN - 4) };
//enum { MEM_SIZE = 0x10000 };    // TODO: decide about memory size
enum { TAGS_NUM = MEM_SIZE / 16 };

// Memory allocations must be aligned on 16 bytes

class Memory
{
public:
    Memory();
    ~Memory();
    void read(address_t address, void* dst, size_t nbyte);
    void write(address_t address, void* src, size_t nbyte);
    tag_t getTag(address_t address);
    void setTag(address_t address, tag_t tag);

    //int dump(void* start=)

private:
    uint8_t* memory_;
    std::array<tag_t, TAGS_NUM> tags;
};

#endif
