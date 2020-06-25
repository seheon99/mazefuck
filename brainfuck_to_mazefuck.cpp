/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brainfuck_to_mazefuck.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seyu <seyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 05:49:11 by seyu              #+#    #+#             */
/*   Updated: 2020/06/25 12:09:26 by seyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include "mazegen.hpp"

using namespace std;

static bool		is_brainfuck(const char ch)
{
	return (ch == '<' || ch == '>' || ch == '+' || ch == '-'
			|| ch == '.' || ch == ',' || ch == '[' || ch == ']');
}

static bool		is_brainfuck(string str)
{
	for (char ch : str)
		if (!is_brainfuck(ch))
			return (false);
	return (true);
}

static string	file_to_string(ifstream &input_file)
{
	string	line = "";
	string	brainfuck = "";

	if (!input_file.is_open())
		return (NULL);
	while (getline(input_file, line))
		brainfuck += line;
	return (brainfuck);
}

static string	brainfuck_to_binary(string brainfuck)
{
	string	binary = "";

	for (char command : brainfuck)
	{
		if (command == '>')
			binary += "000";
		else if (command == '<')
			binary += "001";
		else if (command == '+')
			binary += "010";
		else if (command == '-')
			binary += "011";
		else if (command == '.')
			binary += "100";
		else if (command == ',')
			binary += "101";
		else if (command == '[')
			binary += "110";
		else if (command == ']')
			binary += "111";
	}
	return (binary);
}

static void		binary_to_map(ofstream &output_file, string set, string binary)
{
	Mazegen	maze(set, binary);

	output_file << set[0] << set[1] << set[3] << endl;
	for (size_t itr_y = 0; itr_y < maze.mapsize_y; itr_y++)
	{
		for (size_t itr_x = 0; itr_x < maze.mapsize_x; itr_x++)
			output_file << maze.map[itr_y][itr_x];
		output_file << endl;
	}
}

int				main(int argc, char **argv)
{
	if (argc == 1 || argc == 2)
		cout << "[Error] No input files or brainfuck code" << endl;
	else if (argc > 3)
		cout << "[Error] Too many arguments" << endl;
	else
	{
		ifstream	input_file;
		ofstream	output_file;
		string		brainfuck;
		string		binary;
		string		output_file_name;

		if (string(argv[1]).size() != 4)
		{
			cout << "[Error] Invalid character set" << endl;
			return (-1);
		}
		if (is_brainfuck(argv[2]))
		{
			brainfuck = argv[2];
			output_file_name = "a.mf";
		}
		else
		{
			input_file.open(argv[2]);
			if (!input_file.is_open())
			{
				cout << "[Error] No such files or invalid brainfuck code" << endl;
				return (-1);
			}
			brainfuck = file_to_string(input_file);
			input_file.close();
			if (string(argv[2]).find('.') == string::npos)
				output_file_name = string(argv[2]) + ".mf";
			output_file_name = string(argv[2]).substr(0, string(argv[2]).find_last_of('.')) + ".mf";
		}
		binary = brainfuck_to_binary(brainfuck);
		if (binary.empty())
		{
			cout << "[Error] Empty brainfuck code" << endl;
			return (-1);
		}
		output_file.open(output_file_name, ios::trunc);
		binary_to_map(output_file, argv[1], binary);
		output_file.close();
	}
}
