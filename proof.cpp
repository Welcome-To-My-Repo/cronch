#include <iostream>
#include <vector>
#include <list>

int main ()
{
	std::string a;
	std::vector<int> data (2);

	std::cout << "Enter a string of characters \"a\" and \"b\" at most, 8 characters long." << std::endl;
	std::cin >> a;
	for (int i = 0; i < a.size (); i ++)
		switch (a.at(i))
		{
			case 'a':
			{
				data.at (0) ++;
				break;
			}
			case 'b':
			{
				data.at(1) ++;
				break;
			}
		}
	for (int i = 0; i < data.size (); i ++)
		std::cout << data.at(i) << " ";
	std::cout << std::endl;
	std::list <bool>l;
	bool io[8];
}
