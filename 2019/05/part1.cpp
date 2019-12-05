#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <string>

#define DEBUG

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
            std::cerr << "unknown parameter" << std::endl;
            throw "unknown parameter";
        }
    }
}

void debug_print_code(const std::vector<int>& codes, int inst_ptr, const int code) {

    #ifdef DEBUG
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
            std::cout << "ADDITION( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << "\t";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        case INSTRUCTION::MULTIPLY: {
            std::cout << "MULTIPLY( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << "\t";
            std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << "\t";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        case INSTRUCTION::INPUT: {
            std::cout << "INPUT\t( ";
            std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
            break;
        }
        case INSTRUCTION::OUTPUT: {
            std::cout << "OUTPUT\t( ";
            std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << ") ";
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

void execute_input(std::vector<int>& codes, int& inst_ptr, const int code) {
    constexpr int input = 1;
    auto write_to = codes.at(inst_ptr + 1);
    codes.at(write_to) = input;
    inst_ptr += 2;
}

void execute_output(std::vector<int>& codes, int& inst_ptr, const int code) {
    auto val = get_param<1>(codes, code, inst_ptr);
    std::cout << val << std::endl;
    inst_ptr += 2;
}

int execute_codes(std::vector<int> codes) {
    bool termination_indicator = false;
    auto inst_ptr = 0;
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
            execute_input(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::OUTPUT: {
            execute_output(codes, inst_ptr, code);
            break;
        }
        default: {
            std::cout << "Terminating due to unknown instruction" << std::endl;
            termination_indicator = true;
            break;
        }
        }
    }
    return codes[0];
}

int main()
{
    auto codes = read_input("input.txt");
    // print(codes);
    auto result = execute_codes(codes);
}
