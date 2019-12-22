#include <functional>
//#include <elf.h>
//#include <gelf.h>
#include "../memory.h"
#include <err.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <chrono>

#include "simulator.h"

void Simulator::load(const char* name)
{
    FILE* file = fopen(name, "r");
    uint32_t tmp = 0;
    
    uint32_t addr = 0xff;
    riscv.hart.pc = addr;
    while(fscanf(file, "%u", &tmp) != EOF)
    {
        riscv.memory.write(addr, &tmp, 4);
        uint32_t a = 0;
        riscv.memory.read(addr, &a, 4);
        addr += 4;
    }
}

uint32_t Simulator::fetch(address_t address)
{
    uint32_t tmp = 0;
    riscv.memory.read(address, &tmp, 4);

    printf("%u\n", tmp);
    return tmp;
}

Instruction Simulator::decode(uint32_t encoding)
{
    return decoder.decode(encoding);
}

void Simulator::execute(const Instruction& instr)
{
    std::invoke(instr.executor, riscv, instr);
}

void Simulator::run()
{

    printf("0x%x\n", riscv.hart.pc);
    while(true)
    {
        //std::cout << std::hex << riscv.hart.pc << "\n";
        //std::cerr << riscv.hart.pc << "\n\n";
        if(riscv.hart.pc > MEM_SIZE)
            break;
        uint32_t encoding = fetch(riscv.hart.pc);
        Instruction instr = decode(encoding);
        execute(instr);
    }

}
