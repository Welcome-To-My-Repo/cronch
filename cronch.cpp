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

		while (not_small)
		{
			//std::cout << "starting a pass..." << std::endl;
			passes ++;
			working.clear ();
			working_output.str ("");
//check if size of input is a multiple of 4
			if (filesize < 4)
			{
				std::cout << "filesize is too small" << std::endl;
				return 7;
			}
			else if (filesize%4 == 0)
			{
				filesize = filesize/4;
				is_leftovers = false;
			}
			else
			{
				std::cout << "filesize is not a multiple of 4" << std::endl;
				filesize = 1 + (filesize/4);
				is_leftovers = true;
			}
//read in 4 bytes from the stream
			for (int i = 0; i < filesize; i ++)
			{
				all32bits.clear ();
				factors.clear ();
				for (int i = 0; i < run_comp_factors.size (); i ++)
					run_comp_factors.at (i) = 0;
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
					charset[i] = std::bitset <8> (readin[i]);
				for (int i = 0; i < 4; i ++)
					all32bits.append (charset[i].to_string ());
				all8char = new std::bitset <32> (all32bits.c_str ());
				original = all8char->to_ullong ();
				////std::cout << "cronching: " << all8char->to_ullong () << std::endl;
				dividend = original;
				remainder = dividend%primes[14];
				prime = 14;
				factorProduct = 1;
				factoring = true;
				while (factoring)
				{
					if (dividend == 0)
						break;
					for (int a = 14; a > -1; a --)
						if (primes[a] == dividend)
						{
							factors.push_back (a);
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

							//std::cout << "writing 32 bits out...\t";
							cronchPUT[0] = 3;
							working_output.write (cronchPUT, 1);
							long_out_32 = new std::bitset <32> (difference);
							//std::cout << long_out_32->to_ullong () << std::endl;
							//std::cout << "\t\t\t" << 3 << std::endl;
							//std::cout << "\t\t\t" << "00000011" << std::endl;
							short_out = new std::bitset <8> ();
							for (int i = 3; i > -1; i--)
							{
								counter = 0;
								for (int j = 0 + (8 * i); j < 8 * (i + 1); j ++)
								{
									(*short_out)[counter] = (*long_out_32)[j];
									counter ++;
								}
								cronchPUT[0] = (char)short_out->to_ullong ();
								//std::cout << "\t\t\t" << short_out->to_ullong () << std::endl;
								//std::cout << "\t\t\t" << short_out->to_string () << std::endl;
								working_output.write (cronchPUT, 1);
							}
						}
						else
						{

							//std::cout << "writing 16 bits out...\t";
							cronchPUT[0] = 2;
							working_output.write (cronchPUT, 1);
							long_out_16 = new std::bitset <16> (difference);
							//std::cout << long_out_16->to_string () << std::endl;
							//std::cout << "\t\t\t" << 2 << std::endl;
							//std::cout << "\t\t\t" << "00000010" << std::endl;
							short_out = new std::bitset <8> ();
							for (int i = 1; i > -1; i--)
							{
								counter = 0;
								for (int j = 0 + (8 * 1); j < 8 * (i + 1); j++)
								{
									(*short_out)[counter] = (*long_out_16)[j];
									counter ++;
									//std::cout << (*short_out) << std::endl;
								}
								cronchPUT[0] = (char)short_out->to_ullong ();
								//std::cout << "\t\t\t" << short_out->to_ullong () << std::endl;
								//std::cout << "\t\t\t" << short_out->to_string () << std::endl;
								working_output.write (cronchPUT, 1);
							}
						}
					}
					else
					{
						//std::cout << "\t\t\t" << 1 << std::endl;
						//std::cout << "\t\t\t" << "00000001" << std::endl;
						cronchPUT[0] = 1;
						working_output.write (cronchPUT, 1);
						cronchPUT[0] = (char)difference;
						working_output.write (cronchPUT, 1);
					}
				}
				else
				{
					//std::cout << "\t\t\t" << 0 << std::endl;
					//std::cout << "\t\t\t" << "00000000" << std::endl;
					cronchPUT[0] = 0;
					working_output.write (cronchPUT, 1);
				}
				for (int j = 0; j < 15; j ++)
				{
					if (run_comp_factors.at (j) != 0)
					{
						//std::cout << "number of occurances for " << primes[j] << ": " << run_comp_factors.at (j) << std::endl;
						if (run_comp_factors.at (j) > 15)
						{
							for (int a = 0; a < run_comp_factors.at (j)/15; a ++)
							{
								temp.clear ();
								write_factors[0] = std::bitset<4> (15);
								write_factors[1] = std::bitset<4> (j);
								temp.append (write_factors[0].to_string ());
								temp.append (write_factors[1].to_string ());
								writeout = new std::bitset<8> (temp.c_str ());
								//std::cout << "writing one byte..." << writeout->to_string () << std::endl;
								cronchPUT[0] = (char)writeout->to_ullong ();
								working_output.write (cronchPUT, 1);
							}
							if (run_comp_factors.at (j)%15 > 0)
							{
								temp.clear ();
								write_factors[0] = std::bitset<4> (run_comp_factors.at (j) - (15 * (run_comp_factors.at (j) / 15)));
								write_factors[1] = std::bitset<4> (j);
								temp.append (write_factors[0].to_string ());
								temp.append (write_factors[1].to_string ());
								writeout = new std::bitset<8> (temp.c_str ());
								//std::cout << "writing one byte..." << writeout->to_string () << std::endl;
								cronchPUT[0] = (char)writeout->to_ullong ();
								working_output.write (cronchPUT, 1);
							}
						}
						else
						{
							temp.clear ();
							write_factors[0] = std::bitset<4> (run_comp_factors.at (j));
							write_factors[1] = std::bitset<4> (j);
							temp.append (write_factors[0].to_string ());
							temp.append (write_factors[1].to_string ());
							writeout = new std::bitset<8> (temp.c_str ());
							//std::cout << "writing one byte..." << writeout->to_string () << std::endl;
							cronchPUT[0] = (char)writeout->to_ullong ();
							working_output.write (cronchPUT, 1);
						}
					}
				}
			}
//check if output size is less than filesize
			working = working_output.str ();
			std::cout << working.size () << std::endl;
			break;
			if (working.size () < start_input_size)
			{
				std::cout << "output file is smaller" << std::endl;
				not_small = false;
			}
			else
			{
				std::cout << "output file is not smaller" << std::endl;
				not_small = false;
				working_input.str (working);
				filesize = working.size ();
			}
//			if (passes == UINT32_MAX)
			if (passes == 1)
			{
				std::cout << "reached maximum allowable passes" << std::endl;
				break;
			}
		}
		long_out_32 = new std::bitset<32> (passes);
		//std::cout << "appending number of passes..." << long_out_32->to_ullong () << std::endl;
		short_out = new std::bitset <8> ();
		for (int i = 3; i > -1; i--)
		{
			counter = 0;
			for (int j = 0 + (8 * i); j < 8 * (i + 1); j ++)
			{
				(*short_out)[counter] = (*long_out_32)[j];
				counter ++;
			}
			cronchPUT[0] = (char)short_out->to_ullong ();
			//std::cout << "\t\t\t" << short_out->to_ullong () << std::endl;
			//std::cout << "\t\t\t" << short_out->to_string () << std::endl;
			working.insert (0, cronchPUT);
		}
		for (int i = 0; i < working.size (); i ++)
		{
			cronchPUT[0] = working[i];
			cronchOUT.write (cronchPUT, 1);
		}

	}
	else
	{
	}

	return 0;
}
