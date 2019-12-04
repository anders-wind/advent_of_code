#include <math.h> 
#include <iostream>
#include <optional>

int get_digit(int number, int digit) {
    return static_cast<int>(number/pow(10,digit))%10;
}

bool meets_criteria(int number) {
    auto digit = get_digit(number, 0);

    auto has_two_in_a_row = false;
    for(auto i = 1; i<6; i++) {
        const auto next_digit = get_digit(number, i);
        if(digit < next_digit){
            return false;
        }
        if(digit == next_digit) {
            has_two_in_a_row = digit;
        }
        digit = next_digit;
    }

    return has_two_in_a_row;
}

int main()
{
    const auto from = 246515; 
    const auto to = 739105;

    auto number_of_valid_passwords = 0;
    for(auto i = from; i<= to; i++) {
        if(meets_criteria(i)) {
            number_of_valid_passwords++;
        }
    }
    std::cout << number_of_valid_passwords << std::endl;
}