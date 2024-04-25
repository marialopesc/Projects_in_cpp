#include "ALI.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Instruction.hpp"
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;


// Constructor initializing the ALI components and memory structures
ALI::ALI() : instructionMemory(START_ADDRESS_FOR_VARIABLES),
             dataMemory(MEMORY_SIZE - START_ADDRESS_FOR_VARIABLES, 0),
             accumulator(0), data_register(0), program_counter(0),
             zero_bit(false), overflow_bit(false), halt_program(false) {
    cout << "ALI initialized with " << START_ADDRESS_FOR_VARIABLES
              << " instruction slots and "
              << (MEMORY_SIZE - START_ADDRESS_FOR_VARIABLES)
              << " data slots." << endl;
}

ALI::~ALI() = default;


// Convert symbolic labels to their respective memory addresses
int ALI::convert_symbol_to_address(const string& symbol) {
    auto it = symbol_table.find(symbol);
    if (it == symbol_table.end()) {
        int address = symbol_table.size() + START_ADDRESS_FOR_VARIABLES;
        symbol_table[symbol] = address;
        return address;
    }
    return it->second;
}


// Load and parse SAL program from file
void ALI::load_program(const string& file_name) {
    ifstream file(file_name);
    string line;
    int line_number = 0;

    if (!file.is_open()) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }

    while (getline(file, line) && line_number < START_ADDRESS_FOR_VARIABLES) {
        istringstream iss(line);
        string instruction_name;
        vector<string> operands;
        string operand;

        iss >> instruction_name;
        while (iss >> operand) {
            operands.push_back(operand);
        }

        try {
            auto instruction = create_instruction(instruction_name, operands);
            if (instruction && line_number < instructionMemory.size()) {
                instructionMemory[line_number] = std::move(instruction);
                line_number++;
            } else {
                cerr << "Failed to create instruction from line: " << line << endl;
            }
        } catch (const exception& e) {
            cerr << "Exception while creating instruction: " << e.what() << endl;
        }
    }

    file.close();
}


// Factory method to create instructions based on type
unique_ptr<Instruction> ALI::create_instruction(const string& instruction_name, const vector<string>& operands) {
    try {
        if (instruction_name == "DEC" && operands.size() == 1) {
            return make_unique<DecInstruction>(operands[0]);
        } else if (instruction_name == "LDI" && operands.size() == 1) {
            int value = stoi(operands[0]);
            return make_unique<LdiInstruction>(value);
        } else if (instruction_name == "STR" && operands.size() == 1) {
            return make_unique<StrInstruction>(operands[0]);
        } else if (instruction_name == "XCH" && operands.empty()) {
            return make_unique<XchInstruction>();
        } else if (instruction_name == "ADD" && operands.empty()) {
            return make_unique<AddInstruction>();
        } else if (instruction_name == "JZS" && operands.size() == 1) {
            int address = stoi(operands[0]);
            return make_unique<JzsInstruction>(address);
        } else if (instruction_name == "JVS" && operands.size() == 1) {
            int address = stoi(operands[0]);
            return make_unique<JvsInstruction>(address);
        } else if (instruction_name == "JMP" && operands.size() == 1) {
            int address = stoi(operands[0]);
            return make_unique<JmpInstruction>(address);
        } else if (instruction_name == "LDA" && operands.size() == 1) {
            return make_unique<LdaInstruction>(operands[0]);
        } else if (instruction_name == "HLT" && operands.empty()) {
            return make_unique<HltInstruction>();
        } else {
            throw runtime_error("Incorrect number of operands or unknown instruction: " + instruction_name);
        }
    } catch (const invalid_argument& e) {
        throw runtime_error("Invalid argument for instruction '" + instruction_name + "': " + e.what());
    } catch (const out_of_range& e) {
        throw runtime_error("Argument out of range for instruction '" + instruction_name + "': " + e.what());
    }
}


// Print current state of ALI
void ALI::print_state() {
    // Print registers
    cout << "--- REGISTERS ---" << endl;
    cout << "A/Accum: " << accumulator << endl;
    cout << "B/Data: " << data_register << endl;
    cout << "PC: " << program_counter << endl;
    cout << "ZF: " << (zero_bit ? "True" : "False") << endl;
    cout << "OF: " << (overflow_bit ? "True" : "False") << endl;

    // Print instruction memory
    cout << "--- Instruction Memory ---" << endl;
    bool has_instruction = false;
    for (int i = 0; i < START_ADDRESS_FOR_VARIABLES; ++i) {
        if (instructionMemory[i]) {
            cout << "[" << i << "]: " << instructionMemory[i]->to_string() << endl;
            has_instruction = true;
        }
    }
    if (!has_instruction) {
        cout << "No instructions loaded." << endl;
    }

    // Print data memory with symbolic names
    cout << "--- Data Memory ---" << endl;
    bool has_data = false;
    for (int i = 0; i < dataMemory.size(); ++i) {
        string symbol = symbol_for_address(128 + i);
        if (!symbol.empty() || dataMemory[i] != 0) {
            cout << "[" << 128 + i << "] " << (symbol.empty() ? "": symbol + ": ") << dataMemory[i] << endl;
            has_data = true;
        }
    }
    if (!has_data) {
        cout << "No data stored." << endl;
    }
}

string ALI::symbol_for_address(int address) {
    // Assuming you have a reverse lookup from address to symbol
    for (const auto& pair : symbol_table) {
        if (pair.second == address) {
            return pair.first;
        }
    }
    return "";
}



//void ALI::run() {
//    cout << "Starting program execution..." << endl;
//    int instruction_count = 0;
//    while (!getHaltProgram() && getPC() < MEMORY_SIZE) {
//        step(false);
//    }
//    cout << "Program execution finished." << endl;
//}


// Main execution loop handling instruction limits and continuation
void ALI::run() {
    cout << "Starting program execution..." << endl;
    int instruction_count = 0;
    const int max_instruction_limit = 1000;

    while (!getHaltProgram() && getPC() < MEMORY_SIZE && instruction_count < max_instruction_limit) {
        step(false);
        instruction_count++;
    }

    if (instruction_count >= max_instruction_limit) {
        char response;
        cout << "Execution limit of " << max_instruction_limit << " reached. Continue? (y/n): ";
        cin >> response;
        if (response == 'y' || response == 'Y') {
            run();
        } else {
            cout << "Execution halted by user." << endl;
        }
    } else {
        cout << "Program execution finished." << endl;
    }
}



bool ALI::error() const {
    if (getPC() == 6) {
        return true;
    }
    return false;
}



bool ALI::execute_instruction(Instruction* instruction) {
    if (instruction != nullptr) {
        return instruction->execute(*this);
    } else {
        cerr << "Error: Null instruction cannot be executed." << endl;
        return true;
    }
}

void ALI::step(bool print_state_after_step) {
    if (getHaltProgram() || getPC() >= instructionMemory.size()) {
        return;
    }

    auto& current_instruction = instructionMemory[getPC()];
    if (current_instruction != nullptr) {
        bool incrementPC = execute_instruction(current_instruction.get());
        if (incrementPC) {
            setPC(getPC() + 1);
        }
    } else {
        cerr << "Error: No instruction found at program counter " << getPC() << endl;
    }

    if (print_state_after_step) {
        print_state();
    }

    if (error()) {
        return;
    }
}





