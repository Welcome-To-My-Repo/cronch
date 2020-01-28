#include "cronch.h"

int main (int argc, char **argv)
{
//initialize variables
		std::string start_string, working, all32bits, leftovers, temp;
		std::istringstream working_input;
		std::ostringstream working_output;
		std::bitset <32>* all8char;
		std::bitset <8> charset[4];
		char readin [4], get[1];
		bool is_leftovers;
		uint32_t	original,
				dividend,
				remainder,
				prime,
				difference,
				factorProduct = 1,
				totalremainder = 0,
				start_input_size;
		bool factoring = true;
		std::vector <int> factors;
		std::vector <int> run_comp_factors (15, 0);
		std::bitset <4> write_factors [2];
		std::bitset <8> *writeout;
		uint64_t to_char_convert;
		char cronchPUT[1];
		std::bitset <8> *short_out;
		std::bitset <16> *long_out_16;
		std::bitset <32> *long_out_32;
		int counter, filesize;
		long int passes = 0;
		bool is_factoring, not_small = true;
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
//create file input and output streams
	std::ifstream cronchIN;
	std::ofstream cronchOUT;

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
