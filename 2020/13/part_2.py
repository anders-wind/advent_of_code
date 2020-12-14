"""
day 13
"""


def read_input(file_path):
    with open(file_path, 'r') as file_handle:
        lines = file_handle.readlines()
        busses = []
        for bus in lines[1].strip().split(","):
            if bus != "x":
                busses.append(int(bus))
            else:
                busses.append(1)
        return busses


def find_offset(first_bus, later_buss, offset):
    if later_buss == 1:
        return offset + 1
    for x in range(offset + 1, first_bus * later_buss, first_bus):
        if (x % later_buss) == 0:
            return x

    raise Exception("no")


def solve(busses):
    step = busses[0]
    offset = 0
    for i in range(1, len(busses)):
        offset = find_offset(step, busses[i], offset)
        step = step * busses[i]
    return offset - len(busses) + 1


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()