#ifndef ALI_HPP
#define ALI_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "Instruction.hpp"

using namespace std;

class Instruction;
using MemoryUnit = std::variant<int*, std::unique_ptr<Instruction>>;

class ALI {
public:
    static const int MEMORY_SIZE = 256;
    static const int START_ADDRESS_FOR_VARIABLES = 128;
    std::vector<std::unique_ptr<Instruction>> instructionMemory;
    std::vector<int> dataMemory;

    std::vector<MemoryUnit> memory;


    int32_t accumulator;
    int32_t data_register;
    int program_counter;
    bool zero_bit;
    bool overflow_bit;
    std::unordered_map<std::string, int> symbol_table;
    bool halt_program;

     ALI();
    ~ALI();

    // Functions for ALI operations
    int convert_symbol_to_address(const std::string& symbol);
    void load_program(const std::string& file_name);


    static std::unique_ptr<Instruction> create_instruction(const std::string& instruction_name, const std::vector<std::string>& operands);
    void print_state();
    void run();
    void step(bool print_state_after = true);
    bool execute_instruction(Instruction* instruction);

    // Getter and setter methods for registers and flags
    int getA() const { return accumulator; }
    void setA(int value) { accumulator = value; }
    int getB() const { return data_register; }
    void setB(int value) { data_register = value; }
    int getPC() const { return program_counter; }
    void setPC(int value) { program_counter = value; }
    bool getZeroBit() const { return zero_bit; }
    void setZeroBit(bool value) { zero_bit = value; }
    bool getOverflowBit() const { return overflow_bit; }
    void setOverflowBit(bool value) { overflow_bit = value; }
    bool getHaltProgram() const { return halt_program; }
    void setHaltProgram(bool value) { halt_program = value; }

    string symbol_for_address(int address);
    bool error() const;

private:
    unordered_map<int, string> address_to_symbol;  // Reverse lookup map


};



#endif // ALI_HPP
