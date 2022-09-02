#ifndef NCLASS_H
# define NCLASS_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "helpers.h"
#include "types.h"

constexpr const char end[] = "\n";

using Members = std::vector<std::string>;

//	Global Options for the program
struct Options
{
	std::string	className;
	//	Default behaviours
	bool		header = true;
	bool		pclass = true;
	bool		source = true;
	bool		overwrite = false;
	bool		getters = true;
	bool		setters = true;
	bool		members = true;
	bool		implement = true;
	bool		constructor_msg = true;

	//	Paths
	std::string	headerPath = "./";
	std::string	srcPath = "./";
	std::string	headerSuffix = ".h";
	std::string	srcSuffix = ".cpp";

	//	Style
	std::string	memberPrefix = "m_";
	std::string	memberSuffix = "";
	std::string	getterPrefix = "get";
	std::string	setterPrefix = "set";
	bool		uppercaseMember = true;
};

extern Options g_options;

void		genHeader(std::ofstream& file, const std::string& className, const Members& members);
void		genSource(std::ofstream& file, const std::string& className, const Members& members);

#endif
