#include "DbReader.h"

std::unique_ptr<DbHandle> DbReader::open_db(std::string path)
{
	auto dbhandle = std::make_unique<DbHandle>();

	std::ifstream db(path, std::ios::binary);
	if (db.is_open())
	{
		auto head = std::make_unique<DbHeader>();

		db.read(reinterpret_cast<char*>(&*head), sizeof(DbHeader));
		db.close();

		std::cout << "read magic: " << head->magic << "\n";
		std::cout << "read version: " << head->version << "\n";
		std::cout << "read format: " << (uint16_t)head->format << "\n";
		std::cout << "read dirty: " << head->dirty << "\n";
		std::cout << "read crc32: " << head->crc32 << "\n";
		std::cout << "read pagecount: " << head->pagecount << "\n";

		dbhandle->path = path;
		dbhandle->format = head->format;

		auto structure = load_structure_page(&*dbhandle);
		dbhandle->columncount = structure->columncount;
		dbhandle->columns.assign(structure->columncount, *(structure->columns));
	}
	else
	{
		dbhandle->error = true;
	}

	return dbhandle;
}

std::shared_ptr<DbPage> DbReader::load_page(DbHandle* dbhandle, uint16_t index)
{
	auto page = std::make_shared<DbPage>();

	if (dbhandle->error) 
	{
		page->type = PageType::empty;
		return page;
	}

	std::ifstream istr(dbhandle->path, std::ios::binary);

	istr.seekg(sizeof(DbHeader) + (PAGE_LENGTH * index), istr.beg);

	if (istr.is_open() && istr.good()) 
	{
		istr.read(reinterpret_cast<char*>(&*page), PAGE_LENGTH);
		istr.close();
	}
	else 
	{
		page->type = PageType::empty;
	}

	return page;
}

int DbReader::find_next_page(DbHandle* dbhandle, PageType type, int from = 1)
{
	std::ifstream istr(dbhandle->path, std::ios::binary);

	PageType currtype = PageType::empty;
	istr.seekg(sizeof(DbHeader) + (PAGE_LENGTH * from), istr.beg);
	for (int i = from; !istr.eof(); i++) {
		istr.read(reinterpret_cast<char*>(&currtype), 2);
		if (currtype == type) {
			istr.close();
			return i;
		}
		istr.seekg(sizeof(DbHeader) + (PAGE_LENGTH * i + 1), istr.beg);
	}
	istr.close();
	return -1;
}

std::shared_ptr<StructureData> DbReader::load_structure_page(DbHandle* dbhandle)
{
	auto structurepage = load_page(dbhandle, 0);
	if (structurepage->type == PageType::dbstructure) {
		return std::shared_ptr<StructureData>(structurepage, &(structurepage->structure));
	}
	else {
		return std::make_shared<StructureData>();
	}
}

