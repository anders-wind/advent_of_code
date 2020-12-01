from pathlib import Path


def read_ints(file_path):
    res = set({})
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            res.add(int(line))
    return res


def calculate_result(file_path):
    numbers = read_ints(file_path)
    for number in numbers:
        opposite = 2020 - number
        if opposite in numbers:
            print(number * opposite)
            return

    raise Exception("Could not find combi")


def main():
    calculate_result(Path(__file__).parent / Path("sample.txt"))
    calculate_result(Path(__file__).parent / Path("input.txt"))


if __name__ == "__main__":
    main()