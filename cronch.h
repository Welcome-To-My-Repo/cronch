#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <bitset>
#include <sstream>

std::fstream cronchFile;

int compress ();
int decompress ();
int find_primes (std::vector <std::string> &PrimeDivisors, unsigned long long int to_decimal);

static const int PRIMES[4] = {2, 3, 5, 7};

struct EightBit
{
	bool
		_128,
		_64,
		_32,
		_16,
		_8,
		_4,
		_2,
		_1;
};
static long long int _4byte = 4294967295;
