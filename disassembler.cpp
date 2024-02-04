#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

class Disassemler {
private:
  std::vector<char> hexdump;

  std::string getHexString(int& idx, std::string ins, int opbytes = 1, bool isAddress = false) {
    std::stringstream ss;

    ss << ins;
    if (opbytes > 1) ss << ", " << (isAddress ? "$" : "#0x");
    if (opbytes > 2) ss << std::hex << std::setw(2) << std::setfill('0') << (hexdump[idx + 2] & 0xFF);
    if (opbytes > 1) ss << std::hex << std::setw(2) << std::setfill('0') << (hexdump[idx + 1] & 0xFF);
    ss << "\n";

    idx += (opbytes - 1);

    return ss.str();
  }

public:
  Disassemler(std::ifstream & infile) {
    char c;
    while (infile.get(c)) hexdump.push_back(c & 0xFF);
  }

  void translateToOpCode(std::ofstream & outfile) {
    // Using the OpCode mapping for Intel 8080, we translate the hex to assembly
    for (int idx = 0; idx < hexdump.size(); idx++) {
      switch ((unsigned char) hexdump[idx]) {
        case 0x00: outfile << getHexString(idx, "NOP"); break;
        case 0x01: outfile << getHexString(idx, "LXI B", 3); break;
        case 0x02: outfile << getHexString(idx, "STAX B"); break;
        case 0x03: outfile << getHexString(idx, "INX B"); break;
        case 0x04: outfile << getHexString(idx, "INR B"); break;
        case 0x05: outfile << getHexString(idx, "DCR B"); break;
        case 0x06: outfile << getHexString(idx, "MVI B", 2); break;
        case 0x07: outfile << getHexString(idx, "RLC"); break;
        case 0x09: outfile << getHexString(idx, "DAD B"); break;
        case 0x0a: outfile << getHexString(idx, "LDAX B"); break;
        case 0x0b: outfile << getHexString(idx, "DCX B"); break;
        case 0x0c: outfile << getHexString(idx, "INR C"); break;
        case 0x0d: outfile << getHexString(idx, "DCR C"); break;
        case 0x0e: outfile << getHexString(idx, "MVI C", 2); break;
        case 0x0f: outfile << getHexString(idx, "RRC", 1); break;
        case 0x11: outfile << getHexString(idx, "LXI D", 3); break;
        case 0x12: outfile << getHexString(idx, "STAX D"); break;
        case 0x13: outfile << getHexString(idx, "INX D"); break;
        case 0x14: outfile << getHexString(idx, "INR D"); break;
        case 0x15: outfile << getHexString(idx, "DCR D"); break;
        case 0x16: outfile << getHexString(idx, "MVI D", 2); break;
        case 0x17: outfile << getHexString(idx, "RAL"); break;
        case 0x19: outfile << getHexString(idx, "DAD D"); break;
        case 0x1a: outfile << getHexString(idx, "LDAX D"); break;
        case 0x1b: outfile << getHexString(idx, "DCX D"); break;
        case 0x1c: outfile << getHexString(idx, "INR E"); break;
        case 0x1d: outfile << getHexString(idx, "DCR E"); break;
        case 0x1e: outfile << getHexString(idx, "MVI E",	2); break;
        case 0x1f: outfile << getHexString(idx, "RAR"); break;
        case 0x21: outfile << getHexString(idx, "LXI H", 3); break;
        case 0x22: outfile << getHexString(idx, "SHLD", 3, true); break;
        case 0x23: outfile << getHexString(idx, "INX H"); break;
        case 0x24: outfile << getHexString(idx, "INR H"); break;
        case 0x25: outfile << getHexString(idx, "DCR H"); break;
        case 0x26: outfile << getHexString(idx, "MVI H", 2); break;
        case 0x27: outfile << getHexString(idx, "DAA"); break;		
        case 0x29: outfile << getHexString(idx, "DAD H"); break;
        case 0x2a: outfile << getHexString(idx, "LHLD", 3, true); break;
        case 0x2b: outfile << getHexString(idx, "DCX H"); break;
        case 0x2c: outfile << getHexString(idx, "INR L"); break;
        case 0x2d: outfile << getHexString(idx, "DCR L"); break;
        case 0x2e: outfile << getHexString(idx, "MVI L", 2); break;
        case 0x2f: outfile << getHexString(idx, "CMA"); break;
        case 0x31: outfile << getHexString(idx, "LXI SP", 3); break;
        case 0x32: outfile << getHexString(idx, "STA", 3, true); break;
        case 0x33: outfile << getHexString(idx, "INX SP"); break;
        case 0x34: outfile << getHexString(idx, "INR M"); break;
        case 0x35: outfile << getHexString(idx, "DCR M"); break;
        case 0x36: outfile << getHexString(idx, "MVI M", 2); break;
        case 0x37: outfile << getHexString(idx, "STC"); break;
        case 0x39: outfile << getHexString(idx, "DAD SP"); break;
        case 0x3a: outfile << getHexString(idx, "LDA", 3, true); break;
        case 0x3b: outfile << getHexString(idx, "DCX SP"); break;
        case 0x3c: outfile << getHexString(idx, "INR A"); break;
        case 0x3d: outfile << getHexString(idx, "DCR A"); break;
        case 0x3e: outfile << getHexString(idx, "MVI A", 2); break;
        case 0x3f: outfile << getHexString(idx, "CMC"); break;
        case 0x40: outfile << getHexString(idx, "MOV B,B"); break;
        case 0x41: outfile << getHexString(idx, "MOV B,C"); break;
        case 0x42: outfile << getHexString(idx, "MOV B,D"); break;
        case 0x43: outfile << getHexString(idx, "MOV B,E"); break;
        case 0x44: outfile << getHexString(idx, "MOV B,H"); break;
        case 0x45: outfile << getHexString(idx, "MOV B,L"); break;
        case 0x46: outfile << getHexString(idx, "MOV B,M"); break;
        case 0x47: outfile << getHexString(idx, "MOV B,A"); break;
        case 0x48: outfile << getHexString(idx, "MOV C,B"); break;
        case 0x49: outfile << getHexString(idx, "MOV C,C"); break;
        case 0x4a: outfile << getHexString(idx, "MOV C,D"); break;
        case 0x4b: outfile << getHexString(idx, "MOV C,E"); break;
        case 0x4c: outfile << getHexString(idx, "MOV C,H"); break;
        case 0x4d: outfile << getHexString(idx, "MOV C,L"); break;
        case 0x4e: outfile << getHexString(idx, "MOV C,M"); break;
        case 0x4f: outfile << getHexString(idx, "MOV C,A"); break;
        case 0x50: outfile << getHexString(idx, "MOV D,B"); break;
        case 0x51: outfile << getHexString(idx, "MOV D,C"); break;
        case 0x52: outfile << getHexString(idx, "MOV D,D"); break;
        case 0x53: outfile << getHexString(idx, "MOV D,E"); break;
        case 0x54: outfile << getHexString(idx, "MOV D,H"); break;
        case 0x55: outfile << getHexString(idx, "MOV D,L"); break;
        case 0x56: outfile << getHexString(idx, "MOV D,M"); break;
        case 0x57: outfile << getHexString(idx, "MOV D,A"); break;
        case 0x58: outfile << getHexString(idx, "MOV E,B"); break;
        case 0x59: outfile << getHexString(idx, "MOV E,C"); break;
        case 0x5a: outfile << getHexString(idx, "MOV E,D"); break;
        case 0x5b: outfile << getHexString(idx, "MOV E,E"); break;
        case 0x5c: outfile << getHexString(idx, "MOV E,H"); break;
        case 0x5d: outfile << getHexString(idx, "MOV E,L"); break;
        case 0x5e: outfile << getHexString(idx, "MOV E,M"); break;
        case 0x5f: outfile << getHexString(idx, "MOV E,A"); break;
        case 0x60: outfile << getHexString(idx, "MOV H,B"); break;
        case 0x61: outfile << getHexString(idx, "MOV H,C"); break;
        case 0x62: outfile << getHexString(idx, "MOV H,D"); break;
        case 0x63: outfile << getHexString(idx, "MOV H,E"); break;
        case 0x64: outfile << getHexString(idx, "MOV H,H"); break;
        case 0x65: outfile << getHexString(idx, "MOV H,L"); break;
        case 0x66: outfile << getHexString(idx, "MOV H,M"); break;
        case 0x67: outfile << getHexString(idx, "MOV H,A"); break;
        case 0x68: outfile << getHexString(idx, "MOV L,B"); break;
        case 0x69: outfile << getHexString(idx, "MOV L,C"); break;
        case 0x6a: outfile << getHexString(idx, "MOV L,D"); break;
        case 0x6b: outfile << getHexString(idx, "MOV L,E"); break;
        case 0x6c: outfile << getHexString(idx, "MOV L,H"); break;
        case 0x6d: outfile << getHexString(idx, "MOV L,L"); break;
        case 0x6e: outfile << getHexString(idx, "MOV L,M"); break;
        case 0x6f: outfile << getHexString(idx, "MOV L,A"); break;
        case 0x70: outfile << getHexString(idx, "MOV M,B"); break;
        case 0x71: outfile << getHexString(idx, "MOV M,C"); break;
        case 0x72: outfile << getHexString(idx, "MOV M,D"); break;
        case 0x73: outfile << getHexString(idx, "MOV M,E"); break;
        case 0x74: outfile << getHexString(idx, "MOV M,H"); break;
        case 0x75: outfile << getHexString(idx, "MOV M,L"); break;
        case 0x76: outfile << getHexString(idx, "HLT"); break;
        case 0x77: outfile << getHexString(idx, "MOV M,A"); break;
        case 0x78: outfile << getHexString(idx, "MOV A,B"); break;
        case 0x79: outfile << getHexString(idx, "MOV A,C"); break;
        case 0x7a: outfile << getHexString(idx, "MOV A,D"); break;
        case 0x7b: outfile << getHexString(idx, "MOV A,E"); break;
        case 0x7c: outfile << getHexString(idx, "MOV A,H"); break;
        case 0x7d: outfile << getHexString(idx, "MOV A,L"); break;
        case 0x7e: outfile << getHexString(idx, "MOV A,M"); break;
        case 0x7f: outfile << getHexString(idx, "MOV A,A"); break;
        case 0x80: outfile << getHexString(idx, "ADD B"); break;
        case 0x81: outfile << getHexString(idx, "ADD C"); break;
        case 0x82: outfile << getHexString(idx, "ADD D"); break;
        case 0x83: outfile << getHexString(idx, "ADD E"); break;
        case 0x84: outfile << getHexString(idx, "ADD H"); break;
        case 0x85: outfile << getHexString(idx, "ADD L"); break;
        case 0x86: outfile << getHexString(idx, "ADD M"); break;
        case 0x87: outfile << getHexString(idx, "ADD A"); break;
        case 0x88: outfile << getHexString(idx, "ADC B"); break;
        case 0x89: outfile << getHexString(idx, "ADC C"); break;
        case 0x8a: outfile << getHexString(idx, "ADC D"); break;
        case 0x8b: outfile << getHexString(idx, "ADC E"); break;
        case 0x8c: outfile << getHexString(idx, "ADC H"); break;
        case 0x8d: outfile << getHexString(idx, "ADC L"); break;
        case 0x8e: outfile << getHexString(idx, "ADC M"); break;
        case 0x8f: outfile << getHexString(idx, "ADC A"); break;
        case 0x90: outfile << getHexString(idx, "SUB B"); break;
        case 0x91: outfile << getHexString(idx, "SUB C"); break;
        case 0x92: outfile << getHexString(idx, "SUB D"); break;
        case 0x93: outfile << getHexString(idx, "SUB E"); break;
        case 0x94: outfile << getHexString(idx, "SUB H"); break;
        case 0x95: outfile << getHexString(idx, "SUB L"); break;
        case 0x96: outfile << getHexString(idx, "SUB M"); break;
        case 0x97: outfile << getHexString(idx, "SUB A"); break;
        case 0x98: outfile << getHexString(idx, "SBB B"); break;
        case 0x99: outfile << getHexString(idx, "SBB C"); break;
        case 0x9a: outfile << getHexString(idx, "SBB D"); break;
        case 0x9b: outfile << getHexString(idx, "SBB E"); break;
        case 0x9c: outfile << getHexString(idx, "SBB H"); break;
        case 0x9d: outfile << getHexString(idx, "SBB L"); break;
        case 0x9e: outfile << getHexString(idx, "SBB M"); break;
        case 0x9f: outfile << getHexString(idx, "SBB A"); break;
        case 0xa0: outfile << getHexString(idx, "ANA B"); break;
        case 0xa1: outfile << getHexString(idx, "ANA C"); break;
        case 0xa2: outfile << getHexString(idx, "ANA D"); break;
        case 0xa3: outfile << getHexString(idx, "ANA E"); break;
        case 0xa4: outfile << getHexString(idx, "ANA H"); break;
        case 0xa5: outfile << getHexString(idx, "ANA L"); break;
        case 0xa6: outfile << getHexString(idx, "ANA M"); break;
        case 0xa7: outfile << getHexString(idx, "ANA A"); break;
        case 0xa8: outfile << getHexString(idx, "XRA B"); break;
        case 0xa9: outfile << getHexString(idx, "XRA C"); break;
        case 0xaa: outfile << getHexString(idx, "XRA D"); break;
        case 0xab: outfile << getHexString(idx, "XRA E"); break;
        case 0xac: outfile << getHexString(idx, "XRA H"); break;
        case 0xad: outfile << getHexString(idx, "XRA L"); break;
        case 0xae: outfile << getHexString(idx, "XRA M"); break;
        case 0xaf: outfile << getHexString(idx, "XRA A"); break;
        case 0xb0: outfile << getHexString(idx, "ORA B"); break;
        case 0xb1: outfile << getHexString(idx, "ORA C"); break;
        case 0xb2: outfile << getHexString(idx, "ORA D"); break;
        case 0xb3: outfile << getHexString(idx, "ORA E"); break;
        case 0xb4: outfile << getHexString(idx, "ORA H"); break;
        case 0xb5: outfile << getHexString(idx, "ORA L"); break;
        case 0xb6: outfile << getHexString(idx, "ORA M"); break;
        case 0xb7: outfile << getHexString(idx, "ORA A"); break;
        case 0xb8: outfile << getHexString(idx, "CMP B"); break;
        case 0xb9: outfile << getHexString(idx, "CMP C"); break;
        case 0xba: outfile << getHexString(idx, "CMP D"); break;
        case 0xbb: outfile << getHexString(idx, "CMP E"); break;
        case 0xbc: outfile << getHexString(idx, "CMP H"); break;
        case 0xbd: outfile << getHexString(idx, "CMP L"); break;
        case 0xbe: outfile << getHexString(idx, "CMP M"); break;
        case 0xbf: outfile << getHexString(idx, "CMP A"); break;
        case 0xc0: outfile << getHexString(idx, "RNZ"); break;
        case 0xc1: outfile << getHexString(idx, "POP B"); break;
        case 0xc2: outfile << getHexString(idx, "JNZ", 3, true); break;
        case 0xc3: outfile << getHexString(idx, "JMP", 3, true); break;
        case 0xc4: outfile << getHexString(idx, "CNZ", 3, true); break;
        case 0xc5: outfile << getHexString(idx, "PUSH B"); break;
        case 0xc6: outfile << getHexString(idx, "ADI D8"); break;
        case 0xc7: outfile << getHexString(idx, "RST 0"); break;
        case 0xc8: outfile << getHexString(idx, "RZ"); break;
        case 0xc9: outfile << getHexString(idx, "RET"); break;
        case 0xca: outfile << getHexString(idx, "JZ", 3, true); break;
        case 0xcc: outfile << getHexString(idx, "CZ", 3, true); break;
        case 0xcd: outfile << getHexString(idx, "CALL", 3, true); break;
        case 0xce: outfile << getHexString(idx, "ACI", 2); break;
        case 0xcf: outfile << getHexString(idx, "RST 1"); break;
        case 0xd0: outfile << getHexString(idx, "RNC"); break;
        case 0xd1: outfile << getHexString(idx, "POP D"); break;
        case 0xd2: outfile << getHexString(idx, "JNC", 3, true); break;
        case 0xd3: outfile << getHexString(idx, "OUT", 2); break;
        case 0xd4: outfile << getHexString(idx, "CNC", 3, true); break;
        case 0xd5: outfile << getHexString(idx, "PUSH D"); break;
        case 0xd6: outfile << getHexString(idx, "SUI", 2); break;
        case 0xd7: outfile << getHexString(idx, "RST 2"); break;
        case 0xd8: outfile << getHexString(idx, "RC"); break;
        case 0xda: outfile << getHexString(idx, "JC", 3, true); break;
        case 0xdb: outfile << getHexString(idx, "IN", 2); break;
        case 0xdc: outfile << getHexString(idx, "CC", 3, true); break;
        case 0xde: outfile << getHexString(idx, "SBI", 2); break;
        case 0xdf: outfile << getHexString(idx, "RST 3"); break;
        case 0xe0: outfile << getHexString(idx, "RPO"); break;
        case 0xe1: outfile << getHexString(idx, "POP H"); break;
        case 0xe2: outfile << getHexString(idx, "JPO", 3, true); break;
        case 0xe3: outfile << getHexString(idx, "XTHL"); break;
        case 0xe4: outfile << getHexString(idx, "CPO", 3, true); break;
        case 0xe5: outfile << getHexString(idx, "PUSH H"); break;
        case 0xe6: outfile << getHexString(idx, "ANI", 2); break;
        case 0xe7: outfile << getHexString(idx, "RST 4"); break;
        case 0xe8: outfile << getHexString(idx, "RPE"); break;
        case 0xe9: outfile << getHexString(idx, "PCHL"); break;
        case 0xea: outfile << getHexString(idx, "JPE", 3, true); break;
        case 0xeb: outfile << getHexString(idx, "XCHG"); break;
        case 0xec: outfile << getHexString(idx, "CPE", 3, true); break;
        case 0xee: outfile << getHexString(idx, "XRI", 2); break;
        case 0xef: outfile << getHexString(idx, "RST 5"); break;
        case 0xf0: outfile << getHexString(idx, "RP"); break;
        case 0xf1: outfile << getHexString(idx, "POP PSW"); break;
        case 0xf2: outfile << getHexString(idx, "JP", 3, true); break;
        case 0xf3: outfile << getHexString(idx, "DI"); break;
        case 0xf4: outfile << getHexString(idx, "CP", 3, true); break;
        case 0xf5: outfile << getHexString(idx, "PUSH PSW"); break;
        case 0xf6: outfile << getHexString(idx, "ORI", 2); break;
        case 0xf7: outfile << getHexString(idx, "RST 6"); break;
        case 0xf8: outfile << getHexString(idx, "RM"); break;
        case 0xf9: outfile << getHexString(idx, "SPHL"); break;
        case 0xfa: outfile << getHexString(idx, "JM", 3, true); break;
        case 0xfb: outfile << getHexString(idx, "EI"); break;
        case 0xfc: outfile << getHexString(idx, "CM", 3, true); break;		
        case 0xfe: outfile << getHexString(idx, "CPI", 2); break;
        case 0xff: outfile << getHexString(idx, "RST 7"); break;
      }
    }
  }
};


int main() {
  std::ifstream infile("./roms/invaders.h", std::ios::binary);
  std::ofstream outfile("./out/disassembly.txt");
  
  // Verify if the file is available for disassembly
  if (!infile) std::cerr << "error: Unable to open input file!" << std::endl;
 
  Disassemler disassembler(infile);
  disassembler.translateToOpCode(outfile);
}