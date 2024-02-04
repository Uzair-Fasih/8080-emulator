disassemble:
	@g++ ./src/disassembler.cpp
	@./a.out
	@rm ./a.out