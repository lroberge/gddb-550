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

typedef struct DatabaseHandle
{
    std::string name;
    short columncount;
    ColumnType *columns;
    bool incomplete = true;
};
