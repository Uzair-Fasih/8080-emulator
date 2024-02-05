disassemble:
	@g++ ./src/disassembler.cpp
	@./a.out
	@rm ./a.out

emulate:
	@g++ ./src/emulator.cpp
	@./a.out
	@rm ./a.out