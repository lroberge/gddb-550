#pragma once

#include "DbWriter.h"
#include "DbReader.h"
#include "DbPages.h"

class DbOperations
{
public:
	static bool create_column(DbHandle* dbhandle, ColumnType coltype, std::string name);
	static bool create_tag(DbHandle* dbhandle, std::string name, SimpleColor color);
	static int entry_length(DbHandle* dbhandle);

private:
	
};

