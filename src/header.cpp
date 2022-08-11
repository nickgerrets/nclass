#include "nclass.h"

static void	genGetAndSet(std::ofstream& file, const Members& members)
{
	if (members.empty())
		return ;
	//	GETTERS
	if (g_options.getters)
	{
		file << "\t\t//\t=== Getters ===" << end;
		for (const std::string& str : members)
		{
			std::string type = str.substr(0, str.find_last_of(' '));
			std::string var = lastWord(str);
			file << "\t\t" << type << '\t' << "get" << firstUpper(var) << "(void) const;" << end;
		}
	}

	//	SETTERS
	if (g_options.setters)
	{
		file << end << "\t\t//\t=== Setters ===" << end;
		for (const std::string& str : members)
		{
			std::string type = str.substr(0, str.find_last_of(' '));
			std::string var = lastWord(str);
			file << "\t\tvoid" << '\t' << "set" << firstUpper(var) << '(' << type << ' ' << lowerCase(var) << ");" << end;
		}
	}
}

static void	genMemberVars(std::ofstream& file, const Members& members)
{
	if (members.empty())
		return ;
	file << "\tprivate:" << end;
	file << "\t\t//\t=== Member variables ===" << end;
	for (const std::string& str : members)
	{
		std::string type = str.substr(0, str.find_last_of(' '));
		std::string var = g_options.memberPrefix + lastWord(str);

		file << "\t\t" << type << '\t' << var << ';' << end;
	}
}

static void	genClass(std::ofstream& file, const std::string& className, const Members& members)
{
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
	{
		file << end;
		genMemberVars(file, members);
	}

	//	End class
	file << "};" << end;
}

void	genHeader(std::ofstream& file, const std::string& className, const Members& members)
{
	//	Starting header guard
	file << "#ifndef " << upperCase(className) << "_H" << end;
	file << "# define " << upperCase(className) << "_H\n" << end;

	//	Class
	if (g_options.pclass)
	{
		genClass(file, className, members);
	}

	//	Ending header guard & Flush
	file << "\n#endif " << "// " << upperCase(className) << "_H" << std::endl;
}
