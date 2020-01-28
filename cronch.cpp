#include "cronch.h"

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
			cronchIN.read (cronchPUT, 1);
			start_string.push_back (cronchPUT[0]);
		}
//get length of initial input string
		std::cout << "size of file: " << start_string.size () << " bytes" << std::endl;
		start_input_size = start_string.size ();
		filesize = start_input_size;
//put string into string stream
		working_input.str (start_string);

//start generating a neural network

	return 0;
}
