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
	cronchOUT.open ("file.cronch", std::ios::out | std::ios::binary);
	cronchIN.open ("test/test.txt", std::ios::in | std::ios::binary);
	if (!cronchIN.is_open ())
		return 0;
	//while (!cronchIN.eof ())
	//{
		cronchIN.read (_32bit, 4);
		//cronchOUT.write (bit64, 4);
		_8bit = _32bit[0];
		for (int j = 7; _8bit > 0; j--)
		{
			binarycollate[j] = _8bit%2;
			_8bit = _8bit/2;
		}
		_8bit = _32bit[1];
		for (int j = 15; _8bit > 0; j--)
		{
			binarycollate[j] = _8bit%2;
			_8bit = _8bit/2;
		}
		_8bit = _32bit[2];
		for (int j = 23; _8bit > 0; j--)
		{
			binarycollate[j] = _8bit%2;
			_8bit = _8bit/2;
		}
		_8bit = _32bit[3];
		for (int j = 31; _8bit > 0; j--)
		{
			binarycollate[j] = _8bit%2;
			_8bit  = _8bit/2;
		}
		for (int i = 0; i < 32; i ++)
			std::cout << binarycollate[i] << " ";
		std::cout << std::endl;
		int64_t max = _4byte;
		for (int i = 0; i < 32; i++)
		{
			std::cout << "maximum: " << max << std::endl;
			if (binarycollate[i])
			{
				collate_to_decimal = collate_to_decimal + max;
			}
			max = max/2;
			std::cout << "collated total: " << collate_to_decimal << std::endl;
		}
	//}
	return 0;

}

int decompress ()
{
}
