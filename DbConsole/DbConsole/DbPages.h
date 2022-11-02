#pragma once

#include <cstdint>

#include "DbUtility.h"

const uint16_t MAX_COLUMN_COUNT = 100;
const uint16_t MAX_TAG_COUNT = 255;

struct DbPage {
	uint16_t type;
	char* data[8190];
};

struct StructurePage : DbPage {
	uint8_t columncount;
	Column columns[MAX_COLUMN_COUNT];

	StructurePage() {
		this->type = PageType::dbstructure;
	}
};

struct TagListPage : DbPage {
	uint8_t totaltagnum = 0;
	Tag tags[MAX_TAG_COUNT];

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