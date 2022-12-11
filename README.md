# Mazefuck

Mazefuck is a language inspired by [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) and [Befunge](https://en.wikipedia.org/wiki/Befunge). It is inspired by the fact that Brainfuck's commands can be represented in binary with three digits and that Befunge can pass commands through the flow of coordinates on a two-dimensional plane.

Like Brainfuck, Mazefuck uses a 30,000-byte array initialized to 0 and a pointer to the first byte of the array. However, Mazefuck uses a map with a start point and an end point. Through the map, Mazefuck calculate the shortest path and replaces left turns with `0` and right turns with `1` to combine commands. The following table shows the meaning of the commands in Mazefuck.

| MazeFuck | Meaning                                                                              |
| -------- | ------------------------------------------------------------------------------------ |
| `000`    | Move the pointer to the right                                                        |
| `001`    | Move the pointer to the left                                                         |
| `010`    | Increase the value of the byte the pointer is pointing to                            |
| `011`    | Decrease the value of the byte the pointer is pointing to                            |
| `100`    | Output the value of the byte the pointer is pointing to as an ASCII char             |
| `101`    | Input a character and store it in the cell at the pointer                            |
| `110`    | If the value of the byte the pointer is pointing to is `0`, move to `]` or `111`     |
| `111`    | If the value of the byte the pointer is pointing to is not `0`, move to `[` or `110` |

If there are multiple shortest paths, the first path in the order of (right, left, down, up) is considered the shortest path. For example, if the path is (right, down, down, left) and (left, down, down, right), the right is considered to have a higher priority than the left, so (right, down, down, left) is considered the shortest path.

The map must be a rectangle shape that includes the wall, the start point, the end point, and the empty space. The wall is represented by `#`, the start point is represented by `^`, the end point is represented by `$`, and the empty space is represented by `.`.

## Usage

`mazefuck.py` is a Python script that execute the Mazefuck code. The following command executes the code in `input.mf`.

```sh
$ ./mazefuck < input.mf
```

It waits for empty input to execute. You can input some characters after the code is executed.

## Examples

- The following code print `42`.

```mf
#########################################
####..................................###
####.################################.###
####.#..............................#.###
####.#.############################.#.###
####.#.##........................##.#.###
####.#.##.######################.##.#.###
####.#.#..##..................##..#.#.###
####.#.#.#...################...#.#.#.###
####.#.#.#.####################.#.#.#.###
####.#.#.#.##.................#.#.#.#.###
####.#.#.#.##.###############.#.#.#.#.###
####.#.#.#.##.#.............#.#.#.#.#.###
####.#.#.#.##.#.###########.#.#.#.#.#.###
####.#.#.#.##.#.####....###.#.#.#.#.#.###
####.#.#.#.##.#.####.##.###.#.#.#.#.#.###
####.#.#.#.##.#.####..#..##.#.#.#.#.#.###
####.#.#.#.##.#.#$.##.##.##.#.#.#.#.#.###
####.#.#.#.##.#.##.##.##.##.#.#.#.#.#.###
####.#.#.#.##.#.#..#..##..#.#.#.#.#.#.###
####.#.#.#.##.#.#.##.####.#.#.#.#.#.#.###
####.#.#.#.##.#.#....####.#.#.#.#.#.#.###
####.#.#.#.##.#.#########.#.#.#.#.#.#.###
####.#.#.#.##.#......###..#.#.#.#.#.#.###
####.#.#.#.##.######.....##.#.#.#.#.#.###
####.#.#.#.##.#############.#.#.#.#.#.###
####.#.#.#.##.#.............#.#.#.#.#.###
####.#.#.#.##.#.#############.#.#.#.#.###
####.#.#.#.#..#...............#.#.#.#.###
####.#.#.#...##################.#.#.#.###
####.#.#..###################...#.#.#.###
####.#.##.....................##..#.#.###
####.#.#########################.##.#.###
####.#...........................##.#.###
####.##############################.#.###
#^#..#..............................#...#
#.#.##.################################.#
#.#.##..............................###.#
#.#.###############################...#.#
#.#.#################################.#.#
#.#..##############################...#.#
#.##................................###.#
#...#################################...#
###...................................###
#########################################
```
