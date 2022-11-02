#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "DbUtility.h"
#include "DbPages.h"

class DbWriter
{
public:
	static DbHandle create_db(std::string path);

public: //private, but public for testing
	template <class typedPage> static bool write_page(DbHandle* dbhandle, typedPage* page, uint16_t index);
};

