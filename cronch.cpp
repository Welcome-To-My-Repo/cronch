#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>

std::ifstream cronchFile;

std::vector <long long int> input_contents (256);

int main (int argc, char **argv)
{
//initialize variables
		std::ifstream cronchIN;
		std::ofstream cronchOUT;
		std::string start_string, working, all32bits, leftovers, temp;
		std::istringstream working_input;
		std::ostringstream working_output;
		
		long long int filesize;
		char readin [4], get[1];
//check arguments
	if (argc < 2)
	{
		std::cout << "No mode specified!" << std::endl;
		return 1;
	}
	if (argc < 3)
	{
		std::cout << "No stream to compress!" << std::endl;
		return 2;
	}
	if (argc < 4)
	{
		std::cout << "No output name given!" << std::endl;
		return 3;
	}
	if (argv[1][0] != 'c' and argv[1][0] != 'd')
	{
		std::cout << "Incorrect mode!" << std::endl;
		return 4;
	}

	cronchIN.open (argv[2], std::ios_base::in | std::ios_base::binary);
	cronchOUT.open (argv[3], std::ios_base::out | std::ios_base::binary);
	if (!cronchIN.is_open ())
	{
		std::cout << "Could not open input stream!" << std::endl;
		return 5;
	}
	if (!cronchOUT.is_open ())
	{
		std::cout << "Could not open output stream!" << std::endl;
		return 6;
	}
//if arguments was for compression, compress the input file
	if (argv[1][0] == 'c')
	{
		cronchIN.seekg (0, cronchIN.end);
		filesize = cronchIN.tellg ();
		cronchIN.seekg (0, cronchIN.beg);
//read entire file into a string
		for (int i = 0; i < filesize; i ++)
		{
			cronchIN.read (get, 1);
			start_string.push_back (get[0]);
		}
//get length of initial input string
		std::cout << "size of file: " << start_string.size () << " bytes" << std::endl;
		filesize = start_string.size ();
//put string into string stream
		working_input.str (start_string);
//start the cronch algorithm
		for (int i = 0; i < start_string.size (); i ++)
		{
			input_contents.at((int)start_string.at(i)) ++;
		}
		for (int i = 0; i < input_contents.size (); i ++)
			std::cout << input_contents.at(i) << " ";
		std::cout << std::endl;
	}

	return 0;
}
