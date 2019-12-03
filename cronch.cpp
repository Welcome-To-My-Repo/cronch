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
	cronchOUT.open ("file.cronch", std::ios::out | std::ios::binary);
	cronchIN.open ("test/test.txt", std::ios::in | std::ios::binary);
	char bit64 [4];
	while (!cronchIN.eof ())
	{
		cronchIN.read (bit64, 4);
		cronchOUT.write (bit64, 4);
	}

}

int decompress ()
{
}
