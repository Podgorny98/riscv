#!/usr/bin/python3.6

import yaml
import sys


abi = { 'zero': 0,
        'ra': 1,
        'sp': 2,
        'gp': 3,
        'tp': 4,
        't0': 5,
        't1': 6,
        't2': 7,
        's0': 8,
        's1': 9,
        'a0': 10,
        'a1': 11,
        'a2': 12,
        'a3': 13,
        'a4': 14,
        'a5': 15,
        'a6': 16,
        'a6': 17,
        's2': 18,
        's3': 19,
        's4': 20,
        's5': 21,
        's6': 22,
        's7': 23,
        's8': 24,
        's9': 25,
        's10': 26,
        's11': 27,
        't3': 28,
        't4': 29,
        't5': 30,
        't6': 31}

def getInstr(instructions, mnem):
    for instr in instructions:
        if instr['mnemonic'] == mnem:
            return instr
    return None

def genBitMask(msb, lsb):
    res = 0
    for i in range(lsb, msb+1):
        res |= 1 << i
    return res

def genBitf(bits, val):
    mask = genBitMask(bits['from'], bits['to'])
    res = ((val & mask) >> bits['to']) << bits['lsb']
    return res

def genField(field, val):
    res = 0
    for bits in field['location']['bits']:
        res |= genBitf(bits, val)
    return res

def parseArgs(components):

    def isdigit(n):
        try:
            int(n)
            return True
        except ValueError:
            return  False

    args = list()
    imm = None
    digit = [x for x in components if isdigit(x)]
    if digit:
        imm = int(digit[0]) & 0xffffffff

    params = components[1:]

    for param in params:
        if isdigit(param):
            continue
        args.append(abi[param])
    if imm is not None:
        args.append(imm)
    return args

def genOpcode(data, components):
    mnem = components[0]
    args = parseArgs(components)

    #print(mnem)
    #print(args)
    instr = getInstr(data['instructions'], mnem)
    #print(instr)
    opcode = instr['fixedvalue']
    #print(opcode)


    for i, dfield in enumerate(instr['fields']):
        field = data['fields'][dfield]
        opcode |= genField(field, args[i])
    print(opcode)


def main():
    isa = open("risc-v.yaml")
    data = yaml.safe_load(isa)

    fields = data["fields"]
    instructions = data["instructions"]
    asm = open('main.s')

    lines = asm.readlines()

    for line in lines:
        components = line.strip().replace('(', ' ').replace(')', ' ').replace(',', ' ').split()
        genOpcode(data, components)

if __name__ == '__main__':
    main()






