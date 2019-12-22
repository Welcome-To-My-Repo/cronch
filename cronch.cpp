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
				start_input_size,
				filesize;
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
		int short_counter;
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
//read entire file into a string
		while (cronchIN.read (cronchPUT, 1));
		{
			start_string.push_back (cronchPUT[0]);
		}
//get length of initial input string
		start_input_size = start_string.size ();
		filesize = start_input_size;
//put string into string stream
		working_input.str (start_string);
		while (not_small)
		{
//check if size of input is a multiple of 4
			if (input_size < 4)
			{
				std::cout << "filesize is too small" << std::endl;
				return 7;
			}
			else if (input_size%4 == 0)
			{
				filesize = filesize/4;
				is_leftovers = false;
			}
			else
			{
				filesize = 1 + (filesize/4);
				is_leftovers = true;
			}
//read in 4 bytes from the stream
			for (int i = 0; i < filesize; i ++)
			{
				all32bits.clear ();
				factors.clear ();
				temp.clear ();
				is_factoring = true;
				factors.clear ();
				for (int a = 0; a < 4; a ++)
				{
					readin[a] = -1;
				}
				if (i == filesize - 1 and is_leftovers)
				{
					while (working_input.get (get, 1));
						working_output.write (get, 1);
					break;
				}
				else
				{
					working_input.read (readin, 4);
				}
				for (int i = 0; i < 4; i++)
					charset[i] = std:;bitset <8> (readin[i]);
				for (int i = 0; i < 4; i ++)
					all32bits.append (charset[i].to_string ());
				all8char = new std::bitset <32> (all32bits.c_str ());
				original = all8char->to_ullong ();
				dividend = original;
				remainder = dividend%primes[14];
				prime = 14;
				factorProduct = 1;
				factoring = true;
				while (factoring)
				{
					for (int a = 14; a > -1; a --)
						if (primes[a] == dividend)
						{
							factors.push_back (a);
							std::cout << primes[a] << " ";
							factorProduct = factorProduct * primes[a];
							factoring = false;
							break;
						}
					if (!factoring)
						continue;
					for (int a = 14; a > -1; a --)
					{
						if (dividend%primes[a] < remainder)
						{
							prime = a;
						}
					}
					std::cout << primes[prime] << ", ";
					dividend = dividend/primes[prime];
					factors.push_back (prime);
					factorProduct = factorProduct * primes[prime];
				}
				difference = original - factorProduct;
				for (int j = 0; j < factors.size (); j ++)
				{
					run_comp_factors.at (factors.at (j)) ++;
				}
				if (difference > 0)
				{
					if (difference > UINT8_MAX)
					{
						if (difference > UINT16_MAX)
						{
							cronchPUT[0] = 3;
							working_output.write (cronchPUT, 1);
							long_out_32 = new std::bitset <32> (difference);
							short_out = new std::bitset <8> ();
							for (int i = 0; i < 4; i++)
							{
								
							}
						}
					}
				}
			}
//turn each of the bytes into an 8 bit bitset
//append each bitset in order to a binary string
//turn the binary string into a 32 bit bitset
//turn the 32 bit bitset into a 32 bit integer

//start factoring the integer
//if the integer equals one of the prime numbers...
//add the dividend to the factors list
//exit the while loop
//divide the dividend by the prime number with the smallest modulu result
//add the prime with the smallest modulo to the factors list
//multiply the factor product by the new prime

//loop through the factors list to count the similar factors
//incrememt the number of occurrances of a factor

//get the difference between the original dividend and the factor product
//make a 4 bit zero value
//make a 4 bit value corresponding to 0, 8, 16, or 32 bits with 0, 1, 2, 3
//create a byte with the first 4 being the zero and the second 4 bits being the number
//write the byte out
//write out the difference that was recorded earlier

//loop through the list of factor occurances
//if the occurances is more than zero
//check if the occurances is greater than 15
//write out a byte with the value 15 and then the list position
//check if the number of occurances is not a multiple of 15
//write out a byte with the remainder of the occurances / 15 and then the list position
//write out a byte with the number of occurances and then the list position

//move the output stream into a string
//if the size of the output string isn't small enough repeat the entire process
//write out the entire string to a file
	}
	else
	{
	}

	return 0;
}
