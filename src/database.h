/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#ifndef EXAMPLE_CLASS_H
#define EXAMPLE_CLASS_H

// We don't need windows.h in this example plugin but many others do, and it can
// lead to annoying situations due to the ton of macros it defines.
// So we include it and make sure CI warns us if we use something that conflicts
// with a Windows define.
// #ifdef WIN32
// #include <windows.h>
// #endif

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/dictionary.hpp>

#include "DbUtility.h"
#include "DbReader.h"

using namespace godot;

class Database : public Object {
	GDCLASS(Database, Object);

public:
	Database(String path);
	Database(Database &db);
	~Database();

	TypedArray<Dictionary> query_column(String column);

protected:
	static void _bind_methods();

	std::unique_ptr<DbHandle> handle;
};

// VARIANT_ENUM_CAST(DatabaseUI, Constants);

#endif // EXAMPLE_CLASS_H
