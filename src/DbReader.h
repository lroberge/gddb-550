#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "DbUtils.h"

static class DbReader
{
public:
    static DatabaseHandle *open_file(std::string);

private:
    static bool check_magic(std::ifstream *);
    static bool check_crc(std::ifstream *);
    static std::string get_name(std::ifstream *);
    // static std::vector<ColumnType> get_columns(std::ifstream *);
    // static int get_numpages(std::ifstream *);
};