#pragma once

#include <set>

#include <jsoncons/json.hpp>
#include <jsoncons_ext/bson/bson.hpp>

#include <MurmurHash3.h>

#include "DbWriter.h"
#include "DbReader.h"
#include "DbPages.h"

class DbOperations
{
public:
	static int create_column(DbHandle* dbhandle, ColumnType coltype, std::string name);
	static int create_entry(DbHandle* dbhandle, jsoncons::json* entry);
	static bool create_tag(DbHandle* dbhandle, std::string name, SimpleColor color);

	static std::set<uint32_t> lookup_by_string(DbHandle* dbhandle, uint8_t column, std::string lookup);
	static std::set<uint32_t> intersection(std::set<uint32_t> set1, std::set<uint32_t> set2);
private:
	
};

