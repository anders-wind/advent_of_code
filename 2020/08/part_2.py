"""
day 8
"""
from part_1 import read_input


def solve(data):
    for i, operation in enumerate(data):
        original_operation = operation
        if operation[0] == 'nop':
            data[i] = ('jmp', operation[1])
        elif operation[0] == 'jmp':
            data[i] = ('nop', operation[0])
        else:
            continue

        could_complete = True
        visited = [False for _ in data]
        accumulator = 0
        current_pos = 0
        while 0 <= current_pos < len(data):
            if visited[current_pos]:
                could_complete = False
                break

            visited[current_pos] = True

            current_op, current_amt = data[current_pos]
            if current_op == 'nop':
                current_pos += 1
            elif current_op == 'acc':
                accumulator += current_amt
                current_pos += 1
            elif current_op == 'jmp':
                current_pos += current_amt

        data[i] = original_operation
        if could_complete:
            return accumulator

    print("Could not complete")
    return 0


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()