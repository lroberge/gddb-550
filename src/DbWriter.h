#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "DbUtils.h"

static class DbWriter
{
public:
    static DatabaseHandle *create_db(std::string name);

private:
    static void create_magic(std::ofstream *);
    static void create_crc(std::ofstream *);
    static void create_name(std::ofstream *);
    // static std::vector<ColumnType> get_columns(std::ifstream *);
    // static int get_numpages(std::ifstream *);
};