#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <cmath>

int main ()
{
	std::string input;
	int table[4] = {0, 0, 0, 0};
	int network[12];
	int connections [32];

	std::cout << "Enter a series using \"A\", \"B\", \"C\", and \"D\"." << std::endl;
	std::cin >> input;
	for (int i = 0; i < input.size (); i ++)
	{
		if (input.at (i) != 'A' and 
		input.at (i) != 'B' and
		input.at (i) != 'C' and
		input.at (i) != 'D')
		{
			std::cout << "invalid input!" << std::endl;
			return 1;
		}
		else if (input.at (i) == 'B')
			table[1] ++;
		else if (input.at (i) == 'C')
			table[2] ++;
		else if (input.at (i) == 'D')
			table[3] ++;
		else	
			table[0] ++;
	}
	std::cout << "The table is as follows:\n"
		<< "A:\t" << table[0] << std::endl 
		<< "B:\t" << table[1] << std::endl
		<< "C:\t" << table[2] << std::endl
		<< "D:\t" << table[3] << std::endl
		<< std::endl;
	
}
