#define _CRT_SECURE_NO_WARNINGS

#include "DbOperations.h"
#include "MurmurHash3.h"

int DbOperations::create_column(DbHandle* dbhandle, ColumnType coltype, std::string name)
{
	if (name.length() <= 0 || 
		name.length() > MAX_COLUMN_NAME_LENGTH || 
		(dbhandle->columncount + 1) > MAX_COLUMN_COUNT ||
		dbhandle->error)
	{
		return -1;
	}

	Column newCol = {
		coltype,
		"",
		false
	};
	strcpy(newCol.name, name.c_str());
	
	dbhandle->columns.push_back(newCol);
	return dbhandle->columns.size() - 1;
}

int DbOperations::create_entry(DbHandle* dbhandle, jsoncons::json* entry) {

	return false;
}

bool DbOperations::create_tag(DbHandle* dbhandle, std::string name, SimpleColor color)
{
	if (name.length() <= 0 ||
		name.length() + 1 > MAX_TAG_NAME_LENGTH ||
		dbhandle->error ||
		dbhandle->tagcount >= MAX_TAG_COUNT)
	{
		return false;
	}

	std::shared_ptr<DbPage> page;

	if (dbhandle->tagcount > 0) 
	{
		page = DbReader::load_page(dbhandle, 1);
	}
	else
	{
		page = std::make_shared<DbPage>();
		page->type = PageType::taglist;
	}

	TagListData* taglist = &(page->taglist);

	Tag newtag = {};
	strcpy(newtag.name, name.c_str());
	newtag.tagcolor = color;

	Tag* tags = taglist->tags;

	tags[taglist->totaltagnum] = newtag;
	taglist->totaltagnum += 1;

	dbhandle->tagcount = taglist->totaltagnum;
	dbhandle->tags.assign(tags, tags + taglist->totaltagnum);

	DbWriter::write_page(dbhandle, &*page, 1);

	return true;
}

std::set<uint32_t> DbOperations::lookup_by_string(DbHandle* dbhandle, uint8_t column, std::string lookup)
{
	if (dbhandle->columns[column].indexed) {
		auto index = DbReader::load_index(dbhandle, column);

		uint64_t seed = 7;
		uint32_t hash = 0;

		MurmurHash3_x86_32(lookup.c_str(), strlen(lookup.c_str()), seed, &hash);
		auto matches = index.at_or_null(std::to_string(hash));
		if (matches != NULL) {
			return matches.as<std::set<uint32_t>>();
		}
		else {
			return std::set<uint32_t>();
		}
	}
	else {
		return std::set<uint32_t>();
	}
}

std::set<uint32_t> DbOperations::intersection(std::set<uint32_t> set1, std::set<uint32_t> set2)
{
	std::set<uint32_t> result;
	for (auto entry : set1) {
		if (set2.find(entry) != set2.end()) {
			result.insert(entry);
		}
	}
	return result;
}
