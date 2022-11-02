#pragma once

#include <string>
#include <vector>

static const uint16_t DB_VERSION = 2;
static const uint16_t PAGE_LENGTH = 8192;
static const uint16_t MAX_COLUMN_NAME_LENGTH = 75;
static const uint16_t MAX_TAG_NAME_LENGTH = 29;

enum ColumnType
{
    numi,
    numf,
    phrase,
    sentence,
    tags
};

enum PageType
{
    empty,
    dbstructure,
    taglist,
    tree,
    entry
};

enum DbFormat
{
    paged,
    packed
};

struct Column {
    uint8_t type;
    char name[MAX_COLUMN_NAME_LENGTH];
    uint16_t idxpage;
    uint16_t idxindex;
};

struct SimpleColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Tag {
    char name[MAX_TAG_NAME_LENGTH];
    SimpleColor tagcolor;
};

struct DbHandle
{
    std::string path;
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