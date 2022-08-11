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

			if (!isBasic)
				file << "const ";
			file << type;
			if (!isBasic)
				file << "&";
			file << '\t' << className << "::get" << firstUpper(var) << "(void) const" << end;
			file << '{' << end;
			file << "\treturn " << g_options.memberPrefix << var << ';' << end;
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

			file << "void" << '\t' << className << "::set" << firstUpper(var) << '(';
			if (!isBasic)
				file << "const ";
			file << type;
			if (!isBasic)
				file << "&";
			file << ' ' << lowerCase(var) << ")" << end;
			file << '{' << end;
			file << '\t'<< g_options.memberPrefix << var << " = " << lowerCase(var) << ';' << end;
			file << '}' << end << end;
		}
	}

}

static void	defConstructor(std::ofstream& file, const std::string& className)
{
	file << className << "::" << className << "() {}" << end; //	Default
}

static void	copyConstructor(std::ofstream& file, const std::string& className)
{
	file << className << "::" << className << "(const " << className << "& rhs)" << end; // Copy

	file << '{' << end;
	file << "\t*this = rhs;" << end;
	file << '}' << end;
}

static void	copyAssignment(std::ofstream& file, const std::string& className, const Members& members)
{
	file <<  className << "&\t" << className << "::operator=(const " << className << "& rhs)" << end; // copy assignment

	file << '{' << end;
	for (const std::string& str : members)
	{
		const std::string var = g_options.memberPrefix + lastWord(str);
		file << '\t' << var << " = " << "rhs." << var << ';' << end;
	}
	file << "\treturn *this;" << end;
	file << '}' << end;
}

static void	destructor(std::ofstream& file, const std::string& className)
{
	file << className << "::~" << className << "() {}" << end; //	Destructor
}

void	genSource(std::ofstream& file, const std::string& className, const Members& members)
{
	//	includes
	if (g_options.header)
		file << "#include \"" << className << ".h\"" << end << end;

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
