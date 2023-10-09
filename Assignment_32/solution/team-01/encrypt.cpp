#include <iostream>
#include <cstring>

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		std::cout << "usage: encrypt <key>" << std::endl;
		return 1;
	}
	const char *key = argv[1];
	int i = 0;
	char c;
	while (std::cin.get(c))
	{
		std::cout << (char)(c ^ key[i % strlen(key)]);
		i++;
	}
	return 0;
}
