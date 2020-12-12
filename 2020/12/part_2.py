"""
day 12
"""
import math
from part_1 import read_input, east, north, south, west, rotate, manhatten


def rotate(wayp_y, wayp_x, pos_y, pos_x, degrees):
    delta_wayp_y = wayp_y - pos_y
    delta_wayp_x = wayp_x - pos_x
    if degrees == 90:
        wayp_y = pos_y - delta_wayp_x
        wayp_x = pos_x + delta_wayp_y
    elif degrees == 180:
        wayp_y = pos_y - delta_wayp_y
        wayp_x = pos_x - delta_wayp_x
    elif degrees == 270:
        wayp_y = pos_y + delta_wayp_x
        wayp_x = pos_x - delta_wayp_y

    return wayp_y, wayp_x


def left_to_right(degrees):
    return 360 - degrees


def solve(data):
    start_y = 0
    start_x = 0

    wayp_y = 1
    wayp_x = 10
    pos_y = start_y
    pos_x = start_x
    for action, argumnet in data:
        print(f"{action}{argumnet} p({pos_y}, {pos_x}) w({wayp_y}, {wayp_x})")
        if action == 'N':
            wayp_y += argumnet
        elif action == "S":
            wayp_y -= argumnet
        elif action == "E":
            wayp_x += argumnet
        elif action == "W":
            wayp_x -= argumnet
        elif action == "L":
            wayp_y, wayp_x = rotate(wayp_y, wayp_x, pos_y, pos_x,
                                    left_to_right(argumnet))
        elif action == "R":
            wayp_y, wayp_x = rotate(wayp_y, wayp_x, pos_y, pos_x, argumnet)
        elif action == "F":
            delta_wayp_y = wayp_y - pos_y
            delta_wayp_x = wayp_x - pos_x
            pos_y += (wayp_y - pos_y) * argumnet
            pos_x += (wayp_x - pos_x) * argumnet
            wayp_y = pos_y + delta_wayp_y
            wayp_x = pos_x + delta_wayp_x
        print(f"res p({pos_y}, {pos_x}) w({wayp_y}, {wayp_x})")

    # print(f"({pos_y}, {pos_x})")
    return manhatten(pos_y, pos_x, start_y, start_x)


def main():
    print(solve(read_input("sample.txt")))
    print(solve(read_input("input.txt")))


if __name__ == "__main__":
    main()

# 10 units east and 4 units north
# 4 units east and 10 units south