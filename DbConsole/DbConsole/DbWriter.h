#pragma once

#include <iostream>
#include <string>
#include <fstream>

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
	static bool write_entries(DbHandle* dbhandle, jsoncons::ojson* entries);
};

