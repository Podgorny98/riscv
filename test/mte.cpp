
#include "../simulator.h"

#define ENCODING 0
#define EXECUTOR nullptr
#define RS1 0
#define RS2 0
#define RD 0
#define IMM 0


// Instruction(encoding, executor, imm, rs1, rs2, rd)

int main()
{
    Simulator sim;

    uint8_t x1 = 1; // holds address
    uint8_t x2 = 2; // holds tag
    uint8_t x3 = 3;
    uint8_t x4 = 4;
    tag_t tag = 0xa;
    reg_t data = 0x12345678;
    address_t addr = 0xf000abcd;
    Instruction i = {ENCODING, EXECUTOR, IMM, RS1, RS2, RD};

    // addi x1, x1, addr -> x1 = adr
    i = {ENCODING, EXECUTOR, addr, x1, RS2, x1};
    sim.riscv.addi(i);

    // addi x2, x2, tag  -> x2 = tag
    i = {ENCODING, EXECUTOR, tag, x2, RS2, x2};
    sim.riscv.addi(i);

    // sptg x1, x2       -> x1.tag = x2 = tag
    i = {ENCODING, EXECUTOR, IMM, x2, RS2, x1};
    sim.riscv.sptg(i);

    // gptg x3, 0(x1)    -> x3 = (x1 + 0).tag = x1.tag = tag
    i = {ENCODING, EXECUTOR, 0, x1, RS2, x3};
    sim.riscv.gptg(i);

    assert(sim.riscv.hart.getReg(x3) == tag && "Invalid tag in reg");

    // stg x2, 1(x1) -> Mem[x1 + 1].tag = x2 = tag (+1 doesn't change tag num)
    i = {ENCODING, EXECUTOR, 1, x1, x2, RD};
    sim.riscv.stg(i);

    // addi x4, x4, data  -> x4 = data
    i = {ENCODING, EXECUTOR, data, x4, RS2, x4};
    sim.riscv.addi(i);

    // cmptg x2, 0(x1) -> exception if Mem[x1].tag != tag
    i = {ENCODING, EXECUTOR, 0, x1, x2, RD};
    sim.riscv.cmptg(i);


    // sw x4, 0(x1) -> Mem[x1] = x4 = data
    i = {ENCODING, EXECUTOR, 0, x1, x4, RD};
    sim.riscv.sw(i);

    // lw x3, 0(x1) -> x3 = Mem[x1] = data
    i = {ENCODING, EXECUTOR, 0, x1, RS2, x3};
    sim.riscv.lw(i);

    assert(sim.riscv.hart.getReg(x3) == data && "Invalid data readed");

    // xor x3, x3, x3   -> x3 = 0
    i = {ENCODING, EXECUTOR, IMM, x3, x3, x3};
    sim.riscv.xor_(i);

    // addi x3, x3, !tag -> x3 = !tag
    i = {ENCODING, EXECUTOR, !tag, x3, RS2, x3};
    sim.riscv.addi(i);

    // stg x3, 1(x1) -> Mem[x1 - 1].tag = x3 = !tag (-1 doesn't change tag num)
    // Change tag in memory
    i = {ENCODING, EXECUTOR, -1, x1, x3, RD};
    sim.riscv.stg(i);

    // cmptg x2, 0(x1) -> exception if Mem[x1].tag != tag
    // Compare tags in address and in memory  (Exception expected)
    i = {ENCODING, EXECUTOR, 0, x1, x2, RD};
    sim.riscv.cmptg(i);

    // lw x3, 0(x1) -> x3 = Mem[x1] = data               (won't be executed)
    i = {ENCODING, EXECUTOR, 0, x1, RS2, x3};
    sim.riscv.lw(i);

    return 0;
}

