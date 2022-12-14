#pragma once

#include <string>
#include <vector>

static const uint16_t DB_VERSION = 2;
static const uint16_t PAGE_LENGTH = 8192;
static const uint16_t MAX_COLUMN_NAME_LENGTH = 75;
static const uint16_t MAX_TAG_NAME_LENGTH = 29;
// may change - ints can have a table and tree index, necessitating up to 2
static const uint8_t MAX_INDEXES = 2;

enum DbFormat
{
    paged,
    packed
};

enum ColumnType
{
    numi,
    numf,
    string,
    tags
};

//enum IndexType
//{
//    table,
//    tree
//};

enum PageType
{
    empty,
    dbstructure,
    taglist,
    tablepage,
    treepage,
    entry
};

//struct Index {
//    IndexType type;
//    uint16_t idxpage;
//    uint16_t idxindex;
//};

struct Column {
    ColumnType type;
    char name[MAX_COLUMN_NAME_LENGTH];
    bool indexed = false;
    /*uint8_t numindexes;
    Index indexes[MAX_INDEXES];*/
};

struct SimpleColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Tag {
    char name[MAX_TAG_NAME_LENGTH] = {};
    SimpleColor tagcolor;
};

struct DbHandle
{
    std::string path;
    std::string basepath;
    std::string entriespath;
    jsoncons::ojson entries;
    uint8_t format = 0;
    uint8_t columncount = 0;
    std::vector<Column> columns;
    uint8_t tagcount = 0;
    std::vector<Tag> tags;
    bool error = false;
};

struct DbHeader
{
    char magic[4];
    uint16_t version;
    uint8_t format;
    bool dirty;
    uint32_t crc32; //unused right this second
    uint16_t pagecount;
};

class DbEntry
{
private:
    // the list of columns and their types is in here
    // so we can map a column index to its type
    std::shared_ptr<DbHandle> parentDb;

    char data; // unformatted memory of the entry
    int offsets; // list of byte offsets where columns start
                 // defined by db's columns (if possible) and entry's contents

public:
    DbEntry(char data[]); // construct the offsets list
    void* get_entry(int column); // probably have an outside function to handle casting
};