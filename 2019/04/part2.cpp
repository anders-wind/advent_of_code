#include <math.h> 
#include <iostream>
#include <optional>
#include <array>

int get_digit(int number, int digit) {
    return static_cast<int>(number/pow(10,digit))%10;
}

bool meets_criteria(int number) {
    auto digit = get_digit(number, 0);
    auto counts = std::array<int, 10>();
    counts[digit]++;

    for(auto i = 1; i<6; i++) {
        const auto next_digit = get_digit(number, i);
        if(digit < next_digit){
            return false;
        }
        counts[next_digit]++;
        digit = next_digit;
    }

    auto result = false;
    for(auto elem : counts) {
        if(elem == 2){
            result = true;
        }
    }
    return result;
}

int main()
{
    const auto from = 246515; 
    const auto to = 739105;

    std::cout << (meets_criteria(112233) == true) << std::endl;
    std::cout << (meets_criteria(123444) == false) << std::endl;
    std::cout << (meets_criteria(111122) == true) << std::endl;
    std::cout << (meets_criteria(112222) == true) << std::endl;
    std::cout << (meets_criteria(112211) == false) << std::endl;
    std::cout << (meets_criteria(112221) == false) << std::endl;
    std::cout << (meets_criteria(111111) == false) << std::endl;
    std::cout << (meets_criteria(111222) == false) << std::endl;
    std::cout << (meets_criteria(112345) == true) << std::endl;
    std::cout << (meets_criteria(123345) == true) << std::endl;
    std::cout << std::endl;

    auto number_of_valid_passwords = 0;
    for(auto i = from; i<= to; i++) {
        if(meets_criteria(i)) {
            number_of_valid_passwords++;
        }
    }
    std::cout << number_of_valid_passwords << std::endl;
}