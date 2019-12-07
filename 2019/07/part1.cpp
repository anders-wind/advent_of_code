#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

// compile with: [C++ compiler] part2.cpp [-DDEBUG]

constexpr const char* OUT_PREFIX = "OUT: \t";
constexpr const char* ERROR_PREFIX = "ERR: \t";
constexpr const char* DEBUG_PREFIX = "DBG: \t";

int get_inst_code(int number)
{
    return number % 100;
}

template <int Param> int get_param_code(int number)
{
    constexpr int pow_10[3] = { 100, 1000, 10000 };
    return (number / pow_10[Param - 1]) % 10;
}

std::vector<int> read_input(const std::string& filename)
{
    std::cout << "Reading program from file: '" << filename << "'" << std::endl;
    auto result = std::vector<int>();
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        throw std::runtime_error("Could not load file: '" + filename + "'");
    }
    int elem;
    char seperator;
    while (infile >> elem)
    {
        result.push_back(elem);
        infile >> seperator;
    }
    return result;
}

template <typename Iter> void print(const Iter& arr)
{
    std::cout << "Array: " << std::endl;
    for (const auto& elem : arr)
    {
        std::cout << "  " << elem << std::endl;
    }
}

enum INSTRUCTION
{
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

enum PARAMETER_MODE
{
    POSITION = 0,
    IMMIDEATE = 1,
};

template <int Param> int get_param(const std::vector<int>& codes, const int code, const int ptr)
{
    auto param = get_param_code<Param>(code);
    switch (param)
    {
    case PARAMETER_MODE::POSITION:
    {
        auto address = codes.at(ptr + Param);
        return codes.at(address);
    }
    case PARAMETER_MODE::IMMIDEATE:
    {
        return codes.at(ptr + Param);
    }
    default:
    {
        std::cerr << ERROR_PREFIX << "unknown parameter" << std::endl;
        throw "unknown parameter";
    }
    }
}

void debug_print_code(const std::vector<int>& codes, int inst_ptr, const int code)
{

#ifdef DEBUG
    std::cout << DEBUG_PREFIX;
    const auto instruction = get_inst_code(code);
    std::cout << "inst_ptr: " << inst_ptr << " \t";
    std::cout << "code: " << code << " \t";
    // std::cout << "instruction: " << instruction << ", \t";
    switch (instruction)
    {
    case INSTRUCTION::TERMINATE:
    {
        std::cout << "TERMINATE!";
        break;
    }
    case INSTRUCTION::ADDITION:
    {
        std::cout << "ADDITION\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << " \t";
        std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
        break;
    }
    case INSTRUCTION::MULTIPLY:
    {
        std::cout << "MULTIPLY\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << " \t";
        std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
        break;
    }
    case INSTRUCTION::INPUT:
    {
        std::cout << "INPUT\t\t( ";
        std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
        break;
    }
    case INSTRUCTION::OUTPUT:
    {
        std::cout << "OUTPUT\t\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << ") ";
        break;
    }
    case INSTRUCTION::JUMP_IF_TRUE:
    {
        std::cout << "JUMP_IF_TRUE\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << ") ";
        break;
    }
    case INSTRUCTION::JUMP_IF_FALSE:
    {
        std::cout << "JUMP_IF_FALSE\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << ") ";
        break;
    }
    case INSTRUCTION::LESS_THAN:
    {
        std::cout << "LESS_THAN\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << " \t";
        std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
        break;
    }
    case INSTRUCTION::EQUALS:
    {
        std::cout << "EQUALS\t\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr) << " \t";
        std::cout << "write pos: " << codes.at(inst_ptr + 3) << ") ";
        break;
    }
    default:
    {
        std::cout << "UNKNOWN instruction" << std::endl;
        break;
    }
    }
    std::cout << std::endl;
#endif
}

void execute_addition(std::vector<int>& codes, int& inst_ptr, const int code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr + 3);
    codes.at(write_to) = val1 + val2;
    inst_ptr += 4;
}

void execute_multiplication(std::vector<int>& codes, int& inst_ptr, const int code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr + 3);
    codes.at(write_to) = val1 * val2;
    inst_ptr += 4;
}

void execute_input(std::vector<int>& codes, int& inst_ptr, const int code, const int input)
{
    auto write_to = codes.at(inst_ptr + 1);
    codes.at(write_to) = input;
    inst_ptr += 2;
}

int execute_output(std::vector<int>& codes, int& inst_ptr, const int code)
{
    auto val = get_param<1>(codes, code, inst_ptr);
    std::cout << OUT_PREFIX << val << std::endl;
    inst_ptr += 2;
    return val;
}

void execute_jump_if_true(std::vector<int>& codes, int& inst_ptr, const int code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    if (val1)
    {
        inst_ptr = val2;
    }
    else
    {
        inst_ptr += 3;
    }
}
void execute_jump_if_false(std::vector<int>& codes, int& inst_ptr, const int code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    if (!val1)
    {
        inst_ptr = val2;
    }
    else
    {
        inst_ptr += 3;
    }
}

void execute_less_than(std::vector<int>& codes, int& inst_ptr, const int code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr + 3);
    codes.at(write_to) = val1 < val2;
    inst_ptr += 4;
}

void execute_equals(std::vector<int>& codes, int& inst_ptr, const int code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr);
    auto val2 = get_param<2>(codes, code, inst_ptr);
    auto write_to = codes.at(inst_ptr + 3);
    codes.at(write_to) = val1 == val2;
    inst_ptr += 4;
}

int execute_codes(std::vector<int> codes, int phase, int input)
{
    std::cout << OUT_PREFIX << "input: " << input << std::endl;

    bool termination_indicator = false;
    auto inst_ptr = 0;
    int last_output = 0;
    auto active_input = phase;
    while (inst_ptr < codes.size() && !termination_indicator)
    {
        const auto code = codes[inst_ptr];
        debug_print_code(codes, inst_ptr, code);

        const auto instruction = get_inst_code(code);
        switch (instruction)
        {
        case INSTRUCTION::TERMINATE:
        {
            termination_indicator = true;
            break;
        }
        case INSTRUCTION::ADDITION:
        {
            execute_addition(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::MULTIPLY:
        {
            execute_multiplication(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::INPUT:
        {
            execute_input(codes, inst_ptr, code, active_input);
            active_input = input;
            break;
        }
        case INSTRUCTION::OUTPUT:
        {
            last_output = execute_output(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::JUMP_IF_TRUE:
        {
            execute_jump_if_true(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::JUMP_IF_FALSE:
        {
            execute_jump_if_false(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::LESS_THAN:
        {
            execute_less_than(codes, inst_ptr, code);
            break;
        }
        case INSTRUCTION::EQUALS:
        {
            execute_equals(codes, inst_ptr, code);
            break;
        }
        default:
        {
            std::cerr << ERROR_PREFIX << "Terminating due to unknown instruction" << std::endl;
            termination_indicator = true;
            break;
        }
        }
    }
    return last_output;
}

std::vector<std::array<int, 5>> get_phase_combinations()
{
    auto result = std::vector<std::array<int, 5>>();
    result.reserve(5 * 4 * 3 * 2);
    auto settings = std::array<int, 5>{ 0, 1, 2, 3, 4 };
    do
    {
        result.push_back(settings);
    } while (std::next_permutation(settings.begin(), settings.end()));
    return result;
}

int calculate_max_signal(const std::vector<int>& codes)
{
    auto best = 0;
    for (const auto& phase_settings : get_phase_combinations())
    {
        auto input = 0;
        for (auto i = 0; i < phase_settings.size(); i++)
        {
            auto phase = phase_settings[i];
            input = execute_codes(codes, phase, input);
        }
        if (input > best)
        {
            best = input;
        }
    }
    return best;
}


void tests()
{
    auto test1 =
        (calculate_max_signal({ 3, 15, 3, 16, 1002, 16, 10, 16, 1, 16, 15, 15, 4, 15, 99, 0, 0 }) == 43210);
    auto test2 = (calculate_max_signal({ 3, 23, 3,  24, 1002, 24, 10, 24, 1002, 23, -1, 23, 101,
                                         5, 23, 23, 1,  24,   23, 23, 4,  23,   99, 0,  0 }) == 54321);
    auto test3 = (calculate_max_signal({ 3,    31, 3,  32, 1002, 32, 10, 32, 1001, 31, -2, 31,
                                         1007, 31, 0,  33, 1002, 33, 7,  33, 1,    33, 31, 31,
                                         1,    32, 31, 31, 4,    31, 99, 0,  0,    0 }) == 65210);

    std::cout << test1 << " <- assertion" << std::endl;
    std::cout << test2 << " <- assertion" << std::endl;
    std::cout << test3 << " <- assertion" << std::endl;
}


int main(int argc, char* argv[])
{
    std::cout << "Usage: ./program [program file] [input number]" << std::endl;

    // defaults
    auto file_name = "input.txt";

    // cmd arguments
    if (argc > 1)
    {
        file_name = argv[1];
    }
    auto codes = read_input(file_name);
    // print(codes);

    auto max = calculate_max_signal(codes);
    std::cout << max << std::endl;
    // tests();
}
