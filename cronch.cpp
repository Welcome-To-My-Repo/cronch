#include "cronch.h"

int main (int argc, char **argv)
{
/*
	if (argc < 2)
		return 1;

	if (argc < 3)
		return 2;
*/
	if (argv[1][0] == "c")
		compress ();
	if (argv[1][0] == "d")
		decompress ();

	return;
}

int compress ()
{
}

int decompress ()
{
}
