// DbConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <jsoncons/json.hpp>
#include <jsoncons_ext/bson/bson.hpp>

#include "DbWriter.h"
#include "DbReader.h"
#include "DbOperations.h"


using jsoncons::json;
namespace bson = jsoncons::bson;

int main()
{
	std::ios::sync_with_stdio(false);

	//std::cout << "dbpage size: " << sizeof(DbPage) << "\n";
	//std::cout << "structure size: " << sizeof(StructureData) << "\n";
	//std::cout << "taglist size: " << sizeof(TagListData) << "\n";
	//std::cout << "tableindex size: " << sizeof(TableIndexData) << "\n";
	//std::cout << "entrydata size: " << sizeof(EntryData) << "\n";
	//return 0;

	//StructureData teststructure = {};
	//Index col1idx = { IndexType::table, 1, 1 };
	//Column testcol1 = { ColumnType::numi, "ID", 1, col1idx };
	//Index col2idx = { IndexType::table, 1, 2 };
	//Column testcol2 = { ColumnType::string, "Short Name", 1, col2idx };
	//Index col3idx1 = { IndexType::tree, 2, 1 }, col3idx2 = { IndexType::table, 1, 3 };
	//Column testcol3 = { ColumnType::tags, "Tags", 2, col3idx1, col3idx2 };
	//teststructure.columncount = 3;
	//teststructure.columns[0] = testcol1;
	//teststructure.columns[1] = testcol2;
	//teststructure.columns[2] = testcol3;
	//DbPage testpage = {};
	//testpage.type = PageType::dbstructure;
	//testpage.structure = teststructure;

	DbWriter::create_db("test.gddb");
	auto db = DbReader::open_db("test.gddb");

	//std::cout << "\n\nTesting a page...\n";

	//DbWriter::write_page(&*db, &testpage, 0);
	//std::cout << "Page written!\n";

	//auto read_structure = DbReader::load_structure_page(&*db);
	//std::cout << "Page read!\n";

	//std::cout << "Number of columns: " << (int)read_structure->columncount << "\n";
	//std::cout << "Columns:\n";
	//for (int i = 0; i < (int)read_structure->columncount; i++)
	//{
	//	Column curcol = read_structure->columns[i];
	//	std::cout << "  [" << (int)curcol.type << "] " << curcol.name << ":\n";
	//	for (int j = 0; j < (int)curcol.numindexes; j++)
	//	{
	//		Index curidx = curcol.indexes[j];
	//		std::cout << "    (" << ((curidx.type == IndexType::table) ? "table" : "tree") << " index on page " << curidx.idxpage << " at index " << curidx.idxindex << ")\n";
	//	}
	//}

	//DbOperations::create_tag(&*db, "test tag", { 255, 255, 255 });

	DbOperations::create_column(&*db, ColumnType::string, "name");
	DbOperations::create_column(&*db, ColumnType::string, "type");
	DbOperations::create_column(&*db, ColumnType::string, "tier");
	DbOperations::create_column(&*db, ColumnType::string, "flavorText");
	
	std::ifstream is("test_destiny.json");
	jsoncons::ojson testjson = jsoncons::ojson::parse(is);
	DbWriter::write_entries(&*db, &testjson);
	DbReader::load_entries(&*db);

	std::cout << db->entries << "\n";

	std::cout << "Attempting to index..." << "\n";
	DbWriter::create_string_index(&*db, 0);
	DbWriter::create_string_index(&*db, 1);
	DbWriter::create_string_index(&*db, 2);
	std::cout << "Successfully indexed" << "\n\n";

	std::cout << "Searching for 'Exotic':" << "\n";
	auto exotics = DbOperations::lookup_by_string(&*db, 2, "Exotic");
	std::cout << "Found matches at indices ";
	for (auto match : exotics)
	{
		std::cout << std::to_string(match) << ", ";
	}
	std::cout << "\n\n";

	std::cout << "Searching for 'Gauntlets':" << "\n";
	auto gauntlets = DbOperations::lookup_by_string(&*db, 1, "Gauntlets");
	std::cout << "Found matches at indices ";
	for (auto match : gauntlets)
	{
		std::cout << std::to_string(match) << ", ";
	}
	std::cout << "\n\n";

	std::cout << "Searching for 'Exotic' and 'Gauntlets':" << "\n";
	auto exotic_gauntlets = DbOperations::intersection(exotics, gauntlets);
	std::cout << "Found matches at indices ";
	for (auto match : exotic_gauntlets)
	{
		std::cout << std::to_string(match) << ", ";
	}
	std::cout << "\n\n";

	std::cout << "Done\n";

}
