#ifndef TYPES_H
# define TYPES_H

# include <string>

enum class Type
{
	SHORT,
	USHORT,
	INT,
	INT8,
	INT16,
	INT32,
	INT64,
	UINT,
	UINT8,
	UINT16,
	UINT32,
	UINT64,
	LONG,
	ULONG,
	FLOAT,
	DOUBLE,
	CHAR,
	UCHAR,
	BOOL,
	UNKNOWN
};

bool	isBasicType(const std::string& str);

#endif
