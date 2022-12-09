#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <MurmurHash3.h>

#include <jsoncons/json.hpp>
#include <jsoncons_ext/bson/bson.hpp>

#include "DbUtility.h"
#include "DbPages.h"

class DbWriter
{
public:
	static DbHandle create_db(std::string path);

public: //private, but public for testing
	static bool write_page(DbHandle* dbhandle, DbPage* page, uint16_t index);
	static bool create_string_index(DbHandle* dbhandle, uint8_t column);
	static bool move_string_index(DbHandle* dbhandle, uint8_t oldcol, uint8_t newcol);
	static bool delete_string_index(DbHandle* dbhandle, uint8_t column);
	static bool index_string_entry(DbHandle* dbhandle, uint8_t column, uint32_t entry);
	static bool deindex_string_entry(DbHandle* dbhandle, uint8_t column, uint32_t entry);
	static bool write_entries(DbHandle* dbhandle, jsoncons::ojson* entries);
};

