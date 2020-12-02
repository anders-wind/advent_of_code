from part_1 import read_input


def solve(data) -> int:
    total_passed = 0
    for minimum, maximum, char, password in data:
        occurence = 1 if password[minimum - 1] == char else 0
        occurence += 1 if password[maximum - 1] == char else 0
        if occurence == 1:
            total_passed += 1

    return total_passed


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()