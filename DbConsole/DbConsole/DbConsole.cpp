// DbConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DbWriter.h"
#include "DbReader.h"

int main()
{
	std::ios::sync_with_stdio(false);

	std::cout << "dbpage size: " << sizeof(DbPage) << "\n";
	std::cout << "structure size: " << sizeof(StructureData) << "\n";
	std::cout << "taglist size: " << sizeof(TagListData) << "\n";

	StructureData teststructure = {};
	Index col1idx = { IndexType::table, 1, 1 };
	Column testcol1 = { ColumnType::numi, "ID", 1, col1idx };
	//testcol1.indexes[0] = col1idx;
	Index col2idx = { IndexType::table, 1, 2 };
	Column testcol2 = { ColumnType::phrase, "Short Name", 1, col2idx };
	//testcol2.indexes[0] = col2idx;
	Index col3idx1 = { IndexType::tree, 2, 1 }, col3idx2 = { IndexType::table, 1, 3 };
	Column testcol3 = { ColumnType::tags, "Tags", 2, col3idx1, col3idx2 };
	//testcol3.indexes[0] = col3idx1;
	//testcol3.indexes[1] = col3idx2;
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

	std::cout << "Done\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
