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

		//std::cout << "\nformat as enum: " << (DbFormat)dbhandle.format << "\n";

		//std::cout << "\n\n\nsizeof Column: " << sizeof(Column) << "\n";
		//std::cout << "sizeof PageData: " << sizeof(PageData) << "\n";
		//std::cout << "sizeof DbPage: " << sizeof(DbPage) << "\n";
	}
	else
	{
		dbhandle->error = true;
	}

	return dbhandle;
}

std::unique_ptr<DbPage> DbReader::load_page(DbHandle* dbhandle, uint16_t index)
{
	auto page = std::make_unique<DbPage>();

	if (dbhandle->error) 
	{
		page->type = PageType::empty;
		return page;
	}

	std::ifstream istr(dbhandle->path, std::ios::binary);

	istr.seekg(sizeof(DbHeader) + (sizeof(DbPage) * index), istr.beg);

	if (istr.is_open() && istr.good()) 
	{
		istr.read(reinterpret_cast<char*>(&*page), sizeof(DbPage));
		istr.close();
	}
	else 
	{
		page->type = PageType::empty;
	}

	return page;
}

std::unique_ptr<DbPage> DbReader::load_structure_page(DbHandle* dbhandle)
{
	auto structurepage = load_page(dbhandle, 0);
	if (structurepage->type == PageType::dbstructure) {
		return structurepage;
	}
}

