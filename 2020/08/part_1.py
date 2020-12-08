"""
day 8
"""


def read_input(file_path):
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle:
            operation, amt = line.strip().split(" ")
            res.append((operation, int(amt)))

    return res


def solve(data):
    visited = [False for _ in data]

    accumulator = 0
    current_pos = 0
    while 0 <= current_pos < len(data):
        current_op, current_amt = data[current_pos]
        if current_op == 'nop':
            current_pos += 1
        elif current_op == 'acc':
            accumulator += current_amt
            current_pos += 1
        elif current_op == 'jmp':
            current_pos += current_amt

        if visited[current_pos]:
            return accumulator

        visited[current_pos] = True

    print("never infinite looped")
    return accumulator


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()