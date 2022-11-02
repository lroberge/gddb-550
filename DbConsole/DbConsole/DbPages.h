#pragma once

#include <cstdint>

#include "DbUtility.h"

const uint16_t MAX_COLUMN_COUNT = 102;
const uint16_t MAX_TAG_COUNT = 255;

struct DbPage {
	uint16_t type;
};

struct StructurePage : DbPage {
	uint8_t columncount = 0;
	Column columns[MAX_COLUMN_COUNT];

	char padding[28];

	StructurePage() {
		this->type = PageType::dbstructure;
	}
};

struct TagListPage : DbPage {
	uint8_t totaltagnum = 0;
	Tag tags[MAX_TAG_COUNT];

	char padding[28];

	TagListPage() {
		this->type = PageType::taglist;
	}
};

struct TreePage : DbPage {


	TreePage() {
		this->type = PageType::tree;
	}
};

struct EntryPage : DbPage {


	EntryPage() {
		this->type = PageType::entry;
	}
};