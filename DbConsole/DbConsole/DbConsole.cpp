// DbConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "DbWriter.h"
#include "DbReader.h"

int main()
{
    std::ios::sync_with_stdio(false);

    std::cout << "dbpage size: " << sizeof(DbPage) << "\n";

    StructurePage testpage;
    Column testcol1 = { ColumnType::numi, "ID", 1, 1 };
    Column testcol2 = { ColumnType::phrase, "Short Name", 1, 2 };
    Column testcol3 = { ColumnType::tags, "Tags", 1, 3 };
    testpage.columns[0] = testcol1;
    testpage.columns[1] = testcol2;
    testpage.columns[2] = testcol3;

    std::cout << "\n\n\nSize of DbPage: " << sizeof(DbPage) << "\n";
    std::cout << "Size of TagListData: " << sizeof(TagListPage) << "\n\n\n";

    DbWriter::create_db("test.gddb");
    auto db = DbReader::open_db("test.gddb");

    std::cout << "\n\nTesting a page...\n";

    DbWriter::write_page(db, &testpage, 0);
    std::cout << "Page written!\n";

    auto returned_page = DbReader::load_page(db, 0);
    auto structure = reinterpret_cast<StructurePage*>(&*returned_page);
    std::cout << "Page read!\n";

    std::cout << "Number of columns: " << (int)structure->columncount << "\n";
    std::cout << "Columns:\n";
    for (int i = 0; i < (int)structure->columncount; i++) 
    {
        Column curcol = structure->columns[i];
        std::cout << "  [" << (int)curcol.type << "] " << curcol.name << " (column index at page " << curcol.idxpage << ", index " << curcol.idxindex << ")\n";
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
