#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <bitset>

std::fstream cronchFile;

int compress ();
int decompress ();

static const int
	P_1 = 1,
	P_2 = 2,
	P_3 = 3,
	P_4 = 5,
	P_5 = 7,
	P_6 = 11,
	P_7 = 13,
	P_8 = 17,
	P_9 = 19,
	P_10 = 23,
	P_11 = 29,
	P_12 = 31,
	P_13 = 37,
	P_14 = 41,
	P_15 = 43;

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
