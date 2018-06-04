#include "strToWords.h"

void strToWords(std::string src, std::string *words, int &size)
{
	std::string delimiters = "|";
	std::string tmp = src + " ";
	size = 0;

	size_t pos = tmp.find(delimiters);
	while (pos = tmp.find(delimiters) != std::string::npos)
	{
		pos = tmp.find(delimiters);
		words[size++] = tmp.substr(0, pos);
		tmp.erase(0, pos + 1);
	}
}