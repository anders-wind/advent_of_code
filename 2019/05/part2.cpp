#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <string>

// #define DEBUG
constexpr const char* OUT_PREFIX = "OUT: \t";
constexpr const char* ERROR_PREFIX = "ERR: \t";
constexpr const char* DEBUG_PREFIX = "DBG: \t";

int get_inst_code(int number) {
    return number%100;
}

template<int Param>
int get_param_code(int number) {
    constexpr int pow_10[3] = {100,1000,10000};
    return (number/pow_10[Param-1])%10;
}

std::vector<int> read_input(const std::string& filename)
{
    auto result = std::vector<int>();
    std::ifstream infile(filename);
    int elem;
    char seperator;
    while (infile >> elem)
    {
        result.push_back(elem);
        infile >> seperator;
    }
    return result;
}

template<typename T>
void print(std::vector<T> arr)
{
    std::cout << "Array: " << std::endl;
    for (const auto elem : arr)
    {
        std::cout << "  " << elem << std::endl;
    }
}

enum INSTRUCTION {
    TERMINATE = 99,
    ADDITION = 1,
    MULTIPLY = 2,
    INPUT = 3,
    OUTPUT = 4,
    JUMP_IF_TRUE = 5,
    JUMP_IF_FALSE = 6,
    LESS_THAN = 7,
    EQUALS = 8,
};

enum PARAMETER_MODE {
    POSITION = 0,
    IMMIDEATE = 1, 
};

template<int Param>
int get_param(const std::vector<int>& codes, const int code, const int ptr) {
    auto param = get_param_code<Param>(code);
    switch (param) {
        case PARAMETER_MODE::POSITION: {
            auto address = codes.at(ptr+Param);
            return codes.at(address);
        }
        case PARAMETER_MODE::IMMIDEATE: {
            return codes.at(ptr+Param);
        }
        default: {
            std::cerr << ERROR_PREFIX << "unknown parameter" << std::endl;
            throw "unknown parameter";
        }
    }
}

void debug_print_code(const std::vector<int>& codes, int inst_ptr, const int code) {

    #ifdef DEBUG
    std::cout << DEBUG_PREFIX;
    const auto instruction = get_inst_code(code);
    std::cout << "inst_ptr: " << inst_ptr << " \t";
    std::cout << "code: " << code << " \t";
    // std::cout << "instruction: " << instruction << ", \t";
    switch (instruction)
        {
        case INSTRUCTION::TERMINATE: {
            std::cout << "TERMINATE!";
            break;
        }
        case INSTRUCTION::ADDITION: {
            std::cout << "ADDITION\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << "\t";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        case INSTRUCTION::MULTIPLY: {
            std::cout << "MULTIPLY\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << "\t";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        case INSTRUCTION::INPUT: {
            std::cout << "INPUT\t\t( ";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        case INSTRUCTION::OUTPUT: {
            std::cout << "OUTPUT\t\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << ") ";
            break;
        }
        case INSTRUCTION::JUMP_IF_TRUE: {
            std::cout << "JUMP_IF_TRUE\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t ";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << ") ";
            break;
        }
        case INSTRUCTION::JUMP_IF_FALSE: {
            std::cout << "JUMP_IF_FALSE\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t ";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << ") ";
            break;
        }
        case INSTRUCTION::LESS_THAN: {
            std::cout << "LESS_THAN\t\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t ";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << "\t ";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        case INSTRUCTION::EQUALS: {
            std::cout << "EQUALS\t\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t ";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << "\t ";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        default: {
            std::cout << "UNKNOWN instruction" << std::endl;
            break;
        }
    }
    std::cout << std::endl;
    #endif

}

void execute_addition(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr +3);
    codes.at(write_to) = val1 + val2;
    inst_ptr += 4;
}

void execute_multiplication(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr +3);
    codes.at(write_to) = val1 * val2;
    inst_ptr += 4;
}

void execute_input(std::vector<int>& codes, int& inst_ptr, const int code, const int input) {
    auto write_to = codes.at(inst_ptr + 1);
    codes.at(write_to) = input;
    inst_ptr += 2;
}

int execute_output(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val = get_param<1>(codes, code, inst_ptr);
    std::cout << OUT_PREFIX << val << std::endl;
    inst_ptr += 2;
    return val;
}

void execute_jump_if_true(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    if(val1) {
        inst_ptr = val2;
    } else {
        inst_ptr += 3;
    }
}
void execute_jump_if_false(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    if(!val1) {
        inst_ptr = val2;
    } else {
        inst_ptr += 3;
    }
}

void execute_less_than(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr +3);
    codes.at(write_to) = val1 < val2;
    inst_ptr += 4;
}

void execute_equals(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr +3);
    codes.at(write_to) = val1 == val2;
    inst_ptr += 4;
}

int execute_codes(std::vector<int> codes, int input) {
    bool termination_indicator = false;
    auto inst_ptr = 0;
    int last_output = 0;
    while(inst_ptr < codes.size() && !termination_indicator)
    {
        const auto code = codes[inst_ptr];
        debug_print_code(codes, inst_ptr, code);

        const auto instruction = get_inst_code(code);
        switch (instruction)
        {
        case INSTRUCTION::TERMINATE: {
            termination_indicator = true;
            break;
        }
        case INSTRUCTION::ADDITION: {
            execute_addition(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::MULTIPLY: {
            execute_multiplication(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::INPUT: {
            execute_input(codes, inst_ptr, code, input);
            break;
        }
        case INSTRUCTION::OUTPUT: {
            last_output = execute_output(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::JUMP_IF_TRUE: {
            execute_jump_if_true(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::JUMP_IF_FALSE: {
            execute_jump_if_false(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::LESS_THAN: {
            execute_less_than(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::EQUALS: {
            execute_equals(codes, inst_ptr, code);
            break;
        }
        default: {
            std::cerr << ERROR_PREFIX << "Terminating due to unknown instruction" << std::endl;
            termination_indicator = true;
            break;
        }
        }
    }
    return last_output;
}


void tests() {
    // Using position mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
    std::cout << (execute_codes({3,9,8,9,10,9,4,9,99,-1,8}, 8) == 1) << " <- assertion" << std::endl;
    std::cout << (execute_codes({3,9,8,9,10,9,4,9,99,-1,8}, 7) == 0) << " <- assertion" << std::endl;

    // Using position mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
    std::cout << (execute_codes({3,9,7,9,10,9,4,9,99,-1,8}, 7) == 1) << " <- assertion" << std::endl;
    std::cout << (execute_codes({3,9,7,9,10,9,4,9,99,-1,8}, 8) == 0) << " <- assertion" << std::endl;

    // Using immediate mode, consider whether the input is equal to 8; output 1 (if it is) or 0 (if it is not).
    std::cout << (execute_codes({3,3,1108,-1,8,3,4,3,99}, 8) == 1) << " <- assertion" << std::endl;
    std::cout << (execute_codes({3,3,1108,-1,8,3,4,3,99}, 7) == 0) << " <- assertion" << std::endl;

    // Using immediate mode, consider whether the input is less than 8; output 1 (if it is) or 0 (if it is not).
    std::cout << (execute_codes({3,3,1107,-1,8,3,4,3,99}, 7) == 1) << " <- assertion" << std::endl;
    std::cout << (execute_codes({3,3,1107,-1,8,3,4,3,99}, 8) == 0) << " <- assertion" << std::endl;

    // take an input, then output 0 if the input was zero or 1 if the input was non-zero
    // using position:
    std::cout << (execute_codes({3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9}, 0) == 0) << " <- assertion" << std::endl;
    std::cout << (execute_codes({3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9}, 1) == 1) << " <- assertion" << std::endl;
    // using immediate 
    std::cout << (execute_codes({3,3,1105,-1,9,1101,0,0,12,4,12,99,1}, 0) == 0) << " <- assertion" << std::endl;
    std::cout << (execute_codes({3,3,1105,-1,9,1101,0,0,12,4,12,99,1}, 1) == 1) << " <- assertion" << std::endl;
    

    auto large_example = std::vector<int>{3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
                                          1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
                                          999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99};
    // The above example program uses an input instruction to ask for a single number. 
    // The program will then:
    //  output 999 if the input value is below 8, 
    //  output 1000 if the input value is equal to 8,
    //  output 1001 if the input value is greater than 8.

    std::cout << (execute_codes(large_example, 7) == 999) << " <- assertion" << std::endl;
    std::cout << (execute_codes(large_example, 8) == 1000) << " <- assertion" << std::endl;
    std::cout << (execute_codes(large_example, 9) == 1001) << " <- assertion" << std::endl;
}


int main()
{
    auto codes = read_input("input.txt");
    // print(codes);
    auto result = execute_codes(codes, 5);
    // tests();
}
