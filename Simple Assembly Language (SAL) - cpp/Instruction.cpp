

#include "Instruction.hpp"
#include "ALI.hpp"

// DecInstruction: Initialize data memory location for a symbol to zero
DecInstruction::DecInstruction(const std::string& symbol) : symbol(symbol) {}

bool DecInstruction::execute(ALI& ali) {
    // Convert symbol to address and initialize the memory at that address
    int address = ali.convert_symbol_to_address(this->symbol);
    if (address >= 128 && address < 256) {
        ali.dataMemory[address - 128] = 0;
    }
    return true; // Indicate successful execution
}

std::string DecInstruction::to_string() const {
    return "DEC " + symbol;
}



// LdiInstruction: Load a constant value into the accumulator
LdiInstruction::LdiInstruction(int val) : value(val) {}

bool LdiInstruction::execute(ALI& ali) {
    ali.setA(value); // Directly set the accumulator with the provided value
    return true;  // Indicate that PC should be incremented after execution
}

std::string LdiInstruction::to_string() const {
    return "LDI " + std::to_string(value);
}




// StrInstruction: Store the accumulator's value into a symbol's data memory location
StrInstruction::StrInstruction(const string& sym) : symbol(sym) {}

bool StrInstruction::execute(ALI& ali) {
    int address = ali.convert_symbol_to_address(symbol);
    if (address >= 128 && address < 256) {
        ali.dataMemory[address - 128] = ali.getA();
    }
    return true;  //PC will be incremented after execution
}

std::string StrInstruction::to_string() const {
    return "STR " + symbol;
}



// XchInstruction: Swap the values of the accumulator and data register
XchInstruction::XchInstruction() : Instruction() {}

bool XchInstruction::execute(ALI& ali) {
    int temp = ali.getA();
    ali.setA(ali.getB());
    ali.setB(temp);
    return true;
}

std::string XchInstruction::to_string() const {
    return "XCH";
}




// JmpInstruction: Set program counter to a specific address
JmpInstruction::JmpInstruction(int addr) : address(addr) {}

bool JmpInstruction::execute(ALI& ali) {
    ali.setPC(address);
    return false;
}

std::string JmpInstruction::to_string() const {
    return "JMP " + std::to_string(address);
}




// JzsInstruction: Conditional jump based on the zero-result bit
JzsInstruction::JzsInstruction(int addr) : address(addr) {}

bool JzsInstruction::execute(ALI& ali) {
    if (ali.getZeroBit()) {
        ali.setPC(address);
        return false;
    }
    return true;
}

std::string JzsInstruction::to_string() const {
    return "JZS " + std::to_string(address);
}





// JvsInstruction: Conditional jump based on the overflow bit
JvsInstruction::JvsInstruction(int addr) : address(addr) {}

bool JvsInstruction::execute(ALI& ali) {
    if (ali.getOverflowBit()) {
        ali.setPC(address);
        return false;
    }
    return true;
}

std::string JvsInstruction::to_string() const {
    return "JVS " + std::to_string(address);
}






// AddInstruction: Add values of A and B registers and handle overflow
AddInstruction::AddInstruction() : Instruction() {}

bool AddInstruction::execute(ALI& ali) {
    long long result = static_cast<long long>(ali.getA()) + ali.getB();
    bool overflow = result > INT_MAX || result < INT_MIN;
    ali.setOverflowBit(overflow);
    ali.setA(static_cast<int>(result));
    ali.setZeroBit(ali.getA() == 0);
    return true; // Indicate successful execution
}

std::string AddInstruction::to_string() const {
    return "ADD";
}




// SubInstruction: Subtract the B register from the A register and handle overflow
SubInstruction::SubInstruction() : Instruction() {}

bool SubInstruction::execute(ALI& ali) {
    long long result = static_cast<long long>(ali.getA()) - ali.getB();
    bool overflow = result > INT_MAX || result < INT_MIN;
    ali.setOverflowBit(overflow);
    ali.setA(static_cast<int>(result));
    ali.setZeroBit(ali.getA() == 0);
    return true; // Indicate successful execution, PC should increment
}

std::string SubInstruction::to_string() const {
    return "SUB";
}




// HltInstruction: Halt the execution
HltInstruction::HltInstruction() : Instruction() {}

bool HltInstruction::execute(ALI& ali) {
    ali.halt_program = true;
    return false; // halt and no further PC increment
}

std::string HltInstruction::to_string() const {
    return "HLT";
}


// LdaInstruction: Load data from a symbol's memory location into the accumulator
LdaInstruction::LdaInstruction(const std::string& sym) : symbol(sym) {}

bool LdaInstruction::execute(ALI& ali) {
    int address = ali.convert_symbol_to_address(symbol);
    if (address >= 128 && address < 256) {
        ali.setA(ali.dataMemory[address - 128]); // load integer from dataMemory into the accumulator
    }
    return true; // success in execution, so PC should increment
}

std::string LdaInstruction::to_string() const {
    return "LDA " + symbol;
}
