#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "DbUtility.h"
#include "DbPages.h"


class DbReader
{
public:
	static std::unique_ptr<DbHandle> open_db(std::string path);

public: //private, but public for testing
	template <class typedPage> static std::unique_ptr<typedPage> load_page(DbHandle* dbhandle, uint16_t index);
	static std::unique_ptr<StructurePage> load_structure_page(DbHandle* dbhandle);
};

