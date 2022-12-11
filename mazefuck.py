#!/usr/bin/env python3

import sys
from enum import Enum
from readchar import readkey

CHAR_START = "^"
CHAR_END = "$"
CHAR_WALL = "#"
CHAR_EMPTY = "."
CHAR_VALID = {CHAR_START, CHAR_END, CHAR_WALL, CHAR_EMPTY}


class Steering(Enum):
    LEFT = 0
    RIGHT = 1


def check_maze(maze: list[str]):
    characters = set("".join(maze))

    # Check if all line has the same length
    if len(set(map(len, maze))) != 1:
        raise ValueError("All lines must have the same length")

    # Check if the maze has one start and one end
    count_start = "".join(maze).count(CHAR_START)
    count_end = "".join(maze).count(CHAR_END)
    if count_start != 1 or count_end != 1:
        raise ValueError("Maze must have only one start and one end")

    # Check if the maze has only valid characters
    if characters - CHAR_VALID:
        raise ValueError("Maze must only contain valid characters")


def find_startpoint(maze: list[str]) -> tuple[int, int]:
    for y, line in enumerate(maze):
        if CHAR_START in line:
            return line.index(CHAR_START), y
    raise ValueError("Maze must have one start point")


def find_endpoint(maze: list[str]) -> tuple[int, int]:
    for y, line in enumerate(maze):
        if CHAR_END in line:
            return line.index(CHAR_END), y
    raise ValueError("Maze must have one end point")


# Find the path from start to end by BFS
def find_path(maze: list[str], start: tuple[int, int], end: tuple[int, int]):
    queue = [(start, [])]
    visited = set()
    while queue:
        (x, y), path = queue.pop(0)
        if (x, y) in visited:
            continue
        visited.add((x, y))
        if (x, y) == end:
            return path
        for dx, dy in ((-1, 0), (1, 0), (0, 1), (0, -1)):
            nx, ny = x + dx, y + dy
            if (
                0 <= nx < len(maze[0])
                and 0 <= ny < len(maze)
                and maze[ny][nx] != CHAR_WALL
            ):
                queue.append(((nx, ny), path + [(dx, dy)]))


def path_to_steering(path: list[tuple[int, int]]) -> list[Steering]:
    left = (((1, 0), (0, -1)), ((0, 1), (1, 0)), ((-1, 0), (0, 1)), ((0, -1), (-1, 0)))
    right = (((1, 0), (0, 1)), ((0, 1), (-1, 0)), ((-1, 0), (0, -1)), ((0, -1), (1, 0)))

    steering = []
    if len(path) < 2:
        return steering
    dx, dy = path[1][0] - path[0][0], path[1][1] - path[0][1]
    for i in range(1, len(path)):
        dxi, dyi = path[i]
        if ((dx, dy), (dxi, dyi)) in left:
            steering.append(Steering.LEFT)
        elif ((dx, dy), (dxi, dyi)) in right:
            steering.append(Steering.RIGHT)
        dx, dy = dxi, dyi
    return steering


def steering_to_bf(steering: list[Steering]) -> str:
    if len(steering) % 3 != 0:
        raise ValueError("Steering must be divisible by 3")
    bf_map = {
        (Steering.LEFT, Steering.LEFT, Steering.LEFT): ">",
        (Steering.LEFT, Steering.LEFT, Steering.RIGHT): "<",
        (Steering.LEFT, Steering.RIGHT, Steering.LEFT): "+",
        (Steering.LEFT, Steering.RIGHT, Steering.RIGHT): "-",
        (Steering.RIGHT, Steering.LEFT, Steering.LEFT): ".",
        (Steering.RIGHT, Steering.LEFT, Steering.RIGHT): ",",
        (Steering.RIGHT, Steering.RIGHT, Steering.LEFT): "[",
        (Steering.RIGHT, Steering.RIGHT, Steering.RIGHT): "]",
    }
    bf = ""
    for i in range(0, len(steering), 3):
        bf += bf_map[tuple(steering[i : i + 3])]
    return bf


def execute_bf(bf: str):
    cells = [0 for _ in range(30000)]
    ptr = 0
    ctx = 0
    while ctx < len(bf):
        if bf[ctx] == ">":
            if ptr == 29999:
                raise ValueError("Pointer out of range")
            ptr += 1
        elif bf[ctx] == "<":
            if ptr == 0:
                raise ValueError("Pointer out of range")
            ptr -= 1
        elif bf[ctx] == "+":
            cells[ptr] = 0 if cells[ptr] == 255 else cells[ptr] + 1
        elif bf[ctx] == "-":
            cells[ptr] = 255 if cells[ptr] == 0 else cells[ptr] - 1
        elif bf[ctx] == ".":
            print(chr(cells[ptr]), end="")
        elif bf[ctx] == ",":
            cells[ptr] = ord(readkey())
        elif bf[ctx] == "[":
            if cells[ptr] == 0:
                ctx += bf[ctx:].index("]") - 1
        elif bf[ctx] == "]":
            if cells[ptr] != 0:
                ctx = bf[:ctx].rindex("[") - 1
        ctx += 1


if __name__ == "__main__":
    mf: list[str] = []
    while True:
        line = sys.stdin.readline().rstrip()
        if len(line) == 0:
            break
        mf.append(line)
    check_maze(mf)
    path = find_path(mf, find_startpoint(mf), find_endpoint(mf))
    steering = path_to_steering(path)
    bf = steering_to_bf(steering)
    execute_bf(bf)
