// DbConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DbWriter.h"
#include "DbReader.h"
#include "DbOperations.h"

int main()
{
	std::ios::sync_with_stdio(false);

	std::cout << "dbpage size: " << sizeof(DbPage) << "\n";
	std::cout << "structure size: " << sizeof(StructureData) << "\n";
	std::cout << "taglist size: " << sizeof(TagListData) << "\n";
	std::cout << "tableindex size: " << sizeof(TableIndexData) << "\n";

	StructureData teststructure = {};
	Index col1idx = { IndexType::table, 1, 1 };
	Column testcol1 = { ColumnType::numi, "ID", 1, col1idx };
	Index col2idx = { IndexType::table, 1, 2 };
	Column testcol2 = { ColumnType::phrase, "Short Name", 1, col2idx };
	Index col3idx1 = { IndexType::tree, 2, 1 }, col3idx2 = { IndexType::table, 1, 3 };
	Column testcol3 = { ColumnType::tags, "Tags", 2, col3idx1, col3idx2 };
	teststructure.columncount = 3;
	teststructure.columns[0] = testcol1;
	teststructure.columns[1] = testcol2;
	teststructure.columns[2] = testcol3;
	DbPage testpage = {};
	testpage.type = PageType::dbstructure;
	testpage.structure = teststructure;

	DbWriter::create_db("test.gddb");
	auto db = DbReader::open_db("test.gddb");

	std::cout << "\n\nTesting a page...\n";

	DbWriter::write_page(&*db, &testpage, 0);
	std::cout << "Page written!\n";

	auto read_structure = DbReader::load_structure_page(&*db);
	std::cout << "Page read!\n";

	std::cout << "Number of columns: " << (int)read_structure->columncount << "\n";
	std::cout << "Columns:\n";
	for (int i = 0; i < (int)read_structure->columncount; i++)
	{
		Column curcol = read_structure->columns[i];
		std::cout << "  [" << (int)curcol.type << "] " << curcol.name << ":\n";
		for (int j = 0; j < (int)curcol.numindexes; j++)
		{
			Index curidx = curcol.indexes[j];
			std::cout << "    (" << ((curidx.type == IndexType::table) ? "table" : "tree") << " index on page " << curidx.idxpage << " at index " << curidx.idxindex << ")\n";
		}
	}

	DbOperations::create_tag(&*db, "test tag", { 255, 255, 255 });

	std::cout << "Done\n";

}
