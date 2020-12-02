def read_input(file_path):
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle.read().splitlines():
            limits, char, password = line.split(" ")
            minimum, maximum = limits.split("-")
            char = char[:1]
            res.append((int(minimum), int(maximum), char, password))
    return res


def solve(data) -> int:
    total_passed = 0
    for minimum, maximum, char, password in data:
        count = password.count(char)
        if count >= minimum and count <= maximum:
            total_passed += 1

    return total_passed


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()