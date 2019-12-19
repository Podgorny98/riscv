#!/usr/bin/python3.6

import yaml
import sys


sys.stdin = open("test.asm")
file = open("risc-v.yaml")

data = yaml.safe_load(file)
fields = data["fields"]
instructions = data["instructions"]

labels = {}
consts = {'r16': '16', 'r17': '17', 'r14': '14', 'r15': '15', 'r12': '12', 'r13': '13', 'r10': '10', 'r11': '11', 'r18': '18', 'r19': '19', 'r29': '29', 'r28': '28', 'r27': '27', 'r26': '26', 'r25': '25', 'r24': '24', 'r23': '23', 'r22': '22', 'r21': '21', 'r20': '20', 'r4': '4', 'r5': '5', 'r6': '6', 'r7': '7', 'r0': '0', 'r1': '1', 'r2': '2', 'r3': '3', 'r30': '30', 'r8': '8', 'r9': '9', 'r31': '31'}
consts.update({'R4': 'r4', 'R5': 'r5', 'R6': 'r6', 'R7': 'r7', 'R0': 'r0', 'R1': 'r1', 'R2': 'r2', 'R3': 'r3', 'R8': 'r8', 'R9': 'r9', 'R16': 'r16', 'R17': 'r17', 'R14': 'r14', 'R15': 'r15', 'R12': 'r12', 'R13': 'r13', 'R10': 'r10', 'R11': 'r11', 'R31': 'r31', 'R30': 'r30', 'R18': 'r18', 'R19': 'r19', 'R29': 'r29', 'R28': 'r28', 'R27': 'r27', 'R26': 'r26', 'R25': 'r25', 'R24': 'r24', 'R23': 'r23', 'R22': 'r22', 'R21': 'r21', 'R20': 'r20'})


def gen_bit_mask(msb, lsb):
    res = 0
    for i in range(lsb, msb+1):
        res |= 1 << i
    return res

def gen_bitf(msb, lsb, fromb, tob, val):
    return ((gen_bit_mask(fromb, tob) & val) >> tob) << lsb

def gen_field(field, val):
    res = 0
    for bitf in field["location"]["bits"]:
        res |= gen_bitf(bitf["msb"], bitf["lsb"], bitf["from"], bitf["to"], val)
    return res

def arg_convert(args, addr):
    for i in range(len(args)):
        args[i] = args[i].strip()
        while 1:
            try: 
                int(args[i])
                break
            except:
                try: 
                    args[i] = consts[args[i]]
                except:
                    try:
                        args[i] = int(labels[args[i]]) - addr
                    except:
                        print("error: " + args[i] + " not found")
                        return
    return args

    
def gen_opcode(instr, args):
    res = instr["fixedvalue"]
    for field in instr["fields"]:
        res |= gen_field(fields[field], int(args[instr["fields"].index(field)]))
    return res
    



lines = sys.stdin.readlines()
ep = 0
print("EP:\t" + format(ep, "08X")) 

for line in lines:
    if len(line.strip()) > 0 and line.strip()[0] == ";":
        lines.remove(line)

addr = 0
for line in lines:
    components = line.strip().split()
    
    if len(components) == 0: continue
    if components[0].strip()[-1:] == ":":
        labels.update({components[0].strip()[:-1] : addr})
        components.remove(components[0])
    if len(components) == 0: continue
    
    ok = False
    for instr in instructions:
        if instr["mnemonic"] == components[0]: 
            ok = True
            break
    if not ok: 
        print(components[0] + " not an instruction")
        exit()
    addr += 4            
    
addr = 0
for line in lines:
    components = line.strip().split()
    
    if len(components) == 0: continue
    if components[0].strip()[-1:] == ":":
        labels.update({components[0].strip()[:-1] : addr})
        components.remove(components[0])
    if len(components) == 0: continue
    
    if len(components) > 1:
        args = " ".join(components[1:]).split(",")
        args = arg_convert(args, addr)
    
    ok = False
    for instr in instructions:
        if instr["mnemonic"] == components[0]: 
            ok = True
            break
    if not ok: 
        print(components[0] + " not an instruction")
        exit()
    
    print( format(addr, "X") + "\t" + format(gen_opcode(instr, args), "08X")) 
    addr += 4


