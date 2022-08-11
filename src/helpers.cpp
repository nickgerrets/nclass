#include "helpers.h"

bool	fileExists(const std::string& fname)
{
	std::ifstream	file (fname);
	return file.good();
}

//	Copies and returns uppercase version of string
std::string	upperCase(const std::string& str)
{
	std::string	ret (str);

	if (str.empty())
		return ("");
	for (char& c : ret)
		c = (char)toupper(c);
	return (ret);
}

//	Copies and returns lowercase version of string
std::string	lowerCase(const std::string& str)
{
	std::string	ret (str);

	if (str.empty())
		return ("");
	for (char& c : ret)
		c = (char)tolower(c);
	return (ret);
}

//	Copies and returns version of string with first letter in uppercase
std::string	firstUpper(const std::string& str)
{
	std::string	ret (str);

	if (str.empty())
		return ("");
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

std::string	getNextWord(const std::string& str, size_t& pstart)
{
	pstart = str.find_first_not_of(' ', pstart);
	if (pstart == std::string::npos)
		return ("");

	size_t pend = str.find(' ', pstart);
	std::string ret = str.substr(pstart, pend - pstart);
	pstart = pend;
	return (ret);
}
