#include "cronch.h"

int main (int argc, char **argv)
{
	std::cout << argv[1] << std::endl;
/*
	if (argc < 2)
		return 1;

	if (argc < 3)
		return 2;
*/
	if (argc < 2)
		return 1;
	if (strcmp (argv[1], "c") == 0)
		compress ();
	if (strcmp (argv[1], "d") == 0)
		decompress ();

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
	std::string PrimeDivisors;
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
		std::cout << "loop start" << std::endl;
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
			PrimeDivisors += std::to_string (to_decimal);
		}
		else
		find_primes (PrimeDivisors, to_decimal);
		std::cout << "Primes" << std::endl << PrimeDivisors << std::endl;

		int consecutive;
		std::string currentnumber, comparison;
		char getstuff[100];
		std::stringstream factors;
		factors.str (PrimeDivisors);
		factors.getline (getstuff, 100, ' ');
		factors.get ();
		currentnumber.assign (getstuff);
		while (!factors.eof ())
		{
			factors.getline (getstuff, 100, ' ');
			factors.get ();
			comparison.assign (getstuff);
			if (currentnumber == comparison)
			{
				consecutive ++;
			}
			else
			{
				FinalString += std::to_string (consecutive) + " " + currentnumber + " ";
				currentnumber = comparison;
				consecutive = 1;
			}
		}
		std::cout << FinalString << std::endl;

	}
	return 0;

}

int decompress ()
{
	return 0;
}

int find_primes (std::string &PrimeDivisors, unsigned long long int to_decimal)
{
	bool not_prime = true;
	while (not_prime)
	{
		not_prime = false;
		std::cout << "loop" << std::endl;
		for (int i = 15; i > 1; i--)
		{
			if (to_decimal%i == 0)
			{
				PrimeDivisors += std::to_string (i);
				PrimeDivisors += " ";
				to_decimal = to_decimal/i;
				not_prime = true;
			}
		}
	}
	PrimeDivisors += std::to_string (to_decimal);
	return 0;
}
