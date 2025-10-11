// MenuUtils.cpp
#include "MenuUtils.h"
#include <wx/menu.h> // Include necessary wxWidgets header

// You would typically define the ID constants (like ID_EXPORT_IMAGE, etc.) in MenuUtils.h or a common header.

/**
 * @brief Appends a wxMenu to a wxMenuBar with a given label.
 *
 * @param menuBar The menu bar to append to.
 * @param menu The menu to append.
 * @param label The label for the menu on the menu bar (e.g., "&File").
 */
void AddMenuToBar(wxMenuBar* menuBar, wxMenu* menu, const wxString& label)
{
    if (menuBar && menu)
        menuBar->Append(menu, label);
}

//---

/**
 * @brief Creates the standard File menu.
 * @return A new wxMenu object.
 */
wxMenu* CreateFileMenu()
{
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW, "&New\tCtrl+N", "Create a new document");
    fileMenu->Append(wxID_OPEN, "&Open...\tCtrl+O", "Open an existing document");

    // Open Recent Sub-Menu
    wxMenu* openRecentMenu = new wxMenu;
    openRecentMenu->Append(wxID_ANY, "Recent File 1");
    openRecentMenu->Append(wxID_ANY, "Recent File 2");
    fileMenu->AppendSubMenu(openRecentMenu, "Open &Recent");

    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_CLOSE, "&Close\tCtrl+Shift+W", "Close the current document");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl+S", "Save the current document");
    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl+Shift+S", "Save the document with a new name");

    fileMenu->AppendSeparator();
    fileMenu->Append(ID_EXPORT_IMAGE, "Export &Image...\tCtrl+Shift+E", "Export the current image");
    fileMenu->Append(wxID_PRINT, "&Print...\tCtrl+P", "Print the current document");

    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_PREFERENCES, "&Preferences...\tCtrl+,", "Edit preferences"); // Common shortcut: Ctrl+,
    fileMenu->Append(wxID_EXIT, "E&xit\tCtrl+Q", "Exit the application");

    return fileMenu;
}

//---

/**
 * @brief Creates the standard Edit menu.
 * @return A new wxMenu object.
 */
wxMenu* CreateEditMenu()
{
    wxMenu* menu = new wxMenu;
    // Note: ID_UNDO_REMOVE_WIRE is a specific 'Undo' action; a general wxID_UNDO might be more typical.
    menu->Append(ID_UNDO_REMOVE_WIRE, "Undo Remove Wire\tCtrl+Z");
    menu->AppendSeparator();
    menu->Append(ID_CUT, "Cut\tCtrl+X");
    menu->Append(ID_COPY, "Copy\tCtrl+C");
    menu->Append(ID_PASTE, "Paste\tCtrl+V");
    menu->AppendSeparator();
    menu->Append(ID_DELETE, "Delete\tDelete");
    menu->Append(ID_DUPLICATE, "Duplicate\tCtrl+D");
    menu->Append(ID_SELECT_ALL, "Select All\tCtrl+A");
    menu->AppendSeparator();
    menu->Append(ID_RAISE_SELECTION, "Raise Selection\tCtrl+Up", "Move selected elements up a layer");
    menu->Append(ID_LOWER_SELECTION, "Lower Selection\tCtrl+Down", "Move selected elements down a layer");
    menu->Append(ID_RAISE_TO_TOP, "Raise To Top\tCtrl+Shift+Up", "Move selected elements to the top layer");
    menu->Append(ID_LOWER_TO_BOTTOM, "Lower To Bottom\tCtrl+Shift+Down", "Move selected elements to the bottom layer");
    menu->AppendSeparator();
    menu->Append(ID_ADD_VERTEX, "Add Vertex\tCtrl+Alt+A", "Add a vertex to a selected wire");
    menu->Append(ID_REMOVE_VERTEX, "Remove Vertex\tCtrl+Alt+R", "Remove a vertex from a selected wire");
    return menu;
}

//---

/**
 * @brief Creates the Project-specific menu.
 * @return A new wxMenu object.
 */
wxMenu* CreateProjectMenu()
{
    wxMenu* menu = new wxMenu;
    menu->Append(ID_PROJECT_ADD_CIRCUIT, "Add Circuit...\tCtrl+Alt+N");
    menu->Append(ID_PROJECT_LOAD_LIBRARY, "Load Library...\tCtrl+Alt+L");
    menu->Append(ID_PROJECT_UNLOAD_LIBRARIES, "Unload Libraries...\tCtrl+Alt+U");

    menu->AppendSeparator();
    menu->Append(ID_PROJECT_MOVE_CIRCUIT_UP, "Move Circuit Up\tAlt+Up");
    menu->Append(ID_PROJECT_MOVE_CIRCUIT_DOWN, "Move Circuit Down\tAlt+Down");
    menu->Append(ID_PROJECT_SET_MAIN, "Set As Main\tCtrl+Alt+M");
    menu->Append(ID_PROJECT_REMOVE_CIRCUIT, "Remove Circuit\tCtrl+Alt+Delete");

    menu->AppendSeparator();
    menu->Append(ID_PROJECT_REVERT_APPEARANCE, "Revert Appearance\tCtrl+Alt+P");

    menu->AppendCheckItem(ID_PROJECT_VIEW_TOOLBOX, "View Toolbox\tCtrl+1");
    menu->AppendCheckItem(ID_PROJECT_VIEW_SIM_TREE, "View Simulation Tree\tCtrl+2");

    menu->AppendSeparator();

    menu->Append(ID_PROJECT_EDIT_LAYOUT, "Edit Layout\tCtrl+L");
    // Updated 'Edit Appearance' shortcut to Ctrl+Shift+P to avoid conflict with wxID_PRINT (Ctrl+P) in File menu.
    menu->Append(ID_PROJECT_EDIT_APPEARANCE, "Edit Appearance\tCtrl+Shift+P");

    menu->AppendSeparator();
    menu->Append(ID_PROJECT_ANALYZE, "Analyze Circuit\tF5");
    menu->Append(ID_PROJECT_STATISTICS, "Show Statistics\tF4");
    menu->Append(ID_PROJECT_OPTIONS, "Project Options...\tAlt+Enter");
    return menu;
}

//---

/**
 * @brief Creates the Simulate-specific menu.
 * @return A new wxMenu object.
 */
wxMenu* CreateSimulateMenu()
{
    wxMenu* simulateMenu = new wxMenu;

    wxMenuItem* simulationEnabledItem = new wxMenuItem(simulateMenu, ID_SIMULATION_ENABLED, "&Simulation Enabled\tCtrl+E", "Toggle simulation on/off", wxITEM_CHECK);
    simulateMenu->Append(simulationEnabledItem);

    simulateMenu->Append(ID_RESET_SIMULATION, "Reset &Simulation\tCtrl+R", "Reset the current simulation");
    simulateMenu->Append(ID_STEP_SIMULATION, "Step &Simulation\tCtrl+I", "Step through the simulation");

    // Go Out To State Sub-Menu
    wxMenu* goOutToStateMenu = new wxMenu;
    goOutToStateMenu->Append(wxID_ANY, "State 1");
    goOutToStateMenu->Append(wxID_ANY, "State 2");
    simulateMenu->AppendSubMenu(goOutToStateMenu, "Go Out To &State\tShift+O");

    // Go In To State Sub-Menu
    wxMenu* goInToStateMenu = new wxMenu;
    goInToStateMenu->Append(wxID_ANY, "State 1");
    goInToStateMenu->Append(wxID_ANY, "State 2");
    simulateMenu->AppendSubMenu(goInToStateMenu, "Go In To &State\tShift+I");

    simulateMenu->AppendSeparator();
    simulateMenu->Append(ID_TICK_ONCE, "Tick &Once\tCtrl+T", "Perform a single tick of the simulation");

    // Ticks Enabled Check Item
    wxMenuItem* ticksEnabledItem = new wxMenuItem(simulateMenu, ID_TICKS_ENABLED, "&Ticks Enabled\tCtrl+K", "Toggle automatic ticking", wxITEM_CHECK);
    simulateMenu->Append(ticksEnabledItem);

    // Tick Frequency Sub-Menu
    wxMenu* tickFrequencyMenu = new wxMenu;
    tickFrequencyMenu->Append(wxID_ANY, "1 Hz");
    tickFrequencyMenu->Append(wxID_ANY, "10 Hz");
    tickFrequencyMenu->Append(wxID_ANY, "100 Hz");
    simulateMenu->AppendSubMenu(tickFrequencyMenu, "Tick &Frequency\tCtrl+F");

    simulateMenu->AppendSeparator();
    simulateMenu->Append(ID_LOGGING, "&Logging...\tCtrl+L", "Configure logging options");

    return simulateMenu;
}

//---

/**
 * @brief Creates the standard Window menu.
 * @return A new wxMenu object.
 */
wxMenu* CreateWindowMenu()
{
    wxMenu* windowMenu = new wxMenu;
    windowMenu->Append(ID_MINIMIZE, "&Minimize\tCtrl+M", "Minimize the application");
    windowMenu->Append(ID_MAXIMIZE, "&Maximize\tCtrl+Alt+X", "Maximize the application");
    windowMenu->Append(ID_CLOSE, "&Close\tCtrl+W", "Close the current window");
    windowMenu->AppendSeparator();

    windowMenu->Append(ID_COMBINATIONAL_ANALYSIS, "Combinational &Analysis\tF6", "Perform combinational analysis");

    // Re-appending Preferences here is fine, common in Mac applications, though it uses the same ID and shortcut as the one in the File menu.
    windowMenu->Append(ID_PREFERENCES, "&Preferences\tCtrl+,", "Configure preferences");

    // Untitled Window Item
    wxMenuItem* untitledItem = new wxMenuItem(windowMenu, ID_WINDOW_UNTITLED, "&Untitled\tF7", "Focus on the Untitled window", wxITEM_CHECK);
    // You would typically call untitledItem->Check(true) elsewhere when the window is active.
    windowMenu->Append(untitledItem);

    return windowMenu;
}

//---

/**
 * @brief Creates the standard Help menu.
 * @return A new wxMenu object.
 */
wxMenu* CreateHelpMenu()
{
    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(ID_TUTORIAL, "&Tutorial\tF1", "Open the tutorial");
    helpMenu->Append(ID_USERS_GUIDE, "&User's Guide\tCtrl+F1", "Open the user's guide");
    helpMenu->Append(ID_LIBRARY_REFERENCE, "&Library Reference\tShift+F1", "Open the library reference");
    helpMenu->AppendSeparator();
    helpMenu->Append(ID_ABOUT, "&About...\tF2", "Show about dialog");
    return helpMenu;
}