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
		dbhandle.basepath = path.substr(0, path.length() - 5);
		dbhandle.path = path;
		dbhandle.entriespath = dbhandle.basepath + ".bson";
		dbhandle.entries = jsoncons::ojson::parse(R"({"entries": []})");
		dbhandle.format = DbFormat::paged;
		dbhandle.columncount = 0;
		//dbhandle.columns = nullptr;

		// Write empty structure page into db
		DbPage structurepage = {};
		structurepage.type = PageType::dbstructure;
		structurepage.structure = StructureData();

		write_page(&dbhandle, &structurepage, 0);

		DbWriter::write_entries(&dbhandle, &dbhandle.entries);

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

bool DbWriter::create_string_index(DbHandle* dbhandle, uint8_t column)
{
	if (dbhandle->error ||
		dbhandle->columns.size() < column ||
		dbhandle->columns[column].type != ColumnType::string)
	{
		return false;
	}

	std::string path = dbhandle->path;
	auto colname = dbhandle->columns[column].name;

	std::fstream ostr(dbhandle->basepath + "_" + std::to_string(column) + ".index", std::ios::out | std::ios::binary | std::ios::trunc);

	if (ostr.is_open() && ostr.good())
	{
		std::map<uint64_t, std::vector<uint32_t>> stringIndexMap;

		uint64_t seed = 7;
		uint32_t hash = 0;

		uint32_t currIndex = 0;
		for (auto& entry : dbhandle->entries.array_range())
		{
			MurmurHash3_x86_32(entry.at_or_null(colname).as_cstring(), strlen(entry.at_or_null(colname).as_cstring()), seed, &hash);
			if (!stringIndexMap.contains(hash))
			{
				std::vector<uint32_t> newEntry{ currIndex };
				stringIndexMap.insert_or_assign(hash, newEntry);
			}
			else {
				stringIndexMap.at(hash).push_back(currIndex);
			}

			currIndex += 1;
		}

		std::vector<uint8_t> buffer;
		jsoncons::bson::bson_bytes_encoder encoder(buffer);

		encoder.begin_object();
		for (auto& indexEntry : stringIndexMap)
		{
			encoder.key(std::to_string(indexEntry.first));
			encoder.begin_array();
			for (auto& dbEntry : indexEntry.second) 
			{
				encoder.uint64_value(dbEntry);
			}
			encoder.end_array();
		}
		encoder.end_object();
		encoder.flush();

		ostr.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());

		dbhandle->columns[column].indexed = true;

		return true;
	}
	else
	{
		return false;
	}

	return false;
}

bool DbWriter::index_string_entry(DbHandle* dbhandle, uint8_t column, uint32_t entry)
{
	if (dbhandle->error || dbhandle->entries.size() < entry || dbhandle->columncount < column)
	{
		return false;
	}



	return false;
}

bool DbWriter::deindex_string_entry(DbHandle* dbhandle, uint8_t column, uint32_t entry)
{
	return false;
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