from part_1 import read_input


def calculate_result(numbers) -> int:
    for number_1 in numbers:
        for number_2 in numbers:
            opposite = 2020 - (number_1 + number_2)
            if opposite in numbers:
                return number_1 * number_2 * opposite

    raise Exception("Could not find combi")


def main():
    print(calculate_result(read_input("sample.txt")))
    print(calculate_result(read_input("input.txt")))


if __name__ == "__main__":
    main()