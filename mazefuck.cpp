/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mazefuck.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:25:10 by seyu              #+#    #+#             */
/*   Updated: 2020/06/25 02:11:00 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maze.hpp"
#include <iostream>
#include <string>

using namespace std;

static int brainfuck(string command) {
    char *cells;
    char *pointer;

    cells = (char *)calloc(sizeof(char), 30000);
    pointer = cells;
    for (size_t itr = 0; itr < command.size(); itr++) {
        char ch = command[itr];
        switch (ch) {
        case ('>'):
            pointer++;
            break;
        case ('<'):
            pointer--;
            break;
        case ('+'):
            (*pointer)++;
            break;
        case ('-'):
            (*pointer)--;
            break;
        case ('.'):
            cout << (*pointer);
            break;
        case (','):
            cin >> (*pointer);
            break;
        case ('['):
            if ((*pointer) == 0) {
                ssize_t count = 0;
                while (itr < command.size()) {
                    if (command[itr] == '[')
                        count++;
                    else if (command[itr] == ']')
                        count--;
                    if (count == 0)
                        break;
                    itr++;
                }
                if (command[itr] != ']')
                    return (-1);
            }
            break;
        case (']'):
            if ((*pointer) != 0) {
                ssize_t count = 0;
                while (itr >= 0) {
                    if (command[itr] == ']')
                        count++;
                    else if (command[itr] == '[')
                        count--;
                    if (count == 0)
                        break;
                    itr--;
                }
                if (command[itr] != '[')
                    return (-1);
            }
            break;
        }
        if (pointer < cells || pointer >= cells + 30000)
            return (-1);
    }
    return (0);
}

static bool is_leftturn(const char prev, const char next) {
    if (prev == 'L' && next == 'D')
        return (true);
    else if (prev == 'D' && next == 'R')
        return (true);
    else if (prev == 'R' && next == 'U')
        return (true);
    else if (prev == 'U' && next == 'L')
        return (true);
    else
        return (false);
}

static bool is_rightturn(const char prev, const char next) {
    if (prev == 'L' && next == 'U')
        return (true);
    else if (prev == 'U' && next == 'R')
        return (true);
    else if (prev == 'R' && next == 'D')
        return (true);
    else if (prev == 'D' && next == 'L')
        return (true);
    else
        return (false);
}

static string path_to_binary(string path) {
    string binary = "";

    for (size_t itr = 0; itr < path.size() - 1; itr++) {
        if (is_leftturn(path[itr], path[itr + 1]))
            binary += '0';
        else if (is_rightturn(path[itr], path[itr + 1]))
            binary += '1';
    }
    return (binary);
}

static string binary_to_bf(string binary) {
    string brainfuck = "";

    for (size_t itr = 0; itr < (binary.size() / 3) * 3; itr += 3) {
        string substr = binary.substr(itr, 3);

        if (substr == "000")
            brainfuck += '>';
        else if (substr == "001")
            brainfuck += '<';
        else if (substr == "010")
            brainfuck += '+';
        else if (substr == "011")
            brainfuck += '-';
        else if (substr == "100")
            brainfuck += '.';
        else if (substr == "101")
            brainfuck += ',';
        else if (substr == "110")
            brainfuck += '[';
        else if (substr == "111")
            brainfuck += ']';
    }
    return (brainfuck);
}

int main(int argc, char **argv) {
    for (size_t itr = 1; itr < argc; itr++) {
        Maze *new_maze = new Maze(argv[itr]);
        if (new_maze->is_valid()) {
            string path;
            string binary;
            string bf_command;

            path = new_maze->solve();
            if (!path.empty()) {
                binary = path_to_binary(path);
                bf_command = binary_to_bf(binary);
                if (brainfuck(bf_command) == -1)
                    cout << "[ERROR] " << argv[itr] << ": Invalid command"
                         << endl;
            } else {
                cout << "[ERROR] " << argv[itr] << ": No answer" << endl;
            }
        } else
            cout << "[ERROR] " << argv[itr] << ": Invalid map" << endl;
        delete new_maze;
    }
}
