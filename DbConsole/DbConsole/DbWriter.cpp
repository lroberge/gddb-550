//#ifdef _MSC_VER
//#define _CRT_SECURE_NO_WARNINGS
//#endif

#include "DbWriter.h"

DbHandle DbWriter::create_db(std::string path)
{
	DbHandle dbhandle = DbHandle();

	DbHeader head = {
		"gdb",
		1,
		DbFormat::paged,
		false,
		0,
		3
	};

	std::fstream db(path, std::ios::out | std::ios::binary | std::ios::trunc);
	if (db.is_open())
	{
		db.write((char*)&head, sizeof(DbHeader));
		db.close();

		// Set up db handle with initial values
		dbhandle.path = path;
		dbhandle.entriespath = path.substr(0, path.length() - 5) + ".bson";
		dbhandle.format = DbFormat::paged;
		dbhandle.columncount = 0;
		//dbhandle.columns = nullptr;

		// Write empty structure page into db
		DbPage structurepage = {};
		structurepage.type = PageType::dbstructure;
		structurepage.structure = StructureData();

		write_page(&dbhandle, &structurepage, 0);

		std::cout << "Successfully created db!\n\n";
	}
	else
	{
		dbhandle.error = true;
	}

	return dbhandle;
}

bool DbWriter::write_page(DbHandle* dbhandle, DbPage* page, uint16_t index)
{
	if (dbhandle->error)
	{
		return false;
	}

	std::fstream ostr(dbhandle->path, std::ios::in | std::ios::out | std::ios::binary);

	ostr.seekp(sizeof(DbHeader) + (PAGE_LENGTH * index), std::ios_base::beg);

	if (ostr.is_open() && ostr.good())
	{
		ostr.write((char*)page, PAGE_LENGTH);
		ostr.close();
	}
	else
	{
		return false;
	}

	return true;
}

bool DbWriter::write_entries(DbHandle* dbhandle, jsoncons::ojson* entries)
{
	if (dbhandle->error)
	{
		return false;
	}

	std::fstream ostr(dbhandle->entriespath, std::ios::out | std::ios::binary | std::ios::trunc);

	if (ostr.is_open() && ostr.good())
	{
		std::vector<uint8_t> bsondata;
		jsoncons::bson::encode_bson(*entries, bsondata);

		ostr.write(reinterpret_cast<const char*>(bsondata.data()), bsondata.size());
		return true;
	}
	else
	{
		return false;
	}
}