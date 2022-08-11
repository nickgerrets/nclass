#ifndef NCLASS_H
# define NCLASS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

constexpr const char end[] = "\n";

using Members = std::vector<std::string>;

//	Global Options for the program
struct Options
{
	//	Default behaviours
	bool		header = true;
	bool		pclass = true;
	bool		source = true;
	bool		overwrite = false;
	bool		getters = true;
	bool		setters = true;
	bool		members = true;
	bool		implement = true;
	std::string	headerPath = "./include/";
	std::string	srcPath = "./src/";
	std::string	headerSuffix = ".h";
	std::string	srcSuffix = ".cpp";
	std::string	memberPrefix = "m_";
	std::string	className;
};

extern Options g_options;

//	Helpers
bool		fileExists(const std::string& fname);
std::string	upperCase(const std::string& str);
std::string	lowerCase(const std::string& str);
std::string	firstUpper(const std::string& str);
std::string	lastWord(const std::string& str);

void		genHeader(std::ofstream& file, const std::string& className, const Members& members);
void		genSource(std::ofstream& file, const std::string& className, const Members& members);

#endif