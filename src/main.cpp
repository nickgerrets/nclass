/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:42:39 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/08/10 13:04:44 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <vector>

struct Options
{
	//	Default behaviours
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
}	g_options;

using Members = std::vector<std::string>;

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

std::string	querryUser(const char* question)
{
	if (question)
		std::cout << question << std::endl;
	if (std::cin.eof())
		return ("");
	std::string	response = "";
	getline(std::cin, response);
	return (response);
}

std::ofstream	createFile(const std::string& path, const std::string& name)
{
	if (!g_options.overwrite && fileExists(path + name))
	{
		std::cerr << "File already exists, run with '-o' flag to overwrite file." << std::endl;
		std::exit(-1);
	}
	
	std::ofstream	file (path + name);
	if (file.bad())
		perror("nclass: ");
	return (file);
}

void	genGetAndSet(std::ofstream& file, const Members& members)
{
	constexpr const char end[] = "\n";

	if (members.empty())
		return ;
	//	GETTERS
	if (g_options.getters)
	{
		file << "\t\t//\t=== Getters ===" << end;
		for (const std::string& str : members)
		{
			std::string type = str.substr(0, str.find(' '));

			size_t	pos = str.find(' ');
			std::string var;
			if (pos != std::string::npos)
				var = str.substr(str.find(' ') + 1, str.length());
			else
				var = "UNNAMED";

			file << "\t\t" << type << '\t' << "get" << firstUpper(var) << "(void) const;" << end;
		}
	}

	//	SETTERS
	if (g_options.setters)
	{
		file << end << "\t\t//\t=== Setters ===" << end;
		for (const std::string& str : members)
		{
			std::string type = str.substr(0, str.find(' '));

			size_t	pos = str.find(' ');
			std::string var;
			if (pos != std::string::npos)
				var = str.substr(str.find(' ') + 1, str.length());
			else
				var = "UNNAMED";

			file << "\t\tvoid" << '\t' << "set" << firstUpper(var) << '(' << type << ' ' << lowerCase(var) << ");" << end;
		}
	}
}

void	genMemberVars(std::ofstream& file, const Members& members)
{
	constexpr const char end[] = "\n";
	constexpr const char prefix[] = "m_";

	if (members.empty())
		return ;
	file << "\tprivate:" << end;
	file << "\t\t//\t=== Member variables ===" << end;
	for (const std::string& str : members)
	{
		std::string type = str.substr(0, str.find(' '));

		size_t	pos = str.find(' ');
		std::string var;
		if (pos != std::string::npos)
			var = str.substr(str.find(' ') + 1, str.length());
		else
			var = "UNNAMED";

		file << "\t\t" << type << '\t' << prefix << var << ';' << end;
	}
}

void	genClass(std::ofstream& file, const std::string& className, const Members& members)
{
	constexpr const char end[] = "\n";

	//	Starting header guard
	file << "#ifndef " << upperCase(className) << "_H" << end;
	file << "# define " << upperCase(className) << "_H\n" << end;

	//	Start class
	file << "class " << className << end;
	file << '{' << end;
	file << "\tpublic:" << end;

	//	(de)Constructors
	file << "\t\t//\t=== (de)constructors ===" << end;
	file << "\t\t" << className << "();" << end; //	Default
	file << "\t\t" << className << "(const " << className << "& rhs);" << end; // Copy
	file << "\t\t" << className << "& operator=(const " << className << "& rhs);" << end; // copy assignment
	file << "\t\t~" << className << "();" << end << end; //	Destructor

	genGetAndSet(file, members);
	if (g_options.members)
		genMemberVars(file, members);

	//	End class
	file << "};" << end;

	//	Ending header guard
	file << "\n#endif " << "// " << upperCase(className) << "_H" << std::endl;
}

int	interfaced(void)
{
	std::string	className = "";

	className = querryUser("Please enter class name:");
	std::ofstream file = createFile(g_options.headerPath, className + g_options.headerSuffix);

	std::string memvar = "";
	Members members {};

	if (g_options.members)
	{
		std::cout << "Enter member variables (<type> <name>), blank line to stop:" << std::endl;
		while ((memvar = querryUser(NULL)).size() > 0)
			members.emplace_back(memvar);
	}

	std::cout << "Generating class..." << std::endl;
	genClass(file, className, members);

	return (0);
}

int	direct(void)
{
	std::ofstream file = createFile(g_options.headerPath, g_options.className + g_options.headerSuffix);

	std::cout << "Generating class..." << std::endl;
	genClass(file, g_options.className, {});

	return (0);
}

void	setGlobalsFromArgs(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string	str (argv[i]);
		if (str == "-o")
			g_options.overwrite = true;
		else if (str == "--no-members")
			g_options.members = false;
		else if (str == "--no-getters")
			g_options.getters = false;
		else if (str == "--no-setter")
			g_options.setters = false;
		else if (str == "--no-impl")
			g_options.implement = false;
		else
		{
			g_options.className = str;
		}
	}
}

int	main(int argc, char** argv)
{
	setGlobalsFromArgs(argc, argv);
	if (g_options.className.empty())
		return interfaced();
	else
		return direct();
	return (0);
}
