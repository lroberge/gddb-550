#define _CRT_SECURE_NO_WARNINGS

#include "DbOperations.h"
#include "MurmurHash3.h"

bool DbOperations::create_column(DbHandle* dbhandle, ColumnType coltype, std::string name)
{
	if (name.length() <= 0 || 
		name.length() > MAX_COLUMN_NAME_LENGTH || 
		dbhandle->error)
	{
		return false;
	}


}

bool DbOperations::create_entry(DbHandle* dbhandle) {
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