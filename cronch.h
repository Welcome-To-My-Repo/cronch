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

const int primes [15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

static long long int _4byte = 4294967295;
