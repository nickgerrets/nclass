#ifndef HELPERS_H
# define HELPERS_H

#include <string>
#include <fstream>

bool		fileExists(const std::string& fname);
std::string	upperCase(const std::string& str);
std::string	lowerCase(const std::string& str);
std::string	firstUpper(const std::string& str);
std::string	lastWord(const std::string& str);
std::string	getNextWord(const std::string& str, size_t& pstart);

#endif // HELPERS_H
