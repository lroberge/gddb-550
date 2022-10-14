@tool
extends EditorPlugin

const DBPanel = preload("res://addons/gddb/DatabaseDock.tscn")

var DBPanel_instance

func _enter_tree():
	DBPanel_instance = DBPanel.instantiate()
	# Add the main panel to the editor's main viewport.
	get_editor_interface().get_editor_main_screen().add_child(DBPanel_instance)
	# Hide the main panel. Very much required.
	_make_visible(false)


func _exit_tree():
	if DBPanel_instance:
		DBPanel_instance.queue_free()

func _has_main_screen():
	return true

func _make_visible(visible):
	if DBPanel_instance:
		DBPanel_instance.visible = visible
		get_editor_interface().get_editor_main_screen()

func _get_plugin_name():
	return "GDDB"
	
func _get_plugin_icon():
	# Must return some kind of Texture for the icon.
	return get_editor_interface().get_base_control().get_theme_icon("PackedDataContainer", "EditorIcons")
