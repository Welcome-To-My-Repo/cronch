#include "cronch.h"

int main (int argc, char **argv)
{
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
	if (argv[1][0] != 'c' and argv[1][0] != 'd')
	{
		std::cout << "Incorrect mode!" << std::endl;
		return 3;
	}
	return 0;
}

int compress ()
{
	std::ifstream cronchIN;
	std::ofstream cronchOUT;
	char _32bit [4];
	int8_t _8bit;
	int64_t collate_to_decimal = 0;
	long long int filesize;
	std::string combine = "";
	std::bitset <32> *binarycollate;
	std::bitset <8> blocks[4];
	unsigned long long int to_decimal;
	std::vector <std::string> PrimeDivisors;
	std::string FinalString;
	cronchOUT.open ("file.cronch", std::ios::out | std::ios::binary);
	cronchIN.open ("test/test.txt", std::ios::in | std::ios::binary | std::ios::ate);
	if (!cronchIN.is_open ())
		return 1;
	filesize = cronchIN.tellg ();
	cronchIN.seekg (std::ios_base::beg);
	if (!cronchIN.is_open ())
		return 0;

	std::cout << "filesize " << filesize << std::endl;
	if (filesize%4 == 0)
		filesize = filesize/4;
	else
		filesize = filesize%4 + filesize/4;
	std::cout << "filesize " << filesize << std::endl;
	for (long long int a = 0; a < filesize; a ++)
	{
		if (cronchIN.eof())
			break;
		cronchIN.read (_32bit, 4);
		_8bit = _32bit[0];
		blocks[0] = std::bitset <8> (_8bit);
		_8bit = _32bit[1];
		blocks[1] = std::bitset <8> (_8bit);
		_8bit = _32bit[2];
		blocks[2] = std::bitset <8> (_8bit);
		_8bit = _32bit[3];
		blocks[3] = std::bitset <8> (_8bit);

		combine.append (blocks[0].to_string ());
		std::cout << combine << " ";
		combine.append (blocks[1].to_string ());
		std::cout << combine << " ";
		combine.append (blocks[2].to_string ());
		std::cout << combine << " ";
		combine.append (blocks[3].to_string ());
		std::cout << combine << " " << std::endl;
		binarycollate = new std::bitset<32> (combine.c_str ());
		to_decimal = binarycollate->to_ullong ();
		std::cout << to_decimal << std::endl;
		delete binarycollate;

		if (to_decimal == 0)
		{
			PrimeDivisors.push_back (std::to_string (to_decimal));
		}
		else
		find_primes (PrimeDivisors, to_decimal);

		std::bitset <32> *extra_prime;
		std::string separate_prime;
		char eightbit[1];
		uint32_t convert;
		std::bitset <4> factors[2];
		std::bitset <8> *writeout;
		int consecutive = 1;
		std::string current, comparison;
		current = PrimeDivisors.front ();
		for (int i = 1; i < PrimeDivisors.capacity (); i ++)
		{
			comparison = PrimeDivisors.at (i);
			if (current == comparison)
			{
				consecutive ++;
			}
			else
			{
				if (std::stoull (current) > 15)
				{
					writeout = new std::bitset <8> (0);
					eightbit[0] = writeout->to_ullong ();
					cronchOUT.write (eightbit, 1);
					cronchOUT.put (std::stoull (current));
					extra_prime = new std::bitset <32> (std::stoull (current));
					std::cout << writeout->to_string () << " " << extra_prime->to_string () << " ";
				}
				else
				{
					factors[0] = std::bitset <4> (consecutive);
					factors[1] = std::bitset <4> (std::stoi (current));
					writeout = new std::bitset <8> ();
					for (int i = 4; i < 8; i ++)
					{
						writeout->set (i, factors[0].test(i-4));
					}
					for (int i = 0; i < 3; i++)
					{
						writeout->set (i, factors[1].test(i));
					}
					eightbit[0] = writeout->to_ullong ();
					cronchOUT.write (eightbit, 1);
					std::cout << writeout->to_string () << " ";
				}
				current = comparison;
				consecutive = 1;
			}
			if (std::stoull (current) > 15)
			{
				writeout = new std::bitset <8> (0);
				eightbit[0] = writeout->to_ullong ();
				cronchOUT.write (eightbit, 1);
				//cronchOUT.put (std::stoull (current));
				extra_prime = new std::bitset <32> (std::stoull (current));
				convert = extra_prime->to_ullong ();
				std::cout << writeout->to_string () << " " << extra_prime->to_string () << " ";
			}
			else
			{
				factors[0] = std::bitset <4> (consecutive);
				factors[1] = std::bitset <4> (std::stoi (current));
				writeout = new std::bitset <8> ();
				for (int i = 4; i < 8; i ++)
				{
					writeout->set (i, factors[0].test(i-4));
				}
				for (int i = 0; i < 3; i++)
				{
					writeout->set (i, factors[1].test(i));
				}
				eightbit[0] = writeout->to_ullong ();
				cronchOUT.write (eightbit, 1);
				std::cout << writeout->to_string () << " ";
			}
		}
		std::cout << std::endl;
	}
	return 0;

}

int decompress ()
{
	return 0;
}

int find_primes (std::vector <std::string> &PrimeDivisors, unsigned long long int to_decimal)
{
	bool not_prime = true;
	while (not_prime)
	{
		not_prime = false;
		for (int i = 15; i > 1; i--)
		{
			if (to_decimal%i == 0)
			{
				PrimeDivisors.push_back (std::to_string (i));
				to_decimal = to_decimal/i;
				not_prime = true;
			}
		}
	}
	PrimeDivisors.push_back (std::to_string (to_decimal));
	return 0;
}
