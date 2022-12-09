#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <jsoncons/json.hpp>
#include <jsoncons_ext/bson/bson.hpp>

#include "DbUtility.h"
#include "DbPages.h"


class DbReader
{
public:
	static std::unique_ptr<DbHandle> open_db(std::string path);

public: //private, but public for testing
	static std::shared_ptr<DbPage> load_page(DbHandle* dbhandle, uint16_t index);
	//static int find_next_page(DbHandle* dbhandle, PageType type, int from = 1);
	static std::shared_ptr<StructureData> load_structure_page(DbHandle* dbhandle);
	static bool load_entries(DbHandle* dbhandle);
	static jsoncons::ojson load_index(DbHandle* dbhandle, uint8_t column);
};

