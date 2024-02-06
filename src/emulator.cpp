#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>

struct ConditionCodes {
  uint8_t z:1;
  uint8_t s:1;
  uint8_t p:1;
  uint8_t cy:1;
  uint8_t ac:1;
  uint8_t pad:3;
};

struct State8080 {
  uint8_t a;
  uint8_t b;
  uint8_t c;
  uint8_t d;
  uint8_t e;
  uint8_t h;
  uint8_t l;
  uint16_t sp;
  uint16_t pc = 0;
  uint8_t *memory = new uint8_t[0x10000]; // Allocate 16K;
  struct ConditionCodes cc;
  uint8_t int_enable;
};

class Disassemler {
  private:
    std::string getHexString(unsigned char *instruction, std::string opcode, int opbytes = 1, bool isAddress = false) {
      std::stringstream res;
      res << opcode;

      if (opbytes > 1) {
        res << (isAddress ? " $" : ", #$");
      }

      if (opbytes == 3) {
        res << std::hex << std::setw(2) << std::setfill('0') << (instruction[2] & 0xFF);
        res << std::hex << std::setw(2) << std::setfill('0') << (instruction[1] & 0xFF);
      } else if (opbytes == 2) {
        res << std::hex << std::setw(2) << std::setfill('0') << (instruction[1] & 0xFF);
      }

      res << '\n';

      return res.str();
    }
  
  public:
    void disassemble(int pc, unsigned char *opcode) {
      unsigned char *instruction = &opcode[pc];
      std::cout << std::hex << std::setw(4) << std::setfill('0') << pc << " ";
      
      switch (*instruction) {
          case 0x00: std::cout << getHexString(instruction, "NOP"); break;
          case 0x01: std::cout << getHexString(instruction, "LXI B", 3); break;
          case 0x02: std::cout << getHexString(instruction, "STAX B"); break;
          case 0x03: std::cout << getHexString(instruction, "INX B"); break;
          case 0x04: std::cout << getHexString(instruction, "INR B"); break;
          case 0x05: std::cout << getHexString(instruction, "DCR B"); break;
          case 0x06: std::cout << getHexString(instruction, "MVI B", 2); break;
          case 0x07: std::cout << getHexString(instruction, "RLC"); break;
          case 0x08: std::cout << getHexString(instruction, "NOP"); break;
          case 0x09: std::cout << getHexString(instruction, "DAD B"); break;
          case 0x10: std::cout << getHexString(instruction, "NOP"); break;
          case 0x0a: std::cout << getHexString(instruction, "LDAX B"); break;
          case 0x0b: std::cout << getHexString(instruction, "DCX B"); break;
          case 0x0c: std::cout << getHexString(instruction, "INR C"); break;
          case 0x0d: std::cout << getHexString(instruction, "DCR C"); break;
          case 0x0e: std::cout << getHexString(instruction, "MVI C", 2); break;
          case 0x0f: std::cout << getHexString(instruction, "RRC", 1); break;
          case 0x11: std::cout << getHexString(instruction, "LXI D", 3); break;
          case 0x12: std::cout << getHexString(instruction, "STAX D"); break;
          case 0x13: std::cout << getHexString(instruction, "INX D"); break;
          case 0x14: std::cout << getHexString(instruction, "INR D"); break;
          case 0x15: std::cout << getHexString(instruction, "DCR D"); break;
          case 0x16: std::cout << getHexString(instruction, "MVI D", 2); break;
          case 0x17: std::cout << getHexString(instruction, "RAL"); break;
          case 0x18: std::cout << getHexString(instruction, "NOP"); break;
          case 0x19: std::cout << getHexString(instruction, "DAD D"); break;
          case 0x1a: std::cout << getHexString(instruction, "LDAX D"); break;
          case 0x1b: std::cout << getHexString(instruction, "DCX D"); break;
          case 0x1c: std::cout << getHexString(instruction, "INR E"); break;
          case 0x1d: std::cout << getHexString(instruction, "DCR E"); break;
          case 0x1e: std::cout << getHexString(instruction, "MVI E", 2); break;
          case 0x1f: std::cout << getHexString(instruction, "RAR"); break;
          case 0x21: std::cout << getHexString(instruction, "LXI H", 3); break;
          case 0x22: std::cout << getHexString(instruction, "SHLD", 3, true); break;
          case 0x23: std::cout << getHexString(instruction, "INX H"); break;
          case 0x24: std::cout << getHexString(instruction, "INR H"); break;
          case 0x25: std::cout << getHexString(instruction, "DCR H"); break;
          case 0x26: std::cout << getHexString(instruction, "MVI H", 2); break;
          case 0x27: std::cout << getHexString(instruction, "DAA"); break;
          case 0x28: std::cout << getHexString(instruction, "NOP"); break;
          case 0x29: std::cout << getHexString(instruction, "DAD H"); break;
          case 0x2a: std::cout << getHexString(instruction, "LHLD", 3, true); break;
          case 0x2b: std::cout << getHexString(instruction, "DCX H"); break;
          case 0x2c: std::cout << getHexString(instruction, "INR L"); break;
          case 0x2d: std::cout << getHexString(instruction, "DCR L"); break;
          case 0x2e: std::cout << getHexString(instruction, "MVI L", 2); break;
          case 0x2f: std::cout << getHexString(instruction, "CMA"); break;
          case 0x31: std::cout << getHexString(instruction, "LXI SP", 3); break;
          case 0x32: std::cout << getHexString(instruction, "STA", 3, true); break;
          case 0x33: std::cout << getHexString(instruction, "INX SP"); break;
          case 0x34: std::cout << getHexString(instruction, "INR M"); break;
          case 0x35: std::cout << getHexString(instruction, "DCR M"); break;
          case 0x36: std::cout << getHexString(instruction, "MVI M", 2); break;
          case 0x37: std::cout << getHexString(instruction, "STC"); break;
          case 0x38: std::cout << getHexString(instruction, "NOP"); break;
          case 0x39: std::cout << getHexString(instruction, "DAD SP"); break;
          case 0x3a: std::cout << getHexString(instruction, "LDA", 3, true); break;
          case 0x3b: std::cout << getHexString(instruction, "DCX SP"); break;
          case 0x3c: std::cout << getHexString(instruction, "INR A"); break;
          case 0x3d: std::cout << getHexString(instruction, "DCR A"); break;
          case 0x3e: std::cout << getHexString(instruction, "MVI A", 2); break;
          case 0x3f: std::cout << getHexString(instruction, "CMC"); break;
          case 0x40: std::cout << getHexString(instruction, "MOV B,B"); break;
          case 0x41: std::cout << getHexString(instruction, "MOV B,C"); break;
          case 0x42: std::cout << getHexString(instruction, "MOV B,D"); break;
          case 0x43: std::cout << getHexString(instruction, "MOV B,E"); break;
          case 0x44: std::cout << getHexString(instruction, "MOV B,H"); break;
          case 0x45: std::cout << getHexString(instruction, "MOV B,L"); break;
          case 0x46: std::cout << getHexString(instruction, "MOV B,M"); break;
          case 0x47: std::cout << getHexString(instruction, "MOV B,A"); break;
          case 0x48: std::cout << getHexString(instruction, "MOV C,B"); break;
          case 0x49: std::cout << getHexString(instruction, "MOV C,C"); break;
          case 0x4a: std::cout << getHexString(instruction, "MOV C,D"); break;
          case 0x4b: std::cout << getHexString(instruction, "MOV C,E"); break;
          case 0x4c: std::cout << getHexString(instruction, "MOV C,H"); break;
          case 0x4d: std::cout << getHexString(instruction, "MOV C,L"); break;
          case 0x4e: std::cout << getHexString(instruction, "MOV C,M"); break;
          case 0x4f: std::cout << getHexString(instruction, "MOV C,A"); break;
          case 0x50: std::cout << getHexString(instruction, "MOV D,B"); break;
          case 0x51: std::cout << getHexString(instruction, "MOV D,C"); break;
          case 0x52: std::cout << getHexString(instruction, "MOV D,D"); break;
          case 0x53: std::cout << getHexString(instruction, "MOV D,E"); break;
          case 0x54: std::cout << getHexString(instruction, "MOV D,H"); break;
          case 0x55: std::cout << getHexString(instruction, "MOV D,L"); break;
          case 0x56: std::cout << getHexString(instruction, "MOV D,M"); break;
          case 0x57: std::cout << getHexString(instruction, "MOV D,A"); break;
          case 0x58: std::cout << getHexString(instruction, "MOV E,B"); break;
          case 0x59: std::cout << getHexString(instruction, "MOV E,C"); break;
          case 0x5a: std::cout << getHexString(instruction, "MOV E,D"); break;
          case 0x5b: std::cout << getHexString(instruction, "MOV E,E"); break;
          case 0x5c: std::cout << getHexString(instruction, "MOV E,H"); break;
          case 0x5d: std::cout << getHexString(instruction, "MOV E,L"); break;
          case 0x5e: std::cout << getHexString(instruction, "MOV E,M"); break;
          case 0x5f: std::cout << getHexString(instruction, "MOV E,A"); break;
          case 0x60: std::cout << getHexString(instruction, "MOV H,B"); break;
          case 0x61: std::cout << getHexString(instruction, "MOV H,C"); break;
          case 0x62: std::cout << getHexString(instruction, "MOV H,D"); break;
          case 0x63: std::cout << getHexString(instruction, "MOV H,E"); break;
          case 0x64: std::cout << getHexString(instruction, "MOV H,H"); break;
          case 0x65: std::cout << getHexString(instruction, "MOV H,L"); break;
          case 0x66: std::cout << getHexString(instruction, "MOV H,M"); break;
          case 0x67: std::cout << getHexString(instruction, "MOV H,A"); break;
          case 0x68: std::cout << getHexString(instruction, "MOV L,B"); break;
          case 0x69: std::cout << getHexString(instruction, "MOV L,C"); break;
          case 0x6a: std::cout << getHexString(instruction, "MOV L,D"); break;
          case 0x6b: std::cout << getHexString(instruction, "MOV L,E"); break;
          case 0x6c: std::cout << getHexString(instruction, "MOV L,H"); break;
          case 0x6d: std::cout << getHexString(instruction, "MOV L,L"); break;
          case 0x6e: std::cout << getHexString(instruction, "MOV L,M"); break;
          case 0x6f: std::cout << getHexString(instruction, "MOV L,A"); break;
          case 0x70: std::cout << getHexString(instruction, "MOV M,B"); break;
          case 0x71: std::cout << getHexString(instruction, "MOV M,C"); break;
          case 0x72: std::cout << getHexString(instruction, "MOV M,D"); break;
          case 0x73: std::cout << getHexString(instruction, "MOV M,E"); break;
          case 0x74: std::cout << getHexString(instruction, "MOV M,H"); break;
          case 0x75: std::cout << getHexString(instruction, "MOV M,L"); break;
          case 0x76: std::cout << getHexString(instruction, "HLT"); break;
          case 0x77: std::cout << getHexString(instruction, "MOV M,A"); break;
          case 0x78: std::cout << getHexString(instruction, "MOV A,B"); break;
          case 0x79: std::cout << getHexString(instruction, "MOV A,C"); break;
          case 0x7a: std::cout << getHexString(instruction, "MOV A,D"); break;
          case 0x7b: std::cout << getHexString(instruction, "MOV A,E"); break;
          case 0x7c: std::cout << getHexString(instruction, "MOV A,H"); break;
          case 0x7d: std::cout << getHexString(instruction, "MOV A,L"); break;
          case 0x7e: std::cout << getHexString(instruction, "MOV A,M"); break;
          case 0x7f: std::cout << getHexString(instruction, "MOV A,A"); break;
          case 0x80: std::cout << getHexString(instruction, "ADD B"); break;
          case 0x81: std::cout << getHexString(instruction, "ADD C"); break;
          case 0x82: std::cout << getHexString(instruction, "ADD D"); break;
          case 0x83: std::cout << getHexString(instruction, "ADD E"); break;
          case 0x84: std::cout << getHexString(instruction, "ADD H"); break;
          case 0x85: std::cout << getHexString(instruction, "ADD L"); break;
          case 0x86: std::cout << getHexString(instruction, "ADD M"); break;
          case 0x87: std::cout << getHexString(instruction, "ADD A"); break;
          case 0x88: std::cout << getHexString(instruction, "ADC B"); break;
          case 0x89: std::cout << getHexString(instruction, "ADC C"); break;
          case 0x8a: std::cout << getHexString(instruction, "ADC D"); break;
          case 0x8b: std::cout << getHexString(instruction, "ADC E"); break;
          case 0x8c: std::cout << getHexString(instruction, "ADC H"); break;
          case 0x8d: std::cout << getHexString(instruction, "ADC L"); break;
          case 0x8e: std::cout << getHexString(instruction, "ADC M"); break;
          case 0x8f: std::cout << getHexString(instruction, "ADC A"); break;
          case 0x90: std::cout << getHexString(instruction, "SUB B"); break;
          case 0x91: std::cout << getHexString(instruction, "SUB C"); break;
          case 0x92: std::cout << getHexString(instruction, "SUB D"); break;
          case 0x93: std::cout << getHexString(instruction, "SUB E"); break;
          case 0x94: std::cout << getHexString(instruction, "SUB H"); break;
          case 0x95: std::cout << getHexString(instruction, "SUB L"); break;
          case 0x96: std::cout << getHexString(instruction, "SUB M"); break;
          case 0x97: std::cout << getHexString(instruction, "SUB A"); break;
          case 0x98: std::cout << getHexString(instruction, "SBB B"); break;
          case 0x99: std::cout << getHexString(instruction, "SBB C"); break;
          case 0x9a: std::cout << getHexString(instruction, "SBB D"); break;
          case 0x9b: std::cout << getHexString(instruction, "SBB E"); break;
          case 0x9c: std::cout << getHexString(instruction, "SBB H"); break;
          case 0x9d: std::cout << getHexString(instruction, "SBB L"); break;
          case 0x9e: std::cout << getHexString(instruction, "SBB M"); break;
          case 0x9f: std::cout << getHexString(instruction, "SBB A"); break;
          case 0xa0: std::cout << getHexString(instruction, "ANA B"); break;
          case 0xa1: std::cout << getHexString(instruction, "ANA C"); break;
          case 0xa2: std::cout << getHexString(instruction, "ANA D"); break;
          case 0xa3: std::cout << getHexString(instruction, "ANA E"); break;
          case 0xa4: std::cout << getHexString(instruction, "ANA H"); break;
          case 0xa5: std::cout << getHexString(instruction, "ANA L"); break;
          case 0xa6: std::cout << getHexString(instruction, "ANA M"); break;
          case 0xa7: std::cout << getHexString(instruction, "ANA A"); break;
          case 0xa8: std::cout << getHexString(instruction, "XRA B"); break;
          case 0xa9: std::cout << getHexString(instruction, "XRA C"); break;
          case 0xaa: std::cout << getHexString(instruction, "XRA D"); break;
          case 0xab: std::cout << getHexString(instruction, "XRA E"); break;
          case 0xac: std::cout << getHexString(instruction, "XRA H"); break;
          case 0xad: std::cout << getHexString(instruction, "XRA L"); break;
          case 0xae: std::cout << getHexString(instruction, "XRA M"); break;
          case 0xaf: std::cout << getHexString(instruction, "XRA A"); break;
          case 0xb0: std::cout << getHexString(instruction, "ORA B"); break;
          case 0xb1: std::cout << getHexString(instruction, "ORA C"); break;
          case 0xb2: std::cout << getHexString(instruction, "ORA D"); break;
          case 0xb3: std::cout << getHexString(instruction, "ORA E"); break;
          case 0xb4: std::cout << getHexString(instruction, "ORA H"); break;
          case 0xb5: std::cout << getHexString(instruction, "ORA L"); break;
          case 0xb6: std::cout << getHexString(instruction, "ORA M"); break;
          case 0xb7: std::cout << getHexString(instruction, "ORA A"); break;
          case 0xb8: std::cout << getHexString(instruction, "CMP B"); break;
          case 0xb9: std::cout << getHexString(instruction, "CMP C"); break;
          case 0xba: std::cout << getHexString(instruction, "CMP D"); break;
          case 0xbb: std::cout << getHexString(instruction, "CMP E"); break;
          case 0xbc: std::cout << getHexString(instruction, "CMP H"); break;
          case 0xbd: std::cout << getHexString(instruction, "CMP L"); break;
          case 0xbe: std::cout << getHexString(instruction, "CMP M"); break;
          case 0xbf: std::cout << getHexString(instruction, "CMP A"); break;
          case 0xc0: std::cout << getHexString(instruction, "RNZ"); break;
          case 0xc1: std::cout << getHexString(instruction, "POP B"); break;
          case 0xc2: std::cout << getHexString(instruction, "JNZ", 3, true); break;
          case 0xc3: std::cout << getHexString(instruction, "JMP", 3, true); break;
          case 0xc4: std::cout << getHexString(instruction, "CNZ", 3, true); break;
          case 0xc5: std::cout << getHexString(instruction, "PUSH B"); break;
          case 0xc6: std::cout << getHexString(instruction, "ADI", 2); break;
          case 0xc7: std::cout << getHexString(instruction, "RST 0"); break;
          case 0xc8: std::cout << getHexString(instruction, "RZ"); break;
          case 0xc9: std::cout << getHexString(instruction, "RET"); break;
          case 0xca: std::cout << getHexString(instruction, "JZ", 3, true); break;
          case 0xcb: std::cout << getHexString(instruction, "JUMP", 3, true); break;
          case 0xcc: std::cout << getHexString(instruction, "CZ", 3, true); break;
          case 0xcd: std::cout << getHexString(instruction, "CALL", 3, true); break;
          case 0xce: std::cout << getHexString(instruction, "ACI", 2); break;
          case 0xcf: std::cout << getHexString(instruction, "RST 1"); break;
          case 0xd0: std::cout << getHexString(instruction, "RNC"); break;
          case 0xd1: std::cout << getHexString(instruction, "POP D"); break;
          case 0xd2: std::cout << getHexString(instruction, "JNC", 3, true); break;
          case 0xd3: std::cout << getHexString(instruction, "OUT", 2); break;
          case 0xd4: std::cout << getHexString(instruction, "CNC", 3, true); break;
          case 0xd5: std::cout << getHexString(instruction, "PUSH D"); break;
          case 0xd6: std::cout << getHexString(instruction, "SUI", 2); break;
          case 0xd7: std::cout << getHexString(instruction, "RST 2"); break;
          case 0xd8: std::cout << getHexString(instruction, "RC"); break;
          case 0xd9: std::cout << getHexString(instruction, "RET"); break;
          case 0xda: std::cout << getHexString(instruction, "JC", 3, true); break;
          case 0xdb: std::cout << getHexString(instruction, "IN", 2); break;
          case 0xdc: std::cout << getHexString(instruction, "CC", 3, true); break;
		      case 0xdd: std::cout << getHexString(instruction, "CALL", 3, true); break;
          case 0xde: std::cout << getHexString(instruction, "SBI", 2); break;
          case 0xdf: std::cout << getHexString(instruction, "RST 3"); break;
          case 0xe0: std::cout << getHexString(instruction, "RPO"); break;
          case 0xe1: std::cout << getHexString(instruction, "POP H"); break;
          case 0xe2: std::cout << getHexString(instruction, "JPO", 3, true); break;
          case 0xe3: std::cout << getHexString(instruction, "XTHL"); break;
          case 0xe4: std::cout << getHexString(instruction, "CPO", 3, true); break;
          case 0xe5: std::cout << getHexString(instruction, "PUSH H"); break;
          case 0xe6: std::cout << getHexString(instruction, "ANI", 2); break;
          case 0xe7: std::cout << getHexString(instruction, "RST 4"); break;
          case 0xe8: std::cout << getHexString(instruction, "RPE"); break;
          case 0xe9: std::cout << getHexString(instruction, "PCHL"); break;
          case 0xea: std::cout << getHexString(instruction, "JPE", 3, true); break;
          case 0xeb: std::cout << getHexString(instruction, "XCHG"); break;
          case 0xec: std::cout << getHexString(instruction, "CPE", 3, true); break;
          case 0xed: std::cout << getHexString(instruction, "CALL", 2); break;
          case 0xee: std::cout << getHexString(instruction, "XRI", 2); break;
          case 0xef: std::cout << getHexString(instruction, "RST 5"); break;
          case 0xf0: std::cout << getHexString(instruction, "RP"); break;
          case 0xf1: std::cout << getHexString(instruction, "POP PSW"); break;
          case 0xf2: std::cout << getHexString(instruction, "JP", 3, true); break;
          case 0xf3: std::cout << getHexString(instruction, "DI"); break;
          case 0xf4: std::cout << getHexString(instruction, "CP", 3, true); break;
          case 0xf5: std::cout << getHexString(instruction, "PUSH PSW"); break;
          case 0xf6: std::cout << getHexString(instruction, "ORI", 2); break;
          case 0xf7: std::cout << getHexString(instruction, "RST 6"); break;
          case 0xf8: std::cout << getHexString(instruction, "RM"); break;
          case 0xf9: std::cout << getHexString(instruction, "SPHL"); break;
          case 0xfa: std::cout << getHexString(instruction, "JM", 3, true); break;
          case 0xfb: std::cout << getHexString(instruction, "EI"); break;
          case 0xfc: std::cout << getHexString(instruction, "CM", 3, true); break;		
          case 0xfd: std::cout << getHexString(instruction, "CALL", 3, true); break;	
          case 0xfe: std::cout << getHexString(instruction, "CPI", 2); break;
          case 0xff: std::cout << getHexString(instruction, "RST 7"); break;
        }
    }
};

class Emulator {
  private:
    Disassemler d;
    State8080 state;

    void readIntoMemory (uint32_t address, std::string filePath) {
      std::ifstream file(filePath, std::ios::binary | std::ios::ate);

      if (!file.is_open()) {
        std::cerr << "error: Couldn't open file" << std::endl;
        exit(1);
      }

      std::streamsize size = file.tellg();
      file.seekg(0, std::ios::beg);

      std::vector<char> buffer(size);
      if (!file.read(buffer.data(), size)) {
          std::cerr << "error: Couldn't read file" << std::endl;
          exit(1);
      }
      // Copy the buffer into 'state.memory' starting from the specified address.
        std::memcpy(&state.memory[address], buffer.data(), size);
    }

    int parity(int x, int size) {
      int p = 0;
      x = (x & ((1 << size) - 1));
      
      for (int i = 0; i < size; i++) {
        if (x & 0x1) p++;
        x = x >> 1;
      }
      
      return (0 == (p & 0x1));
    }

    inline void zflag(uint8_t res) {
      state.cc.z = (res == 0);
    }

    inline void sflag(uint8_t res) {
      state.cc.s = (0x80 == (res & 0x80));
    }

    inline void pflag(uint8_t res) {
      state.cc.p = parity(res, 8);
    }

    inline void cyflag(uint32_t res) {
      state->cc.cy = ((res & 0xffff0000) > 0);
    }

  public:
    Emulator() {
      this->d = Disassemler(); // Create a disassembler

      this->readIntoMemory(0, "./roms/invaders.h");
      this->readIntoMemory(0x800, "./roms/invaders.g");
      this->readIntoMemory(0x1000, "./roms/invaders.f");
      this->readIntoMemory(0x1800, "./roms/invaders.e");
    }

    void UnimplementedInstruction () {
      std::cerr << "error: Unimplemented Instruction => ";
      this->d.disassemble(state.pc, state.memory);

      exit(1);
    }

    int exec() {
      unsigned char *instruction = &state.memory[state.pc];
      int opbytes = 1;

      switch(*instruction) {
        case 0x00: break;        
        case 0x01:
          state.c = instruction[1];
          state.b = instruction[2];
          opbytes = 3;
        case 0x05:
          {
            uint8_t res = state.b - 1;
            zflag(res); sflag(res); pflag(res);
            state.b = res;
          }
          break;
        case 0x06:
          {
            state.b = instruction[1];
            opbytes = 2;
          }
          break;
        case 0x09:
          {
            uint32_t hl = (state.h << 8) | state.l;
            uint32_t bc = (state.b << 8) | state.c;
            uint32_t res = hl + bc;

            state.h = (res & 0xff00) >> 8;
            state.l = res & 0xff;
            state->cc.cy = ((res & 0xffff0000) > 0);
          }
          break;
        case 0x0d:
          {
            uint8_t res = state.c - 1;
            zflag(res); sflag(res); pflag(res);
            state.c = res;
          }
          break;
        case 0x0e:
          state.c = instruction[1];
          opbytes = 2;
          break;
        case 0x0f:
          {
            uint8_t x = state.a;
            state->a = ((x & 1) << 7) | (x >> 1);
            state->cc.cy = (1 == (x&1));
          }
          break;

        default: UnimplementedInstruction();
      }

      state.pc += opbytes;
      return 0;
    }

    void start() {
      int done = 0;

      while (done == 0) {
        this->d.disassemble(state.pc, state.memory);
        done = this->exec();
      }
    }
};

int main() {
  Emulator emulator;
  emulator.start();
}