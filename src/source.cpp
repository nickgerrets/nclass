#include "nclass.h"

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

	//	Getters & Setters

	//	Flush
	file << std::endl;
}
