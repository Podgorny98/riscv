
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cstddef>
#include <cstdint>

typedef uint32_t address_t;

enum { MEM_SIZE = 0x10000000 };

class Memory
{
public:
    Memory() = default;
    ~Memory() {}
    void read(address_t address, void* dst, size_t nbyte);
    void write(address_t address, void* src, size_t nbyte);

    //int dump(void* start=)

//private:
    uint8_t memory_[MEM_SIZE];
};

#endif

