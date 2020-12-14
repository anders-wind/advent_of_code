"""
day 14
"""


def read_input(file_path):
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            action, _, argument = line.strip().split(" ")
            if action.startswith("mem"):
                position = int(action[4:-1])
                value = int(argument)
                res.append(("mem", (position, value)))
            else:
                res.append((action, argument))

    return res


num_bits = 36


def all_ones():
    return 2**(num_bits) - 1


def get_and_mask(bitstr, char):
    x = all_ones()
    for i, c in enumerate(bitstr):
        if c == char:
            x &= ~(1 << (num_bits - i - 1))
    return x


def get_or_mask(bitstr, char):
    x = 0
    for i, c in enumerate(bitstr):
        if c == char:
            x |= (1 << (num_bits - i - 1))
    return x


def solve(data):
    current_and_mask = all_ones()
    current_or_mask = 0
    memory = {}
    for action, argument in data:
        if action == "mask":
            current_and_mask = get_and_mask(argument, "0")
            current_or_mask = get_or_mask(argument, "1")
        else:
            address, value = argument
            if address not in memory:
                memory[address] = 0
            memory[address] = (value & current_and_mask) | current_or_mask

    return sum(memory.values())


def main():
    print(solve(read_input("sample_1.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()