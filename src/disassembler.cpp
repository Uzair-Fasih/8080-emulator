#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

class Disassemler {
  private:
    std::vector<char> hexdump;

    std::string getHexString(int &pc, std::vector<char>::iterator &it, std::string opcode, int opbytes = 1, bool isAddress = false) {
      std::stringstream res;
      res << opcode;

      if (opbytes > 1) {
        res << (isAddress ? " $" : ", #$");
      }

      if (opbytes == 3) {
        unsigned char op2 = *it++, op1 = *it++;
        res << std::hex << std::setw(2) << std::setfill('0') << (op1 & 0xFF);
        res << std::hex << std::setw(2) << std::setfill('0') << (op2 & 0xFF);
      } else if (opbytes == 2) {
        unsigned char op = *it++;
        res << std::hex << std::setw(2) << std::setfill('0') << (op & 0xFF);
      }

      res << '\n';

      pc += opbytes;
      return res.str();
    }

  public:
    Disassemler(std::ifstream &infile, std::ofstream &outfile) {
      char c;
      while (infile.get(c)) hexdump.push_back(c & 0xFF);

      auto it = hexdump.begin();
      int pc = 0;
      while (it != hexdump.end()) {
        outfile << std::hex << std::setw(4) << std::setfill('0') << pc << " ";
        switch ((unsigned char) *it) {
          case 0x00: outfile << getHexString(pc, ++it, "NOP"); break;
          case 0x01: outfile << getHexString(pc, ++it, "LXI B", 3); break;
          case 0x02: outfile << getHexString(pc, ++it, "STAX B"); break;
          case 0x03: outfile << getHexString(pc, ++it, "INX B"); break;
          case 0x04: outfile << getHexString(pc, ++it, "INR B"); break;
          case 0x05: outfile << getHexString(pc, ++it, "DCR B"); break;
          case 0x06: outfile << getHexString(pc, ++it, "MVI B", 2); break;
          case 0x07: outfile << getHexString(pc, ++it, "RLC"); break;
          case 0x08: outfile << getHexString(pc, ++it, "NOP"); break;
          case 0x09: outfile << getHexString(pc, ++it, "DAD B"); break;
          case 0x10: outfile << getHexString(pc, ++it, "NOP"); break;
          case 0x0a: outfile << getHexString(pc, ++it, "LDAX B"); break;
          case 0x0b: outfile << getHexString(pc, ++it, "DCX B"); break;
          case 0x0c: outfile << getHexString(pc, ++it, "INR C"); break;
          case 0x0d: outfile << getHexString(pc, ++it, "DCR C"); break;
          case 0x0e: outfile << getHexString(pc, ++it, "MVI C", 2); break;
          case 0x0f: outfile << getHexString(pc, ++it, "RRC", 1); break;
          case 0x11: outfile << getHexString(pc, ++it, "LXI D", 3); break;
          case 0x12: outfile << getHexString(pc, ++it, "STAX D"); break;
          case 0x13: outfile << getHexString(pc, ++it, "INX D"); break;
          case 0x14: outfile << getHexString(pc, ++it, "INR D"); break;
          case 0x15: outfile << getHexString(pc, ++it, "DCR D"); break;
          case 0x16: outfile << getHexString(pc, ++it, "MVI D", 2); break;
          case 0x17: outfile << getHexString(pc, ++it, "RAL"); break;
          case 0x18: outfile << getHexString(pc, ++it, "NOP"); break;
          case 0x19: outfile << getHexString(pc, ++it, "DAD D"); break;
          case 0x1a: outfile << getHexString(pc, ++it, "LDAX D"); break;
          case 0x1b: outfile << getHexString(pc, ++it, "DCX D"); break;
          case 0x1c: outfile << getHexString(pc, ++it, "INR E"); break;
          case 0x1d: outfile << getHexString(pc, ++it, "DCR E"); break;
          case 0x1e: outfile << getHexString(pc, ++it, "MVI E", 2); break;
          case 0x1f: outfile << getHexString(pc, ++it, "RAR"); break;
          case 0x21: outfile << getHexString(pc, ++it, "LXI H", 3); break;
          case 0x22: outfile << getHexString(pc, ++it, "SHLD", 3, true); break;
          case 0x23: outfile << getHexString(pc, ++it, "INX H"); break;
          case 0x24: outfile << getHexString(pc, ++it, "INR H"); break;
          case 0x25: outfile << getHexString(pc, ++it, "DCR H"); break;
          case 0x26: outfile << getHexString(pc, ++it, "MVI H", 2); break;
          case 0x27: outfile << getHexString(pc, ++it, "DAA"); break;
          case 0x28: outfile << getHexString(pc, ++it, "NOP"); break;
          case 0x29: outfile << getHexString(pc, ++it, "DAD H"); break;
          case 0x2a: outfile << getHexString(pc, ++it, "LHLD", 3, true); break;
          case 0x2b: outfile << getHexString(pc, ++it, "DCX H"); break;
          case 0x2c: outfile << getHexString(pc, ++it, "INR L"); break;
          case 0x2d: outfile << getHexString(pc, ++it, "DCR L"); break;
          case 0x2e: outfile << getHexString(pc, ++it, "MVI L", 2); break;
          case 0x2f: outfile << getHexString(pc, ++it, "CMA"); break;
          case 0x31: outfile << getHexString(pc, ++it, "LXI SP", 3); break;
          case 0x32: outfile << getHexString(pc, ++it, "STA", 3, true); break;
          case 0x33: outfile << getHexString(pc, ++it, "INX SP"); break;
          case 0x34: outfile << getHexString(pc, ++it, "INR M"); break;
          case 0x35: outfile << getHexString(pc, ++it, "DCR M"); break;
          case 0x36: outfile << getHexString(pc, ++it, "MVI M", 2); break;
          case 0x37: outfile << getHexString(pc, ++it, "STC"); break;
          case 0x38: outfile << getHexString(pc, ++it, "NOP"); break;
          case 0x39: outfile << getHexString(pc, ++it, "DAD SP"); break;
          case 0x3a: outfile << getHexString(pc, ++it, "LDA", 3, true); break;
          case 0x3b: outfile << getHexString(pc, ++it, "DCX SP"); break;
          case 0x3c: outfile << getHexString(pc, ++it, "INR A"); break;
          case 0x3d: outfile << getHexString(pc, ++it, "DCR A"); break;
          case 0x3e: outfile << getHexString(pc, ++it, "MVI A", 2); break;
          case 0x3f: outfile << getHexString(pc, ++it, "CMC"); break;
          case 0x40: outfile << getHexString(pc, ++it, "MOV B,B"); break;
          case 0x41: outfile << getHexString(pc, ++it, "MOV B,C"); break;
          case 0x42: outfile << getHexString(pc, ++it, "MOV B,D"); break;
          case 0x43: outfile << getHexString(pc, ++it, "MOV B,E"); break;
          case 0x44: outfile << getHexString(pc, ++it, "MOV B,H"); break;
          case 0x45: outfile << getHexString(pc, ++it, "MOV B,L"); break;
          case 0x46: outfile << getHexString(pc, ++it, "MOV B,M"); break;
          case 0x47: outfile << getHexString(pc, ++it, "MOV B,A"); break;
          case 0x48: outfile << getHexString(pc, ++it, "MOV C,B"); break;
          case 0x49: outfile << getHexString(pc, ++it, "MOV C,C"); break;
          case 0x4a: outfile << getHexString(pc, ++it, "MOV C,D"); break;
          case 0x4b: outfile << getHexString(pc, ++it, "MOV C,E"); break;
          case 0x4c: outfile << getHexString(pc, ++it, "MOV C,H"); break;
          case 0x4d: outfile << getHexString(pc, ++it, "MOV C,L"); break;
          case 0x4e: outfile << getHexString(pc, ++it, "MOV C,M"); break;
          case 0x4f: outfile << getHexString(pc, ++it, "MOV C,A"); break;
          case 0x50: outfile << getHexString(pc, ++it, "MOV D,B"); break;
          case 0x51: outfile << getHexString(pc, ++it, "MOV D,C"); break;
          case 0x52: outfile << getHexString(pc, ++it, "MOV D,D"); break;
          case 0x53: outfile << getHexString(pc, ++it, "MOV D,E"); break;
          case 0x54: outfile << getHexString(pc, ++it, "MOV D,H"); break;
          case 0x55: outfile << getHexString(pc, ++it, "MOV D,L"); break;
          case 0x56: outfile << getHexString(pc, ++it, "MOV D,M"); break;
          case 0x57: outfile << getHexString(pc, ++it, "MOV D,A"); break;
          case 0x58: outfile << getHexString(pc, ++it, "MOV E,B"); break;
          case 0x59: outfile << getHexString(pc, ++it, "MOV E,C"); break;
          case 0x5a: outfile << getHexString(pc, ++it, "MOV E,D"); break;
          case 0x5b: outfile << getHexString(pc, ++it, "MOV E,E"); break;
          case 0x5c: outfile << getHexString(pc, ++it, "MOV E,H"); break;
          case 0x5d: outfile << getHexString(pc, ++it, "MOV E,L"); break;
          case 0x5e: outfile << getHexString(pc, ++it, "MOV E,M"); break;
          case 0x5f: outfile << getHexString(pc, ++it, "MOV E,A"); break;
          case 0x60: outfile << getHexString(pc, ++it, "MOV H,B"); break;
          case 0x61: outfile << getHexString(pc, ++it, "MOV H,C"); break;
          case 0x62: outfile << getHexString(pc, ++it, "MOV H,D"); break;
          case 0x63: outfile << getHexString(pc, ++it, "MOV H,E"); break;
          case 0x64: outfile << getHexString(pc, ++it, "MOV H,H"); break;
          case 0x65: outfile << getHexString(pc, ++it, "MOV H,L"); break;
          case 0x66: outfile << getHexString(pc, ++it, "MOV H,M"); break;
          case 0x67: outfile << getHexString(pc, ++it, "MOV H,A"); break;
          case 0x68: outfile << getHexString(pc, ++it, "MOV L,B"); break;
          case 0x69: outfile << getHexString(pc, ++it, "MOV L,C"); break;
          case 0x6a: outfile << getHexString(pc, ++it, "MOV L,D"); break;
          case 0x6b: outfile << getHexString(pc, ++it, "MOV L,E"); break;
          case 0x6c: outfile << getHexString(pc, ++it, "MOV L,H"); break;
          case 0x6d: outfile << getHexString(pc, ++it, "MOV L,L"); break;
          case 0x6e: outfile << getHexString(pc, ++it, "MOV L,M"); break;
          case 0x6f: outfile << getHexString(pc, ++it, "MOV L,A"); break;
          case 0x70: outfile << getHexString(pc, ++it, "MOV M,B"); break;
          case 0x71: outfile << getHexString(pc, ++it, "MOV M,C"); break;
          case 0x72: outfile << getHexString(pc, ++it, "MOV M,D"); break;
          case 0x73: outfile << getHexString(pc, ++it, "MOV M,E"); break;
          case 0x74: outfile << getHexString(pc, ++it, "MOV M,H"); break;
          case 0x75: outfile << getHexString(pc, ++it, "MOV M,L"); break;
          case 0x76: outfile << getHexString(pc, ++it, "HLT"); break;
          case 0x77: outfile << getHexString(pc, ++it, "MOV M,A"); break;
          case 0x78: outfile << getHexString(pc, ++it, "MOV A,B"); break;
          case 0x79: outfile << getHexString(pc, ++it, "MOV A,C"); break;
          case 0x7a: outfile << getHexString(pc, ++it, "MOV A,D"); break;
          case 0x7b: outfile << getHexString(pc, ++it, "MOV A,E"); break;
          case 0x7c: outfile << getHexString(pc, ++it, "MOV A,H"); break;
          case 0x7d: outfile << getHexString(pc, ++it, "MOV A,L"); break;
          case 0x7e: outfile << getHexString(pc, ++it, "MOV A,M"); break;
          case 0x7f: outfile << getHexString(pc, ++it, "MOV A,A"); break;
          case 0x80: outfile << getHexString(pc, ++it, "ADD B"); break;
          case 0x81: outfile << getHexString(pc, ++it, "ADD C"); break;
          case 0x82: outfile << getHexString(pc, ++it, "ADD D"); break;
          case 0x83: outfile << getHexString(pc, ++it, "ADD E"); break;
          case 0x84: outfile << getHexString(pc, ++it, "ADD H"); break;
          case 0x85: outfile << getHexString(pc, ++it, "ADD L"); break;
          case 0x86: outfile << getHexString(pc, ++it, "ADD M"); break;
          case 0x87: outfile << getHexString(pc, ++it, "ADD A"); break;
          case 0x88: outfile << getHexString(pc, ++it, "ADC B"); break;
          case 0x89: outfile << getHexString(pc, ++it, "ADC C"); break;
          case 0x8a: outfile << getHexString(pc, ++it, "ADC D"); break;
          case 0x8b: outfile << getHexString(pc, ++it, "ADC E"); break;
          case 0x8c: outfile << getHexString(pc, ++it, "ADC H"); break;
          case 0x8d: outfile << getHexString(pc, ++it, "ADC L"); break;
          case 0x8e: outfile << getHexString(pc, ++it, "ADC M"); break;
          case 0x8f: outfile << getHexString(pc, ++it, "ADC A"); break;
          case 0x90: outfile << getHexString(pc, ++it, "SUB B"); break;
          case 0x91: outfile << getHexString(pc, ++it, "SUB C"); break;
          case 0x92: outfile << getHexString(pc, ++it, "SUB D"); break;
          case 0x93: outfile << getHexString(pc, ++it, "SUB E"); break;
          case 0x94: outfile << getHexString(pc, ++it, "SUB H"); break;
          case 0x95: outfile << getHexString(pc, ++it, "SUB L"); break;
          case 0x96: outfile << getHexString(pc, ++it, "SUB M"); break;
          case 0x97: outfile << getHexString(pc, ++it, "SUB A"); break;
          case 0x98: outfile << getHexString(pc, ++it, "SBB B"); break;
          case 0x99: outfile << getHexString(pc, ++it, "SBB C"); break;
          case 0x9a: outfile << getHexString(pc, ++it, "SBB D"); break;
          case 0x9b: outfile << getHexString(pc, ++it, "SBB E"); break;
          case 0x9c: outfile << getHexString(pc, ++it, "SBB H"); break;
          case 0x9d: outfile << getHexString(pc, ++it, "SBB L"); break;
          case 0x9e: outfile << getHexString(pc, ++it, "SBB M"); break;
          case 0x9f: outfile << getHexString(pc, ++it, "SBB A"); break;
          case 0xa0: outfile << getHexString(pc, ++it, "ANA B"); break;
          case 0xa1: outfile << getHexString(pc, ++it, "ANA C"); break;
          case 0xa2: outfile << getHexString(pc, ++it, "ANA D"); break;
          case 0xa3: outfile << getHexString(pc, ++it, "ANA E"); break;
          case 0xa4: outfile << getHexString(pc, ++it, "ANA H"); break;
          case 0xa5: outfile << getHexString(pc, ++it, "ANA L"); break;
          case 0xa6: outfile << getHexString(pc, ++it, "ANA M"); break;
          case 0xa7: outfile << getHexString(pc, ++it, "ANA A"); break;
          case 0xa8: outfile << getHexString(pc, ++it, "XRA B"); break;
          case 0xa9: outfile << getHexString(pc, ++it, "XRA C"); break;
          case 0xaa: outfile << getHexString(pc, ++it, "XRA D"); break;
          case 0xab: outfile << getHexString(pc, ++it, "XRA E"); break;
          case 0xac: outfile << getHexString(pc, ++it, "XRA H"); break;
          case 0xad: outfile << getHexString(pc, ++it, "XRA L"); break;
          case 0xae: outfile << getHexString(pc, ++it, "XRA M"); break;
          case 0xaf: outfile << getHexString(pc, ++it, "XRA A"); break;
          case 0xb0: outfile << getHexString(pc, ++it, "ORA B"); break;
          case 0xb1: outfile << getHexString(pc, ++it, "ORA C"); break;
          case 0xb2: outfile << getHexString(pc, ++it, "ORA D"); break;
          case 0xb3: outfile << getHexString(pc, ++it, "ORA E"); break;
          case 0xb4: outfile << getHexString(pc, ++it, "ORA H"); break;
          case 0xb5: outfile << getHexString(pc, ++it, "ORA L"); break;
          case 0xb6: outfile << getHexString(pc, ++it, "ORA M"); break;
          case 0xb7: outfile << getHexString(pc, ++it, "ORA A"); break;
          case 0xb8: outfile << getHexString(pc, ++it, "CMP B"); break;
          case 0xb9: outfile << getHexString(pc, ++it, "CMP C"); break;
          case 0xba: outfile << getHexString(pc, ++it, "CMP D"); break;
          case 0xbb: outfile << getHexString(pc, ++it, "CMP E"); break;
          case 0xbc: outfile << getHexString(pc, ++it, "CMP H"); break;
          case 0xbd: outfile << getHexString(pc, ++it, "CMP L"); break;
          case 0xbe: outfile << getHexString(pc, ++it, "CMP M"); break;
          case 0xbf: outfile << getHexString(pc, ++it, "CMP A"); break;
          case 0xc0: outfile << getHexString(pc, ++it, "RNZ"); break;
          case 0xc1: outfile << getHexString(pc, ++it, "POP B"); break;
          case 0xc2: outfile << getHexString(pc, ++it, "JNZ", 3, true); break;
          case 0xc3: outfile << getHexString(pc, ++it, "JMP", 3, true); break;
          case 0xc4: outfile << getHexString(pc, ++it, "CNZ", 3, true); break;
          case 0xc5: outfile << getHexString(pc, ++it, "PUSH B"); break;
          case 0xc6: outfile << getHexString(pc, ++it, "ADI", 2); break;
          case 0xc7: outfile << getHexString(pc, ++it, "RST 0"); break;
          case 0xc8: outfile << getHexString(pc, ++it, "RZ"); break;
          case 0xc9: outfile << getHexString(pc, ++it, "RET"); break;
          case 0xca: outfile << getHexString(pc, ++it, "JZ", 3, true); break;
          case 0xcb: outfile << getHexString(pc, ++it, "JUMP", 3, true); break;
          case 0xcc: outfile << getHexString(pc, ++it, "CZ", 3, true); break;
          case 0xcd: outfile << getHexString(pc, ++it, "CALL", 3, true); break;
          case 0xce: outfile << getHexString(pc, ++it, "ACI", 2); break;
          case 0xcf: outfile << getHexString(pc, ++it, "RST 1"); break;
          case 0xd0: outfile << getHexString(pc, ++it, "RNC"); break;
          case 0xd1: outfile << getHexString(pc, ++it, "POP D"); break;
          case 0xd2: outfile << getHexString(pc, ++it, "JNC", 3, true); break;
          case 0xd3: outfile << getHexString(pc, ++it, "OUT", 2); break;
          case 0xd4: outfile << getHexString(pc, ++it, "CNC", 3, true); break;
          case 0xd5: outfile << getHexString(pc, ++it, "PUSH D"); break;
          case 0xd6: outfile << getHexString(pc, ++it, "SUI", 2); break;
          case 0xd7: outfile << getHexString(pc, ++it, "RST 2"); break;
          case 0xd8: outfile << getHexString(pc, ++it, "RC"); break;
          case 0xd9: outfile << getHexString(pc, ++it, "RET"); break;
          case 0xda: outfile << getHexString(pc, ++it, "JC", 3, true); break;
          case 0xdb: outfile << getHexString(pc, ++it, "IN", 2); break;
          case 0xdc: outfile << getHexString(pc, ++it, "CC", 3, true); break;
		      case 0xdd: outfile << getHexString(pc, ++it, "CALL", 3, true); break;
          case 0xde: outfile << getHexString(pc, ++it, "SBI", 2); break;
          case 0xdf: outfile << getHexString(pc, ++it, "RST 3"); break;
          case 0xe0: outfile << getHexString(pc, ++it, "RPO"); break;
          case 0xe1: outfile << getHexString(pc, ++it, "POP H"); break;
          case 0xe2: outfile << getHexString(pc, ++it, "JPO", 3, true); break;
          case 0xe3: outfile << getHexString(pc, ++it, "XTHL"); break;
          case 0xe4: outfile << getHexString(pc, ++it, "CPO", 3, true); break;
          case 0xe5: outfile << getHexString(pc, ++it, "PUSH H"); break;
          case 0xe6: outfile << getHexString(pc, ++it, "ANI", 2); break;
          case 0xe7: outfile << getHexString(pc, ++it, "RST 4"); break;
          case 0xe8: outfile << getHexString(pc, ++it, "RPE"); break;
          case 0xe9: outfile << getHexString(pc, ++it, "PCHL"); break;
          case 0xea: outfile << getHexString(pc, ++it, "JPE", 3, true); break;
          case 0xeb: outfile << getHexString(pc, ++it, "XCHG"); break;
          case 0xec: outfile << getHexString(pc, ++it, "CPE", 3, true); break;
          case 0xed: outfile << getHexString(pc, ++it, "CALL", 2); break;
          case 0xee: outfile << getHexString(pc, ++it, "XRI", 2); break;
          case 0xef: outfile << getHexString(pc, ++it, "RST 5"); break;
          case 0xf0: outfile << getHexString(pc, ++it, "RP"); break;
          case 0xf1: outfile << getHexString(pc, ++it, "POP PSW"); break;
          case 0xf2: outfile << getHexString(pc, ++it, "JP", 3, true); break;
          case 0xf3: outfile << getHexString(pc, ++it, "DI"); break;
          case 0xf4: outfile << getHexString(pc, ++it, "CP", 3, true); break;
          case 0xf5: outfile << getHexString(pc, ++it, "PUSH PSW"); break;
          case 0xf6: outfile << getHexString(pc, ++it, "ORI", 2); break;
          case 0xf7: outfile << getHexString(pc, ++it, "RST 6"); break;
          case 0xf8: outfile << getHexString(pc, ++it, "RM"); break;
          case 0xf9: outfile << getHexString(pc, ++it, "SPHL"); break;
          case 0xfa: outfile << getHexString(pc, ++it, "JM", 3, true); break;
          case 0xfb: outfile << getHexString(pc, ++it, "EI"); break;
          case 0xfc: outfile << getHexString(pc, ++it, "CM", 3, true); break;		
          case 0xfd: outfile << getHexString(pc, ++it, "CALL", 3, true); break;	
          case 0xfe: outfile << getHexString(pc, ++it, "CPI", 2); break;
          case 0xff: outfile << getHexString(pc, ++it, "RST 7"); break;
          default: it++;
        }
      }
    }
};

int main() {
  std::ifstream infile("./roms/space-invaders.rom", std::ios::binary);
  std::ofstream outfile("./out/disassembly.txt");

  if (!infile.is_open()) std::cerr << "Unable to open input file" << std::endl;
  Disassemler disassembler(infile, outfile);
}