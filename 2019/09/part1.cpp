#include <algorithm>
#include <array>
#include <cstdint>
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

int get_inst_code(int64_t number)
{
    return number % 100;
}

template <int Param> int64_t get_param_code(int64_t number)
{
    constexpr int64_t pow_10[3] = { 100, 1000, 10000 };
    return (number / pow_10[Param - 1]) % 10;
}

std::vector<int64_t> read_input(const std::string& filename)
{
    std::cout << "Reading program from file: '" << filename << "'" << std::endl;
    auto result = std::vector<int64_t>();
    std::ifstream infile(filename);
    if (!infile.is_open())
    {
        throw std::runtime_error("Could not load file: '" + filename + "'");
    }
    int64_t elem;
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
    ADJUST_RELATIVE_BASE = 9,
};

enum PARAMETER_MODE
{
    POSITION = 0,
    IMMIDEATE = 1,
    RELATIVE = 2,
};

template <int Param>
int64_t get_write_pos_param(const std::vector<int64_t>& codes, const int64_t code, const int64_t ptr, const int64_t relative_base)
{
    auto param = get_param_code<Param>(code);
    switch (param)
    {
    case PARAMETER_MODE::POSITION:
    {
        return codes.at(ptr + Param);
    }
    case PARAMETER_MODE::IMMIDEATE:
    {
        std::cerr << ERROR_PREFIX << "write_pos was PARAMETER_MODE::IMMIDEATE" << std::endl;
        throw "write_pos was PARAMETER_MODE::IMMIDEATE";
    }
    case PARAMETER_MODE::RELATIVE:
    {
        return relative_base + codes.at(ptr + Param);
    }
    default:
    {
        std::cerr << ERROR_PREFIX << "unknown param-mode" << std::endl;
        throw "unknown param-mode";
    }
    }
}

template <int Param>
int64_t get_param(const std::vector<int64_t>& codes, const int64_t code, const int64_t ptr, const int64_t relative_base)
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
    case PARAMETER_MODE::RELATIVE:
    {
        auto address = codes.at(ptr + Param);
        return codes.at(relative_base + address);
    }
    default:
    {
        std::cerr << ERROR_PREFIX << "unknown parameter" << std::endl;
        throw "unknown parameter";
    }
    }
}

void debug_print_code(const std::vector<int64_t>& codes, const int64_t inst_ptr, const int64_t relative_base, const int64_t code)
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
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "write pos: " << get_write_pos_param<3>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::MULTIPLY:
    {
        std::cout << "MULTIPLY\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "write pos: " << get_write_pos_param<3>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::INPUT:
    {
        std::cout << "INPUT\t\t( ";
        std::cout << "write pos: " << get_write_pos_param<1>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::OUTPUT:
    {
        std::cout << "OUTPUT\t\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::JUMP_IF_TRUE:
    {
        std::cout << "JUMP_IF_TRUE\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::JUMP_IF_FALSE:
    {
        std::cout << "JUMP_IF_FALSE\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::LESS_THAN:
    {
        std::cout << "LESS_THAN\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "write pos: " << get_write_pos_param<3>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::EQUALS:
    {
        std::cout << "EQUALS\t\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "val#2: " << get_param<2>(codes, code, inst_ptr, relative_base) << " \t";
        std::cout << "write pos: " << get_write_pos_param<3>(codes, code, inst_ptr, relative_base) << ") ";
        break;
    }
    case INSTRUCTION::ADJUST_RELATIVE_BASE:
    {
        std::cout << "ADJUST_REL_BASE\t( ";
        std::cout << "val#1: " << get_param<1>(codes, code, inst_ptr, relative_base) << ")";
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

void execute_addition(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr, relative_base);
    auto val2 = get_param<2>(codes, code, inst_ptr, relative_base);
    auto write_to = get_write_pos_param<3>(codes, code, inst_ptr, relative_base);
    codes.at(write_to) = val1 + val2;
    inst_ptr += 4;
}

void execute_multiplication(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr, relative_base);
    auto val2 = get_param<2>(codes, code, inst_ptr, relative_base);
    auto write_to = get_write_pos_param<3>(codes, code, inst_ptr, relative_base);
    codes.at(write_to) = val1 * val2;
    inst_ptr += 4;
}

void execute_input(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code, const int64_t input)
{
    auto write_to = get_write_pos_param<1>(codes, code, inst_ptr, relative_base);
    codes.at(write_to) = input;
    inst_ptr += 2;
}

int64_t execute_output(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code)
{
    auto val = get_param<1>(codes, code, inst_ptr, relative_base);
    std::cout << OUT_PREFIX << val << std::endl;
    inst_ptr += 2;
    return val;
}

void execute_jump_if_true(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr, relative_base);
    auto val2 = get_param<2>(codes, code, inst_ptr, relative_base);
    if (val1)
    {
        inst_ptr = val2;
    }
    else
    {
        inst_ptr += 3;
    }
}

void execute_jump_if_false(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr, relative_base);
    auto val2 = get_param<2>(codes, code, inst_ptr, relative_base);
    if (!val1)
    {
        inst_ptr = val2;
    }
    else
    {
        inst_ptr += 3;
    }
}

void execute_less_than(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr, relative_base);
    auto val2 = get_param<2>(codes, code, inst_ptr, relative_base);
    auto write_to = get_write_pos_param<3>(codes, code, inst_ptr, relative_base);
    codes.at(write_to) = val1 < val2;
    inst_ptr += 4;
}

void execute_equals(std::vector<int64_t>& codes, int64_t& inst_ptr, const int64_t relative_base, const int64_t code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr, relative_base);
    auto val2 = get_param<2>(codes, code, inst_ptr, relative_base);
    auto write_to = get_write_pos_param<3>(codes, code, inst_ptr, relative_base);
    codes.at(write_to) = val1 == val2;
    inst_ptr += 4;
}

void execute_adjust_relative_base(const std::vector<int64_t>& codes, int64_t& inst_ptr, int64_t& relative_base, const int64_t code)
{
    auto val1 = get_param<1>(codes, code, inst_ptr, relative_base);
    relative_base += val1;
    inst_ptr += 2;
}

struct Program
{
    std::vector<int64_t> codes_;
    bool termination_indicator = false;
    int64_t inst_ptr = 0;
    int64_t relative_base = 0;
    int64_t last_output = 0;

    Program(const std::vector<int64_t>& codes) : codes_(codes)
    {
        codes_.resize(1 << 16); // todo smarter way?
    }

    int64_t execute_codes(int64_t input)
    {
        std::cout << OUT_PREFIX << "execute_codes( input: " << input << " )" << std::endl;

        while (inst_ptr < codes_.size() && !termination_indicator)
        {
            const auto code = codes_[inst_ptr];
            debug_print_code(codes_, inst_ptr, relative_base, code);

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
                execute_addition(codes_, inst_ptr, relative_base, code);
                break;
            }
            case INSTRUCTION::MULTIPLY:
            {
                execute_multiplication(codes_, inst_ptr, relative_base, code);
                break;
            }
            case INSTRUCTION::INPUT:
            {
                execute_input(codes_, inst_ptr, relative_base, code, input);
                break;
            }
            case INSTRUCTION::OUTPUT:
            {
                last_output = execute_output(codes_, inst_ptr, relative_base, code);
                break;
            }
            case INSTRUCTION::JUMP_IF_TRUE:
            {
                execute_jump_if_true(codes_, inst_ptr, relative_base, code);
                break;
            }
            case INSTRUCTION::JUMP_IF_FALSE:
            {
                execute_jump_if_false(codes_, inst_ptr, relative_base, code);
                break;
            }
            case INSTRUCTION::LESS_THAN:
            {
                execute_less_than(codes_, inst_ptr, relative_base, code);
                break;
            }
            case INSTRUCTION::EQUALS:
            {
                execute_equals(codes_, inst_ptr, relative_base, code);
                break;
            }
            case INSTRUCTION::ADJUST_RELATIVE_BASE:
            {
                execute_adjust_relative_base(codes_, inst_ptr, relative_base, code);
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

    bool has_terminated() const
    {
        return termination_indicator;
    }
};


void tests()
{
    // Program({ 109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006, 101, 0, 99 }).execute_codes(0);
    auto test2 = Program({ 1102, 34915192, 34915192, 7, 4, 7, 99, 0 }).execute_codes(0);
    auto test3 = Program({ 104, 1125899906842624, 99 }).execute_codes(0);
    std::cout << "test2: " << (test2 == 1219070632396864) << " <- assertion" << std::endl;
    std::cout << "test3: " << (test3 == 1125899906842624) << " <- assertion" << std::endl;
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
    Program(codes).execute_codes(1);
    // print(codes);
    // tests();
}
