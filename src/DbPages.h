#pragma once

#include <cstdint>

#include "DbUtility.h"

const uint16_t MAX_COLUMN_COUNT = 85;
const uint16_t MAX_TAG_COUNT = 255;

struct StructureData {
	uint8_t columncount = 0;
	Column columns[MAX_COLUMN_COUNT] = {};
};

struct TagListData {
	uint8_t totaltagnum = 0;
	Tag tags[MAX_TAG_COUNT] = {};
};

struct TableIndexData {
	union {
		int intindex[2047];
		float floatindex[2047];
		char strindex[4][2047];
	};
};

struct TagIndexData {
	uint8_t tagindex = 0;
	uint32_t entryindexes[];
};

//struct EntryData {
//	uint16_t freebytes = 8186;
//	char data[];
//};

struct DbPage {
	uint16_t type = PageType::empty;
	union {
		StructureData structure;
		TagListData taglist;
		TableIndexData table;
		//TreeIndexData tree;
		//EntryData entries;
		char data[8188];
	};

	DbPage() {};
	DbPage(const DbPage& page) {};
};