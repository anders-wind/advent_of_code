"""
day 4
"""
from typing import List, Optional


class Passport:
    byr: Optional[str]  # (Birth Year)
    iyr: Optional[str]  # (Issue Year)
    eyr: Optional[str]  # (Expiration Year)
    hgt: Optional[str]  # (Height)
    hcl: Optional[str]  # (Hair Color)
    ecl: Optional[str]  # (Eye Color)
    pid: Optional[str]  # (Passport ID)
    cid: Optional[str]  # (Country ID)

    def __init__(self):
        self.byr = None
        self.iyr = None
        self.eyr = None
        self.hgt = None
        self.hcl = None
        self.ecl = None
        self.pid = None
        self.cid = None

    def __repr__(self) -> str:
        return f"(byr: {self.byr}, iyr: {self.iyr}, eyr: {self.eyr}, hgt: {self.hgt}, hcl: {self.hcl}, ecl: {self.ecl}, pid: {self.pid}, cid: {self.cid})\n"


def read_input(file_path) -> List[Passport]:
    res = []
    with open(file_path, 'r') as file_handle:
        current_passport = Passport()
        for line in file_handle:
            clean_line = line.strip()
            if (len(clean_line) == 0):
                res.append(current_passport)
                current_passport = Passport()
            else:
                for elements in clean_line.split(" "):
                    code, value = elements.split(":")

                    if code == "byr":
                        current_passport.byr = value
                    if code == "iyr":
                        current_passport.iyr = value
                    if code == "eyr":
                        current_passport.eyr = value
                    if code == "hgt":
                        current_passport.hgt = value
                    if code == "hcl":
                        current_passport.hcl = value
                    if code == "ecl":
                        current_passport.ecl = value
                    if code == "pid":
                        current_passport.pid = value
                    if code == "cid":
                        current_passport.cid = value
    res.append(current_passport)
    return res


def solve(passports: List[Passport]):
    num_valid = 0

    def is_valid(passport) -> bool:
        def valid(x) -> bool:
            return x is not None

        return valid(passport.byr) and valid(passport.iyr) and valid(
            passport.eyr) and valid(passport.hgt) and valid(
                passport.hcl) and valid(passport.ecl) and valid(passport.pid)

    for passport in passports:
        num_valid += is_valid(passport)
    return num_valid


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()