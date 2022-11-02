#define _CRT_SECURE_NO_WARNINGS

#include "DbOperations.h"

bool DbOperations::create_column(DbHandle* dbhandle, ColumnType coltype, std::string name)
{
	if (name.length() <= 0 || 
		name.length() > MAX_COLUMN_NAME_LENGTH || 
		dbhandle->error)
	{
		return false;
	}


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

	std::unique_ptr<DbPage> page;

	if (dbhandle->tagcount > 0) 
	{
		//page = DbReader::load_page(dbhandle, 1);
	}
	else
	{
		page = std::make_unique<TagListPage>();
	}

	TagListPage* taglist = reinterpret_cast<TagListPage*>(&page);

	Tag newtag = {};
	strcpy(newtag.name, name.c_str());
	newtag.tagcolor = color;

	taglist->tags[taglist->totaltagnum] = newtag;
	taglist->totaltagnum += 1;

	dbhandle->tagcount = taglist->totaltagnum;
	//dbhandle->tags.assign(&taglist->tags, &taglist->tags + taglist->totaltagnum);

	return true;
}