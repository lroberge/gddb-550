#pragma once

#include <string>

enum ColumnType
{
    numi,
    numf,
    phrase,
    sentence,
    tags
};

static class DbReader
{
public:
    static DatabaseHandle open_file(std::string);
};

struct DatabaseHandle
{
    std::string name;
    ColumnType *columns;
};