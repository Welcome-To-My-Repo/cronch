#include "cronch.h"

int main (int argc, char **argv)
{
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
//check if filesize can be completely sectioned into 8 byte blocks
//if not, adjust number of blocks to be compressed
	if (filesize%8 == 0)
		filesize = filesize/8;
	else
		filesize = 1 + filesize/8;
	std::cout << "adjusted repetitions: " << filesize << std::endl;
//if arguments was for compression, compress the input file
	if (argv[1][0] == 'c')
	{
//initialize the stuff
		std::string all64bits, leftovers, temp;
		std::bitset <64>* all8char;
		std::bitset <8> charset[8];
		char readin [8], get[1];
		bool is_leftovers = false;
		uint64_t original, dividend, remainder, prime, difference, factorProduct = 1, totalremainder = 0;
		bool factoring = true;
		std::vector <long long int> factors;
		std::vector <int> run_comp_factors (15, 0);
		std::bitset <4> write_factors [2];
		std::bitset <8> *writeout;
		uint64_t to_char_convert;
		char cronchPUT[1];
		std::bitset <8> *short_out;
		std::bitset <16> *long_out_16;
		std::bitset <32> *long_out_32;
		std::bitset <64> *long_out_64;
		int short_counter;
//this loops once to process each 8 byte block from the file
		for (int i = 0; i < filesize; i ++)
		{
			std::cout << "loop start" << std::endl;
			all64bits.clear ();
			factors.clear ();
			temp.clear ();
			bool is_factoring = true;
			factors.clear ();
			//run_comp_factors.clear ();
//set the input string to default
			for (int a = 0; a < 8; a++)
				readin[a] = -1;
//read in 8 bytes
			for (int i = 0; i < 8; i ++)
			{
//if it can't read in 8 bytes, save what it has to a "leftover" string and exit the loop
				if (!cronchIN.read (get, 1))
				{
					readin[i] = get[0];
					is_leftovers = true;
					for (int j = 0; j < 8; j ++)
					{
						if (readin[j] == -1)
							break;
						else if (readin[j] == '\n')
						{
							leftovers.push_back (readin[j]);
							break;
						}
						else
							leftovers.push_back (readin[j]);
					}
					break;
				}
				else
					readin[i] = get[0];
			}
//if it's at the end of the file and it can't get another 8 byte block, do stuff
			if (is_leftovers)
			{
				//std::cout << leftovers << std::endl;
				for (int b = 0; b < leftovers.size (); b ++)
				{
					cronchPUT[0] = leftovers[b];
					cronchOUT.write (cronchPUT, 1);
				}
			}
//if it's not at the end of the file, start the compression algorithm
			else
			{
//separate the 8 bytes
				for (int i = 0; i < 8; i ++)
					charset [i] = std::bitset <8> (readin[i]);
//take the binary representation of each byte and combine them into a 64 bit binary value
				for (int i = 0; i < 8; i++)
					all64bits.append (charset[i].to_string ());

				//std::cout << all64bits << std::endl;
//put the 64 bit binary value into a bitset class because...
				all8char = new std::bitset <64> (all64bits.c_str ());
//convert the binary representation to a 64 bit integer
				original = all8char->to_ullong ();
//duplicate to preserve the initial value
				dividend = original;
				//std::cout << "factoring dividend: " << dividend << std::endl;
//factor the value by small prime numbers
				while (factoring)
				{
					//std::cout << "current dividend: " << dividend << std::endl;
					factoring = false;
//check which prime is a factor
					for (int j = 14; j > -1; j--)
					{
						if (dividend%primes[j] == 0)
						{
							//std::cout << "factor: " << primes[j] << std::endl;
							factors.push_back (j);
							factoring = true;
							dividend = dividend/primes[j];
						}
					}
				}

				for (int i = 0; i < factors.size (); i ++)
					//std::cout << factors.at (i) << std::endl;
				//std::cout << dividend << std::endl;
//combine same factors
				for (int j = 0; j < factors.size (); j ++)
				{
					run_comp_factors.at (factors.at (j)) ++;
				}

				for (int i = 0; i < 15; i ++)
				{
					if (run_comp_factors.at(i) != 0)
						break;
						//std::cout << "compressed factor set: " << i << " - " << run_comp_factors.at (i) << std::endl;
				}
				for (int j = 0; j < 15; j ++)
				{
//if the prime factor is multiplied more than zero times do this stuff
					if (run_comp_factors.at (j) != 0)
					{
//if the prime factor is multiplied more than 15 (maximum 4 bit value) times do this stuff
						if (run_comp_factors.at (j) > 15)
						{
							int x = run_comp_factors.at (j);
							for (int k = 0; k < x/15; k ++)
							{
								temp.clear ();
								write_factors[0] = std::bitset<4> (15);
								write_factors[1] = std::bitset<4> (j);
								temp.push_back (write_factors[0].to_string ().c_str ()[0]);
								temp.push_back (write_factors[1].to_string ().c_str ()[0]);
								writeout = new std::bitset <8> (temp.c_str ());
								to_char_convert = writeout->to_ullong ();
								//std::cout << "writing to file: " << to_char_convert << " ";
								cronchPUT[0] = (char)to_char_convert;
								std::cout << cronchPUT[0] << std::endl;
								cronchOUT.write (cronchPUT, 1);

							}
							if (x%15 != 0)
							{
								temp.clear ();
								write_factors[0] = std::bitset<4> (x%15);
								write_factors[1] = std::bitset<4> (j);
								temp.push_back (write_factors[0].to_string ().c_str ()[0]);
								temp.push_back (write_factors[1].to_string ().c_str ()[0]);
								writeout = new std::bitset <8> (temp.c_str ());
								to_char_convert = writeout->to_ullong ();
								//std::cout << "writing to file: " << to_char_convert << " ";
								cronchPUT[0] = (char)to_char_convert;
								std::cout << cronchPUT[0] << std::endl;
								cronchOUT.write (cronchPUT, 1);
							}
						}
//if the prime factor is multiplied under 16 times do this stuff
						else
						{
							temp.clear ();
							write_factors[0] = std::bitset <4> (run_comp_factors.at (j));
							write_factors[1] = std::bitset <4> (j);
							std::string temp;
							//std::cout << " write factors: " << write_factors[0].to_string ().c_str () << " " << write_factors[1].to_string ().c_str () << std::endl;
							temp.append (write_factors[0].to_string ());
							temp.append (write_factors[1].to_string ());
							writeout = new std::bitset <8> (temp.c_str ());
							std::cout << writeout->to_string () << std::endl;
							to_char_convert = writeout->to_ullong ();
							//std::cout << "writing to file: " << to_char_convert << " ";
							cronchPUT[0] = (char)to_char_convert;
							std::cout << cronchPUT[0] << std::endl;
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
							if (dividend > UINT32_MAX)
							{
								std::cout << "writing 64 bit number" << std::endl;
								cronchPUT[0] = 4;
								cronchOUT.write (cronchPUT, 1);

								long_out_64 = new std::bitset<64> (dividend);
								short_out = new std::bitset <8> ();

								short_counter = 0;
								for (int i = 56; i < 64; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

								short_counter = 0;
								for (int i = 48; i < 56; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

								short_counter = 0;
								for (int i = 40; i < 48; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

								short_counter = 0;
								for (int i = 32; i < 40; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

								short_counter = 0;
								for (int i = 24; i < 32; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

								short_counter = 0;
								for (int i = 16; i < 24; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

								short_counter = 0;
								for (int i = 8; i < 16; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

								short_counter = 0;
								for (int i = 0; i < 8; i++)
								{
									(*short_out)[short_counter] = (*long_out_64)[i];
									short_counter ++;
								}
								to_char_convert = short_out->to_ullong ();
								cronchPUT[0] = (char)to_char_convert;
								cronchOUT.write (cronchPUT, 1);

							}
							else
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
		}
		cronchOUT.close ();
		cronchIN.close ();
	}
	else
	{
	}

	return 0;
}
