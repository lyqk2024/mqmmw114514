// MenuUtils.h
#pragma once

#include <wx/wx.h>

// ================================
// 所有菜单命令 ID 集中定义
// ================================
enum MenuCommandIDs
{
    ID_EXPORT_IMAGE = wxID_HIGHEST + 1,

    // Edit 菜单
    ID_UNDO_REMOVE_WIRE,
    ID_CUT,
    ID_COPY,
    ID_PASTE,
    ID_DELETE,
    ID_DUPLICATE,
    ID_SELECT_ALL,
    ID_RAISE_SELECTION,
    ID_LOWER_SELECTION,
    ID_RAISE_TO_TOP,
    ID_LOWER_TO_BOTTOM,
    ID_ADD_VERTEX,
    ID_REMOVE_VERTEX,

    // Project 菜单
    ID_PROJECT_ADD_CIRCUIT,
    ID_PROJECT_LOAD_LIBRARY,
    ID_PROJECT_UNLOAD_LIBRARIES,
    ID_PROJECT_MOVE_CIRCUIT_UP,
    ID_PROJECT_MOVE_CIRCUIT_DOWN,
    ID_PROJECT_SET_MAIN,
    ID_PROJECT_REMOVE_CIRCUIT,
    ID_PROJECT_REVERT_APPEARANCE,
    ID_PROJECT_VIEW_TOOLBOX,
    ID_PROJECT_VIEW_SIM_TREE,
    ID_PROJECT_EDIT_LAYOUT,
    ID_PROJECT_EDIT_APPEARANCE,
    ID_PROJECT_ANALYZE,
    ID_PROJECT_STATISTICS,
    ID_PROJECT_OPTIONS,

    // Simulate 菜单
    ID_SIMULATION_ENABLED,
    ID_RESET_SIMULATION,
    ID_STEP_SIMULATION,
    ID_GO_OUT_TO_STATE,
    ID_GO_IN_TO_STATE,
    ID_TICK_ONCE,
    ID_TICKS_ENABLED,
    ID_TICK_FREQUENCY,
    ID_LOGGING,

    // Window 菜单
    ID_MINIMIZE,
    ID_MAXIMIZE,
    ID_CLOSE,
    ID_COMBINATIONAL_ANALYSIS,
    ID_PREFERENCES,
    ID_WINDOW_UNTITLED,

    // Help 菜单
    ID_TUTORIAL,
    ID_USERS_GUIDE,
    ID_LIBRARY_REFERENCE,
    ID_ABOUT
};

// 便捷函数声明
void AddMenuToBar(wxMenuBar* menuBar, wxMenu* menu, const wxString& label);

// 菜单创建函数声明
wxMenu* CreateFileMenu();
wxMenu* CreateEditMenu();
wxMenu* CreateProjectMenu();
wxMenu* CreateSimulateMenu();
wxMenu* CreateWindowMenu();
wxMenu* CreateHelpMenu();