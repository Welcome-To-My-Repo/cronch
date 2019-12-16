#include "cronch.h"

int main (int argc, char **argv)
{
//initialize variables
		std::string all64bits, leftovers, temp;
		std::bitset <32>* all8char;
		std::bitset <8> charset[4];
		char readin [4], get[1];
		bool is_leftovers;
		uint32_t original, dividend, remainder, prime, difference, factorProduct = 1, totalremainder = 0;
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
		bool is_factoring;
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
//get the size of the input file
	cronchIN.seekg (0, cronchIN.end);
	long long int filesize = cronchIN.tellg ();
	std::cout << "filesize: " << filesize << std::endl;
	cronchIN.seekg (cronchIN.beg);
//if arguments was for compression, compress the input file
	if (argv[1][0] == 'c')
	{
//check if filesize can be completely sectioned into 8 byte blocks
//if not, adjust number of blocks to be compressed
			if (filesize%8 == 0)
			{
				filesize = filesize/8;
				is_leftovers = false;
			}
			else
			{
				filesize = 1 + filesize/8;
				is_leftovers = true;
			}
			std::cout << "adjusted repetitions: " << filesize << std::endl;
//this loops once to process each 8 byte block from the file
		for (int i = 0; i < filesize; i ++)
		{
			std::cout << "loop start" << std::endl;
			all64bits.clear ();
			factors.clear ();
			temp.clear ();
			is_factoring = true;
			factors.clear ();
			//run_comp_factors.clear ();
//set the input string to default
			for (int a = 0; a < 8; a++)
				readin[a] = -1;
//check if 8 bytes can still be read from the file;
			if (i == filesize - 1 and is_leftovers)
			{
				while (cronchIN.get (get, 1))
					cronchOUT.write (get, 1);
				break;
			}
			else
			{
//read in 8 bytes
				cronchIN.read (readin, 8);
			}
			std::cout << "8 byte block: " << readin << std::endl;
//separate the 8 bytes
				for (int i = 0; i < 8; i ++)
					charset [i] = std::bitset <8> (readin[i]);
//take the binary representation of each byte and combine them into a 64 bit binary value
				for (int i = 0; i < 8; i++)
					all64bits.append (charset[i].to_string ());
//put the 64 bit binary value into a bitset class because...
				all8char = new std::bitset <64> (all64bits.c_str ());
//convert the binary representation to a 64 bit integer
				original = all8char->to_ullong ();
//duplicate to preserve the initial value
				dividend = original;
//factor the value by small prime numbers
				remainder = dividend%primes[14];
				prime = 14;
				factorProduct = 1;
				while (factoring)
				{
					for (int a = 14; a > -1; a --)
						if (primes[a] == dividend)
							break;
					for (int a = 14; a > -1; a --)
					{
						if (dividend%primes[a] < remainder)
						{
							prime = a;
						}
					}
					dividend = dividend/primes[prime];
					factors.push_back (prime);
					factorProduct = factorProduct * primes[prime];
				}
				difference = original - factorProduct;
//combine same factors
				for (int j = 0; j < factors.size (); j ++)
				{
					run_comp_factors.at (factors.at (j)) ++;
				}
				for (int j = 0; j < 15; j ++)
				{
					if (run_comp_factors.at (j) != 0)
					{
						if (run_comp_factors.at (j) > 15)
						{
							for (int a = 0; a < run_comp_factors.at (j)/15; a ++)
							{
								temp.clear ();
								write_factors[0] = std::bitset<4> (15);
								write_factors[1] = std::bitset<4> (j);
								temp.push_back (write_factors[0].to_string ());
								temp.push_back (write_factors[1].to_string ());
								writeout = new std::bitset<8> (temp.c_str ());
								cronchPUT[0] = (char)writeout->to_ulong ();
								cronchOUT.write (cronchPUT, 1);
							}
							temp.clear ();
							write_factors[0] = std::bitset<4> (run_comp_factors.at(j)-(15 * (run_comp_factors.at(j)/15)));
							write_factors[1] = std::bitset<4> (j);
							temp.push_back (write_factors[0].to_string ());
							temp.push_back (write_factors[1].to_string ());
							writeout = new std::bitset<8> (temp.c_str ());
							cronchPUT[0] = (char)writeout->to_ulong ();
							cronchOUT.write (cronchPUT, 1);
						}
						else
						{
							temp.clear ();
							write_factors[0] = std::bitset <4> (run_comp_factors.at (j));
							write_factors[1] = std::bitset <4> (j);
							temp.push_back (write_factors[0].to_string ());
							temp.push_back (write_factors[1].to_string ());
							writeout = new std::bitset<8> (temp.c_str ());
							cronchPUT[0] = (char)writeout->to_ulong ();
							cronchOUT.write (cronchPUT, 1);
						}
					}
				}
//append the leftover really big prime number
				if (dividend > 0)
				{
					if (dividend > UINT8_MAX)
					{
						if (dividend > UINT16_MAX)
						{
							cronchPUT[0] = 3;
							cronchOUT.write (cronchPUT, 1);
							long_out_32 = new std::bitset<32> (dividend);
							short_out = new std::bitset <8> ();
							for (int i = 24; i < 32; i++)
							{
								(*short_out)[i] = (*long_out_32)[i];
							}
							to_char_convert = short_out->to_ullong ();
							cronchPUT[0] = (char)to_char_convert;
							cronchOUT.write (cronchPUT, 1);
							for (int i = 16; i < 24; i++)
							{
								(*short_out)[i] = (*long_out_32)[i];
							}
							to_char_convert = short_out->to_ullong ();
							cronchPUT[0] = (char)to_char_convert;
							cronchOUT.write (cronchPUT, 1);
							for (int i = 8; i < 16; i++)
							{
								(*short_out)[i] = (*long_out_32)[i];
							}
							to_char_convert = short_out->to_ullong ();
							cronchPUT[0] = (char)to_char_convert;
							cronchOUT.write (cronchPUT, 1);
							for (int i = 0; i < 8; i++)
							{
								(*short_out)[i] = (*long_out_32)[i];
							}
							to_char_convert = short_out->to_ullong ();
							cronchPUT[0] = (char)to_char_convert;
							cronchOUT.write (cronchPUT, 1);
						}
						else
						{
							cronchPUT[0] = 2;
							cronchOUT.write (cronchPUT, 1);
							long_out_16 = new std::bitset <16> (dividend);
							short_out = new std::bitset <8> ();
							for (int i = 8; i < 16; i++)
							{
								(*short_out)[i] = (*long_out_16)[i];
							}
							to_char_convert = short_out->to_ullong ();
							cronchPUT[0] = (char)to_char_convert;
							cronchOUT.write (cronchPUT, 1);
							for (int i = 0; i < 8; i++)
							{
								(*short_out)[i] = (*long_out_16)[i];
							}
							to_char_convert = short_out->to_ullong ();
							cronchPUT[0] = (char)to_char_convert;
							cronchOUT.write (cronchPUT, 1);
						}
					}
					else
					{
						cronchPUT[0] = 1;
						cronchOUT.write (cronchPUT, 1);
						cronchPUT[0] = (char)dividend;
						cronchOUT.write (cronchPUT, 1);
					}
				}
				else
				{
					cronchPUT[0] = 0;
					cronchOUT.write (cronchPUT, 1);
				}
			}
			cronchOUT.close ();
			cronchIN.close ();
	}
	else
	{
	}

	return 0;
}
