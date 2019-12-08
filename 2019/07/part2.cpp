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

struct Amplifier
{
    std::vector<int> codes_;
    int phase;
    bool termination_indicator = false;
    int inst_ptr = 0;
    int last_output = 0;

    Amplifier(const std::vector<int>& codes, int phase) : codes_(codes), phase(phase)
    {
        const auto code = codes[inst_ptr];
        const auto instruction = get_inst_code(code);
        if (instruction != INSTRUCTION::INPUT)
        {
            throw "no starting phase input";
        }
        std::cout << OUT_PREFIX << "phase_setting( " << phase << " ) " << std::endl;
        debug_print_code(codes_, inst_ptr, code);
        execute_input(codes_, inst_ptr, code, phase);
    }

    int execute_codes(int input)
    {
        std::cout << OUT_PREFIX << "execute_codes( input: " << input << " )" << std::endl;

        while (inst_ptr < codes_.size() && !termination_indicator)
        {
            const auto code = codes_[inst_ptr];
            debug_print_code(codes_, inst_ptr, code);

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
                execute_addition(codes_, inst_ptr, code);
                break;
            }
            case INSTRUCTION::MULTIPLY:
            {
                execute_multiplication(codes_, inst_ptr, code);
                break;
            }
            case INSTRUCTION::INPUT:
            {
                execute_input(codes_, inst_ptr, code, input);
                break;
            }
            case INSTRUCTION::OUTPUT:
            {
                last_output = execute_output(codes_, inst_ptr, code);
                return last_output;
            }
            case INSTRUCTION::JUMP_IF_TRUE:
            {
                execute_jump_if_true(codes_, inst_ptr, code);
                break;
            }
            case INSTRUCTION::JUMP_IF_FALSE:
            {
                execute_jump_if_false(codes_, inst_ptr, code);
                break;
            }
            case INSTRUCTION::LESS_THAN:
            {
                execute_less_than(codes_, inst_ptr, code);
                break;
            }
            case INSTRUCTION::EQUALS:
            {
                execute_equals(codes_, inst_ptr, code);
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


std::vector<std::array<int, 5>> get_phase_combinations(int start)
{
    auto result = std::vector<std::array<int, 5>>();
    result.reserve(5 * 4 * 3 * 2);
    auto settings = std::array<int, 5>{ start, start + 1, start + 2, start + 3, start + 4 };
    do
    {
        result.push_back(settings);
    } while (std::next_permutation(settings.begin(), settings.end()));
    return result;
}

int execute_amplifiers(const std::vector<int>& codes, const std::array<int, 5>& phase_settings)
{
    auto amplifiers = std::array<Amplifier, 5>{
        Amplifier(codes, phase_settings[0]), Amplifier(codes, phase_settings[1]),
        Amplifier(codes, phase_settings[2]), Amplifier(codes, phase_settings[3]),
        Amplifier(codes, phase_settings[4]),
    };
    auto active_amplifier = 0;
    auto input = 0;
    while (!amplifiers[active_amplifier].has_terminated())
    {
        input = amplifiers[active_amplifier].execute_codes(input);
        active_amplifier = (active_amplifier + 1) % 5;
    }
    return input;
}

int calculate_max_signal(const std::vector<int>& codes)
{
    auto best = 0;
    for (const auto& phase_settings : get_phase_combinations(5))
    {
        auto output = execute_amplifiers(codes, phase_settings);
        if (output > best)
        {
            best = output;
        }
    }
    return best;
}


void tests()
{
    auto test1 =
        (calculate_max_signal({ 3,  26, 1001, 26,   -4, 26, 3,  27,   1002, 27, 2,  27, 1, 27, 26,
                                27, 4,  27,   1001, 28, -1, 28, 1005, 28,   6,  99, 0,  0, 5 }) == 139629729);
    auto test2 = (calculate_max_signal(
                      { 3,    52,   1001, 52,   -5,   52, 3,  53, 1,    52, 56, 54, 1007, 54, 5,
                        55,   1005, 55,   26,   1001, 54, -5, 54, 1105, 1,  12, 1,  53,   54, 53,
                        1008, 54,   0,    55,   1001, 55, 1,  55, 2,    53, 55, 53, 4,    53, 1001,
                        56,   -1,   56,   1005, 56,   6,  99, 0,  0,    0,  0,  10 }) == 18216);


    auto test3 =
        (execute_amplifiers({ 3,  26, 1001, 26,   -4, 26, 3,  27,   1002, 27, 2,  27, 1, 27, 26,
                              27, 4,  27,   1001, 28, -1, 28, 1005, 28,   6,  99, 0,  0, 5 },
                            { 9, 8, 7, 6, 5 }) == 139629729);
    auto test4 =
        (execute_amplifiers({ 3,    52, 1001, 52, -5,   52, 3,    53,   1,    52, 56,   54,
                              1007, 54, 5,    55, 1005, 55, 26,   1001, 54,   -5, 54,   1105,
                              1,    12, 1,    53, 54,   53, 1008, 54,   0,    55, 1001, 55,
                              1,    55, 2,    53, 55,   53, 4,    53,   1001, 56, -1,   56,
                              1005, 56, 6,    99, 0,    0,  0,    0,    10 },
                            { 9, 7, 8, 5, 6 }) == 18216);

    std::cout << "test1: " << test1 << " <- assertion" << std::endl;
    std::cout << "test2: " << test2 << " <- assertion" << std::endl;
    std::cout << "test3: " << test3 << " <- assertion" << std::endl;
    std::cout << "test4: " << test4 << " <- assertion" << std::endl;
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
