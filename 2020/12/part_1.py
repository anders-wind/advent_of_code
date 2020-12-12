"""
day 12
"""
import math


def read_input(file_path):
    res = []
    with open(file_path, 'r') as file_handle:
        for line in file_handle.read().splitlines():
            action = line[0]
            argument = int(line[1:])
            res.append((action, argument))
    return res


north = 0
east = 1
south = 2
west = 3


def rotate(direction, degrees):
    return (direction + (degrees // 90)) % 4


def manhatten(pos_y, pos_x, o_y, o_x):
    return abs(o_y - pos_y) + abs(o_x - pos_x)


def solve(data):
    start_direction = east
    start_y = 0
    start_x = 0

    pos_y = start_y
    pos_x = start_x
    direction = start_direction
    for action, argumnet in data:
        # print(f"({pos_y}, {pos_x}) {direction}")
        if action == 'N':
            pos_y += argumnet
        elif action == "S":
            pos_y -= argumnet
        elif action == "E":
            pos_x += argumnet
        elif action == "W":
            pos_x -= argumnet
        elif action == "L":
            direction = rotate(direction, -argumnet)
        elif action == "R":
            direction = rotate(direction, argumnet)
        elif action == "F":
            modifier = int(math.copysign(1, -(direction - 1.5)))
            if (direction % 2) == 0:
                pos_y += modifier * argumnet
            else:
                pos_x += modifier * argumnet

    # print(f"({pos_y}, {pos_x})")
    return manhatten(pos_y, pos_x, start_y, start_x)


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()
