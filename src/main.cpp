/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 10:42:39 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/09/02 13:35:21 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "nclass.h"
#include "Json.h"

Options g_options;

njson::Json*	asType(njson::Json& node, njson::Json::Type type)
{
	if ( node.getType() == type )
		return &node;
	return nullptr;
}

void	setOptionsFromJson(const char* fname)
{
	using namespace njson;

	Json* json = parse(fname);
	if (!json)
		return ;

	//	STYLING
	Json& style = json->find("style");
	if (style.getType() != Json::Type::OBJECT) { delete json; return ; }

	if ( Json* node = asType(style.find("member_prefix"), Json::Type::STRING) )
		g_options.memberPrefix = node->getString();
	
	if ( Json* node = asType(style.find("member_suffix"), Json::Type::STRING) )
		g_options.memberSuffix = node->getString();

	if ( Json* node = asType(style.find("getter_prefix"), Json::Type::STRING) )
		g_options.getterPrefix = node->getString();

	if ( Json* node = asType(style.find("setter_prefix"), Json::Type::STRING) )
		g_options.setterPrefix = node->getString();
	
	if ( Json* node = asType(style.find("member_uppercase"), Json::Type::BOOL) )
		g_options.uppercaseMember = node->getBool();
	
	//	PATH
	if ( Json* node = asType(style.find("header_path"), Json::Type::STRING) )
		g_options.headerPath = node->getString();

	if ( Json* node = asType(style.find("header_suffix"), Json::Type::STRING) )
		g_options.headerSuffix = node->getString();

	if ( Json* node = asType(style.find("source_path"), Json::Type::STRING) )
		g_options.srcPath = node->getString();

	if ( Json* node = asType(style.find("source_suffix"), Json::Type::STRING) )
		g_options.srcSuffix = node->getString();

}

static std::string	querryUser(const char* question)
{
	if (question)
		std::cout << question << std::endl;
	if (std::cin.eof())
		return ("");
	std::string	response = "";
	getline(std::cin, response);
	return (response);
}

static std::ofstream	createFile(const std::string& path, const std::string& name)
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

static void	generateFiles(const std::string& className, const Members& members)
{
	if (g_options.header)
	{
		std::ofstream hfile = createFile(g_options.headerPath, className + g_options.headerSuffix);
		std::cout << "Generating .h file..." << std::endl;
		genHeader(hfile, className, members);
	}
	if (g_options.source)
	{
		std::ofstream sfile = createFile(g_options.srcPath, className + g_options.srcSuffix);
		std::cout << "Generating .cpp file..." << std::endl;
		genSource(sfile, className, members);
	}
	std::cout << "Done!" << std::endl;
}

int	interfaced(void)
{
	std::string	className = "";

	className = querryUser("Please enter class/header name:");

	std::string memvar = "";
	Members members {};
	if (g_options.members)
	{
		std::cout << "Enter member variables (<type(s)> <name>), blank line to stop:" << std::endl;
		while ((memvar = querryUser(NULL)).size() > 0)
			members.emplace_back(memvar);
	}

	generateFiles(className, members);
	return (0);
}

int	direct(void)
{
	generateFiles(g_options.className, {});
	return (0);
}

void	setGlobalsFromArgs(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string	str (argv[i]);
		if (str == "-o")
			g_options.overwrite = true;
		else if (str == "--no-header")
			g_options.header = false;
		else if (str == "--no-source")
			g_options.source = false;
		else if (str == "--no-members")
			g_options.members = false;
		else if (str == "--no-getters")
			g_options.getters = false;
		else if (str == "--no-setter")
			g_options.setters = false;
		else if (str == "--no-impl")
			g_options.implement = false;
		else if (str == "--no-msg")
			g_options.constructor_msg = false;
		else if (str == "--no-class" || str == "-n")
		{
			g_options.pclass = false;
			g_options.source = false;
		}
		else if (str[0] != '-')
		{
			g_options.className = str;
		}
	}
}

int	main(int argc, char** argv)
{
	setGlobalsFromArgs(argc, argv);
	setOptionsFromJson("options.json");
	if (!g_options.header && !g_options.source)
		return (0);
	if (g_options.className.empty())
		return interfaced();
	else
		return direct();
	return (0);
}
