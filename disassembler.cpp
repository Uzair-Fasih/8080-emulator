#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

std::vector<std::string> getHexDump(std::ifstream & infile) {
  char c;
  std::vector<std::string> hexdump;
  while (infile.get(c)) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0') << (((short) c) & 0xFF);
    hexdump.push_back(ss.str());
  }

  return hexdump;
}

std::vector<std::string> translateToOpCode(std::vector<std::string> & hexdump) {
  
}

int main() {
  std::ifstream infile("./roms/invaders.h", std::ios::binary);
  
  // Verify if the file is available for disassembly
  if (!infile) {
    std::cerr << "error: Unable to open input file!" << std::endl;
  }
  
  auto hexdump = getHexDump(infile);
  for (auto s: hexdump) std::cout << s << " ";
}