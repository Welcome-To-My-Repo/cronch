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
	std::string combine = "";
	std::bitset <32> *binarycollate;
	std::bitset <8> blocks[4];
	unsigned long long int to_decimal;
	cronchOUT.open ("file.cronch", std::ios::out | std::ios::binary);
	cronchIN.open ("test/test.txt", std::ios::in | std::ios::binary);
	if (!cronchIN.is_open ())
		return 0;
	while (!cronchIN.eof ())
	{
		cronchIN.read (_32bit, 4);
		_8bit = _32bit[0];
		blocks[0] = std::bitset <8> (_8bit);
		_8bit = _32bit[1];
		blocks[1] = std::bitset <8> (_8bit);
		
		blocks[2] = std::bitset <8> (_8bit);
		blocks[3] = std::bitset <8> (_8bit);
		combine.append (blocks[0].to_string ());
		std::cout << combine << " ";
		combine.append (blocks[1].to_string ());
		std::cout << combine << " ";
		combine.append (blocks[2].to_string ());
		std::cout << combine << " ";
		combine.append (blocks[3].to_string ());
		std::cout << combine << " ";
		std::endl;
		binarycollate = new std::bitset<32>::bitset (combine);
		to_decimal = binarycollate->to_ullong ();
		std::cout << to_decimal << std::endl;
	}
	return 0;

}

int decompress ()
{
}
