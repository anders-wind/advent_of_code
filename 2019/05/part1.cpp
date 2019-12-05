#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <string>

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
    WRITE = 3,
    PRINT = 4,
};


void execute_addition(std::vector<int>& codes, int& inst_ptr) {
    auto address_1 = codes.at(inst_ptr + 1);
    auto address_2 = codes.at(inst_ptr + 2);
    auto address_write = codes.at(inst_ptr + 3);
    codes.at(address_write) = codes.at(address_1) + codes.at(address_2);
    inst_ptr += 4;
}

void execute_multiplication(std::vector<int>& codes, int& inst_ptr) {
    auto address_1 = codes.at(inst_ptr + 1);
    auto address_2 = codes.at(inst_ptr + 2);
    auto address_write = codes.at(inst_ptr + 3);
    codes.at(address_write) = codes.at(address_1) * codes.at(address_2);
    inst_ptr += 4;
}


int execute_codes(std::vector<int> codes, int noun, int verb) {
    codes[1] = noun;
    codes[2] = verb;
    bool termination_indicator = false;
    auto inst_ptr = 0;
    while(inst_ptr < codes.size() && !termination_indicator)
    {
        const auto code = codes[inst_ptr];
        switch (code)
        {
        case INSTRUCTION::TERMINATE: {
            termination_indicator = true;
            break;
        }
        case INSTRUCTION::ADDITION: {
            execute_addition(codes, inst_ptr);
            break;
        }
        case INSTRUCTION::MULTIPLY: {
            execute_multiplication(codes, inst_ptr);
            break;
        }
        case INSTRUCTION::WRITE: {
            termination_indicator = true;
            break;
        }
        case INSTRUCTION::PRINT: {
            termination_indicator = true;
            break;
        }
        default: {
            std::clog << "hit unknown instruction" << std::endl;
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
    for (auto noun = 0; noun < 100; noun++)
    {
        for (auto verb = 0; verb < 100; verb++)
        {
            auto result = execute_codes(codes, noun, verb);
            if (result == 19690720)
            {
                std::cout << 100 * noun + verb << std::endl;
                return 0;
            }
        }
    }
}
