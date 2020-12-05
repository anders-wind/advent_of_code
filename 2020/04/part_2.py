"""
day 4
"""
from typing import List, Optional
from part_1 import Passport, read_input


def solve(passports: List[Passport]):
    num_valid = 0

    def is_valid(passport) -> bool:
        def height(height: str):
            if height.endswith("cm"):
                return 150 <= int(height[:-2]) <= 193
            if height.endswith("in"):
                return 59 <= int(height[:-2]) <= 76
            return False

        def hair_color(color):
            try:
                res = color[0] == '#'
                for char in color[1:]:
                    res &= char in {
                        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
                        'b', 'c', 'd', 'e', 'f'
                    }
                return res
            except:
                return False

        def eye_color(color: str):
            valids = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"}
            return color in valids

        def pass_id(id: str):
            try:
                return len(id) == 9 and int(id) >= 0
            except:
                return False

        byr_v = passport.byr is not None and 1920 <= int(passport.byr) <= 2002
        iyr_v = passport.iyr is not None and 2010 <= int(passport.iyr) <= 2020
        eyr_v = passport.eyr is not None and 2020 <= int(passport.eyr) <= 2030
        hgt_v = passport.hgt is not None and height(passport.hgt)
        hcl_v = passport.hcl is not None and hair_color(passport.hcl)
        ecl_v = passport.ecl is not None and eye_color(passport.ecl)
        pid_v = passport.pid is not None and pass_id(passport.pid)

        return byr_v and iyr_v and eyr_v and hgt_v and hcl_v and ecl_v and pid_v

    for passport in passports:
        num_valid += is_valid(passport)
    return num_valid


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("valids.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()