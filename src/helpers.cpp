#include "nclass.h"

bool	fileExists(const std::string& fname)
{
	std::ifstream	file (fname);
	return file.good();
}

//	Copies and returns uppercase version of string
std::string	upperCase(const std::string& str)
{
	std::string	ret (str);

	for (char& c : ret)
		c = (char)toupper(c);
	return (ret);
}

//	Copies and returns lowercase version of string
std::string	lowerCase(const std::string& str)
{
	std::string	ret (str);

	for (char& c : ret)
		c = (char)tolower(c);
	return (ret);
}

//	Copies and returns version of string with first letter in uppercase
std::string	firstUpper(const std::string& str)
{
	std::string	ret (str);

	char& c = ret.at(0);
	c = (char)toupper(c);
	return (ret);
}

std::string	lastWord(const std::string& str)
{
	size_t	pos = str.rfind(' ');
	if (pos != std::string::npos)
		return (str.substr(pos + 1, str.length()));
	return ("");
}
