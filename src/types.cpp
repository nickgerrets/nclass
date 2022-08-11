#include "types.h"
#include <string>
#include <array>
#include "helpers.h"

bool	isBasicType(const std::string& str)
{
	static const std::string keywords[] = 
	{
		//	the fundamental datatypes
		"*",
		"void",
		"bool",
		"char",
		"int",
		"float",
		"double",
		//	size specifiers
		"short",
		"long",
		//	sign
		"signed",
		"unsigned",
		//	type definitions
		"size_t",
		"wchar_t"
	};

	std::string word = "";
	size_t	pstart = 0;
	while ((word = getNextWord(str, pstart)) != "")
	{
		for (size_t i = 0; i < (sizeof(keywords) / sizeof(*keywords)); ++i)
		{
			if (word == keywords[i])
				return (true);
			if (word.front() == '*' || word.back() == '*')
				return (true);
		}
	}
	return (false);
}

// Type	getType(const std::string& word)
// {
// 	static const std::unordered_map<std::string, Type> map
// 	{
// 		{"short", Type::SHORT},
// 		{"unsigned short", Type::USHORT},
// 		{"int", Type::INT},
// 		{"int8_t", Type::INT8},
// 		{"int16_t", Type::INT16},
// 		{"int32_t", Type::INT32},
// 		{"int64_t", Type::INT64},
// 		{"unsigned int", Type::UINT},
// 		{"uint8_t", Type::UINT8},
// 		{"uint16_t", Type::UINT16},
// 		{"uint32_t", Type::UINT32},
// 		{"uint64_t", Type::UINT64},
// 		{"long", Type::LONG},
// 		{"unsigned long", Type::ULONG},
// 		{"float", Type::FLOAT},
// 		{"double", Type::DOUBLE},
// 		{"char", Type::CHAR},
// 		{"unsigned char", Type::UCHAR},
// 		{"bool", Type::BOOL}
// 	};

// 	return (Type::UNKNOWN);
// }
