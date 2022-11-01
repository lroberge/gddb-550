#pragma once

#include "DbReader.h"
#include "sqlite3.h"

// #define DB_MAGIC

DatabaseHandle *DbReader::open_file(std::string path)
{
    std::streampos offset;

    std::ifstream dbfile(path, std::ios::binary);
    if (dbfile.is_open())
    {
        if (!check_magic(&dbfile))
        {
            return new DatabaseHandle;
        }
        if (!check_crc(&dbfile))
        {
            return new DatabaseHandle;
        }

        dbfile.close();
    }
}

bool DbReader::check_magic(std::ifstream *dbfile)
{
    char *memblock = new char[5];
    dbfile->read(memblock, 5);
    if (std::string{memblock} == "gddb")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool DbReader::check_crc(std::ifstream *dbfile)
{
    dbfile->ignore(16);
    return true;
}

std::string DbReader::get_name(std::ifstream *dbfile)
{
    unsigned short namelen = dbfile->get();
    char *memblock = new char[namelen];
    dbfile->read(memblock, namelen);
    return std::string{memblock};
}

// std::vector<ColumnType> DbReader::get_columns(std::ifstream *dbfile)
// {

// }

// int DbReader::get_numpages(std::ifstream *dbfile)
// {
// }
