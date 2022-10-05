/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#include "database.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/editor_interface.hpp>

using namespace godot;

void DatabaseUI::_enter_tree() {

}

void DatabaseUI::_exit_tree() {
	
}

bool DatabaseUI::_has_main_screen() const {
	UtilityFunctions::print("Has main screen");
	return true;
}

String DatabaseUI::_get_plugin_name() const {
	return "GDDB Plugin";
}

Ref<Texture2D> DatabaseUI::_get_plugin_icon() {
	return *get_editor_interface()->get_base_control()->get_theme_icon("Node", "EditorIcons");
}

void DatabaseUI::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_enter_tree"), &DatabaseUI::_enter_tree);
	ClassDB::bind_method(D_METHOD("_exit_tree"), &DatabaseUI::_exit_tree);
	ClassDB::bind_method(D_METHOD("has_main_screen"), &DatabaseUI::_has_main_screen);
	ClassDB::bind_method(D_METHOD("get_plugin_name"), &DatabaseUI::_get_plugin_name);
	ClassDB::bind_method(D_METHOD("get_plugin_icon"), &DatabaseUI::_get_plugin_icon);

	// // Methods.
	// ClassDB::bind_method(D_METHOD("simple_func"), &DatabaseUI::simple_func);
	// ClassDB::bind_method(D_METHOD("simple_const_func"), &DatabaseUI::simple_const_func);
	// ClassDB::bind_method(D_METHOD("return_something"), &DatabaseUI::return_something);

	// ClassDB::bind_method(D_METHOD("test_array"), &DatabaseUI::test_array);
	// ClassDB::bind_method(D_METHOD("test_dictionary"), &DatabaseUI::test_dictionary);

	// ClassDB::bind_method(D_METHOD("def_args", "a", "b"), &DatabaseUI::def_args, DEFVAL(100), DEFVAL(200));

	// ClassDB::bind_static_method("Example", D_METHOD("test_static", "a", "b"), &DatabaseUI::test_static);
	// ClassDB::bind_static_method("Example", D_METHOD("test_static2"), &DatabaseUI::test_static2);

	// {
	// 	MethodInfo mi;
	// 	mi.arguments.push_back(PropertyInfo(Variant::STRING, "some_argument"));
	// 	mi.name = "varargs_func";
	// 	ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_func", &DatabaseUI::varargs_func, mi);
	// }

	// {
	// 	MethodInfo mi;
	// 	mi.arguments.push_back(PropertyInfo(Variant::STRING, "some_argument"));
	// 	mi.name = "varargs_func_nv";
	// 	ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_func_nv", &DatabaseUI::varargs_func_nv, mi);
	// }

	// {
	// 	MethodInfo mi;
	// 	mi.arguments.push_back(PropertyInfo(Variant::STRING, "some_argument"));
	// 	mi.name = "varargs_func_void";
	// 	ClassDB::bind_vararg_method(METHOD_FLAGS_DEFAULT, "varargs_func_void", &DatabaseUI::varargs_func_void, mi);
	// }

	// // Properties.
	// ADD_GROUP("Test group", "group_");
	// ADD_SUBGROUP("Test subgroup", "group_subgroup_");

	// ClassDB::bind_method(D_METHOD("get_custom_position"), &DatabaseUI::get_custom_position);
	// ClassDB::bind_method(D_METHOD("get_v4"), &DatabaseUI::get_v4);
	// ClassDB::bind_method(D_METHOD("set_custom_position", "position"), &DatabaseUI::set_custom_position);
	// ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "group_subgroup_custom_position"), "set_custom_position", "get_custom_position");

	// // Signals.
	// ADD_SIGNAL(MethodInfo("custom_signal", PropertyInfo(Variant::STRING, "name"), PropertyInfo(Variant::INT, "value")));
	// ClassDB::bind_method(D_METHOD("emit_custom_signal", "name", "value"), &DatabaseUI::emit_custom_signal);

	// // Constants.
	// BIND_ENUM_CONSTANT(FIRST);
	// BIND_ENUM_CONSTANT(ANSWER_TO_EVERYTHING);

	// BIND_CONSTANT(CONSTANT_WITHOUT_ENUM);
}

DatabaseUI::DatabaseUI() {
	UtilityFunctions::print("Constructor.");
}

DatabaseUI::~DatabaseUI() {
	UtilityFunctions::print("Destructor.");
}
