#include "nclass.h"

static void	genGetAndSet(std::ofstream& file, const std::string& className, const Members& members)
{
	if (g_options.getters)
	{
		file << "//\t=== Getters ===" << end;
		for (const std::string& str : members)
		{
			std::string type = str.substr(0, str.find_last_of(' '));
			std::string var = lastWord(str);
			bool isBasic = isBasicType(str);

			if (!isBasic) file << "const ";
			file << type;
			if (!isBasic) file << "&";
			file << '\t' << className << "::" << g_options.getterPrefix;
			if (g_options.uppercaseMember) file << firstUpper(var); else file << var;
			file << "(void) const" << end;
			file << '{' << end;
			file << "\treturn " << g_options.memberPrefix << var << g_options.memberSuffix << ';' << end;
			file << '}' << end << end;
		}
	}
	if (g_options.setters)
	{
		file << "//\t=== Setters ===" << end;
		for (const std::string& str : members)
		{
			std::string type = str.substr(0, str.find_last_of(' '));
			std::string var = lastWord(str);
			bool isBasic = isBasicType(str);

			file << "void" << '\t' << className << "::" << g_options.setterPrefix;
			if (g_options.uppercaseMember) file << firstUpper(var); else file << var;
			file << '(';
			if (!isBasic) file << "const ";
			file << type;
			if (!isBasic) file << "&";
			file << ' ' << lowerCase(var) << ")" << end;
			file << '{' << end;
			file << '\t'<< g_options.memberPrefix << var << g_options.memberSuffix << " = " << lowerCase(var) << ';' << end;
			file << '}' << end << end;
		}
	}

}

static void	defConstructor(std::ofstream& file, const std::string& className)
{
	file << className << "::" << className << "()"; //	Default

	if (!g_options.constructor_msg)
		file << " {}" << end;
	else
	{
		file
			<< end
			<< '{' << end
			<< "\tstd::cout" << end
			<< "\t\t<< \"::" << className << " default constructor called.\"" << end
			<< "\t\t<< std::endl;" << end
			<< '}' << end;
	}
}

static void	copyConstructor(std::ofstream& file, const std::string& className)
{
	file << className << "::" << className << "(const " << className << "& rhs)" << end; // Copy

	file << '{' << end;

	if (g_options.constructor_msg)
	{
		file
			<< "\tstd::cout" << end
			<< "\t\t<< \"::" << className << " copy constructor called.\"" << end
			<< "\t\t<< std::endl;" << end << end;
	}

	file << "\t*this = rhs;" << end;
	file << '}' << end;
}

static void	copyAssignment(std::ofstream& file, const std::string& className, const Members& members)
{
	file <<  className << "&\t" << className << "::operator=(const " << className << "& rhs)" << end; // copy assignment

	file << '{' << end;

	if (g_options.constructor_msg)
	{
		file
			<< "\tstd::cout" << end
			<< "\t\t<< \"::" << className << " copy-assignment operator called.\"" << end
			<< "\t\t<< std::endl;" << end << end;
	}

	for (const std::string& str : members)
	{
		const std::string var = g_options.memberPrefix + lastWord(str) + g_options.memberSuffix;
		file << '\t' << var << " = " << "rhs." << var << ';' << end;
	}
	file << "\treturn *this;" << end;
	file << '}' << end;
}

static void	destructor(std::ofstream& file, const std::string& className)
{
	file << className << "::~" << className << "()"; //	Destructor

	if (!g_options.constructor_msg)
		file << " {}" << end;
	else
	{
		file
			<< end
			<< '{' << end
			<< "\tstd::cout" << end
			<< "\t\t<< \"::" << className << " destructor called.\"" << end
			<< "\t\t<< std::endl;" << end
			<< '}' << end;
	}
}

void	genSource(std::ofstream& file, const std::string& className, const Members& members)
{
	//	includes
	if (g_options.header)
		file << "#include \"" << className << ".h\"" << end << end;
	if (g_options.constructor_msg)
		file << "#include <iostream>" << end << end;

	//	(de)Constructors
	file << "//\t=== (de)constructors ===" << end;
	defConstructor(file, className);
	file << end;
	copyConstructor(file, className);
	file << end;
	copyAssignment(file, className, members);
	file << end;
	destructor(file, className);
	file << end;

	//	Getters & Setters
	if (!members.empty())
		genGetAndSet(file, className, members);
	//	Flush
	file << std::endl;
}
