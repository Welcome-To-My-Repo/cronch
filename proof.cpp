#include <iostream>
#include <vector>

int main ()
{
	std::string a;
	std::vector<int> data (4);

	std::cout << "Enter a string of characters \"a\", \"b\", \"c\", and \"d\"." << std::endl;
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
			case 'c':
			{
				data.at(2) ++;
				break;
			}
			case 'd':
			{
				data.at(3) ++;
				break;
			}
		}
	for (int i = 0; i < data.size (); i ++)
		std::cout << data.at(i) << " ";
	std::cout << std::endl;
}
