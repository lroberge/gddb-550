#pragma once

#include <cstdint>

#include "DbUtility.h"

const uint16_t MAX_COLUMN_COUNT = 102;
const uint16_t MAX_TAG_COUNT = 255;

struct StructureData {
	uint8_t columncount = 0;
	Column columns[MAX_COLUMN_COUNT] = {};
};

struct TagListData {
	uint8_t totaltagnum = 0;
	Tag tags[MAX_TAG_COUNT] = {};
};

//template <class T>

template <class T> requires (sizeof(T) == 4)
struct TableIndexData {
	T indexvalues[2047][4];
};

struct TreeIndexData {

};

struct EntryData {

};

struct DbPage {
	uint16_t type = PageType::empty;
	union {
		StructureData structure;
		TagListData taglist;
		//TableIndexData table;
		TreeIndexData tree;
		EntryData entries;
		char unstructured[8190];
	};

	DbPage() {};
	DbPage(const DbPage& page) {};
};