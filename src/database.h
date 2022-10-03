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

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>

using namespace godot;

class DatabaseUI : public EditorPlugin {
	GDCLASS(DatabaseUI, EditorPlugin);

public:
	static void _bind_methods();

	bool _has_main_screen() const;
	String _get_plugin_name() const;
	Ref<Texture2D> _get_plugin_icon();


	DatabaseUI();
	~DatabaseUI();
};

// VARIANT_ENUM_CAST(DatabaseUI, Constants);

#endif // EXAMPLE_CLASS_H
