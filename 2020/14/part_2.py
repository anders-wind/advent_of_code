"""
day 14
"""
from part_1 import read_input, get_or_mask, num_bits


def get_indices_of_x(bitstr):
    return [num_bits - i - 1 for i, x in enumerate(bitstr) if x == "X"]


def solve(data):
    current_one_writer = 0
    current_float_indices = []
    memory = {}
    for action, argument in data:
        if action == "mask":
            current_one_writer = get_or_mask(argument, "1")
            current_float_indices = get_indices_of_x(argument)
        else:
            address, value = argument
            if address not in memory:
                memory[address] = 0

            address |= (current_one_writer)
            for combi in range(1 << len(current_float_indices)):
                float_adress = address
                for idx in range(len(current_float_indices)):
                    i = current_float_indices[idx]
                    if ((combi >> idx) & 1) == 1:
                        float_adress |= (1 << (i))
                    else:
                        float_adress &= ~(1 << (i))
                memory[float_adress] = value

    return sum(memory.values())


def main():
    print(solve(read_input("sample_2.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()