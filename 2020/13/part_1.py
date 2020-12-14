"""
day 13
"""


def read_input(file_path):
    with open(file_path, 'r') as file_handle:
        lines = file_handle.readlines()
        arrival = int(lines[0].strip())
        busses = []
        for bus in lines[1].strip().split(","):
            if bus != "x":
                busses.append(int(bus))
        return (arrival, busses)


def solve(arrival, busses):
    def find_first_bus():
        timestamp = arrival
        while True:
            for bus in busses:
                if (timestamp % bus) == 0:
                    return bus, timestamp
            timestamp += 1

    bus, timestamp = find_first_bus()
    return bus * (timestamp - arrival)


def main():
    print(solve(*read_input("sample.txt")))
    print(solve(*read_input("input.txt")))


if __name__ == "__main__":
    main()