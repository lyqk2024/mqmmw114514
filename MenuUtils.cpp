// MenuUtils.cpp
#include "MenuUtils.h"

void AddMenuToBar(wxMenuBar* menuBar, wxMenu* menu, const wxString& label)
{
    if (menuBar && menu)
        menuBar->Append(menu, label);
}

wxMenu* CreateFileMenu()
{
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW, "&New\tCtrl+N", "Create a new document");
    fileMenu->Append(wxID_OPEN, "&Open...\tCtrl+O", "Open an existing document");

    wxMenu* openRecentMenu = new wxMenu;
    openRecentMenu->Append(wxID_ANY, "Recent File 1");
    openRecentMenu->Append(wxID_ANY, "Recent File 2");
    fileMenu->AppendSubMenu(openRecentMenu, "Open &Recent");

    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_CLOSE, "&Close\tCtrl+Shift+W", "Close the current document");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl+S", "Save the current document");
    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl+Shift+S", "Save the document with a new name");

    fileMenu->AppendSeparator();
    fileMenu->Append(ID_EXPORT_IMAGE, "Export &Image...", "Export the current image");
    fileMenu->Append(wxID_PRINT, "&Print...\tCtrl+P", "Print the current document");

    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_PREFERENCES, "&Preferences...", "Edit preferences");
    fileMenu->Append(wxID_EXIT, "E&xit\tCtrl+Q", "Exit the application");

    return fileMenu;
}

wxMenu* CreateEditMenu()
{
    wxMenu* menu = new wxMenu;
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
    menu->Append(ID_RAISE_SELECTION, "Raise Selection\tCtrl+Up");
    menu->Append(ID_LOWER_SELECTION, "Lower Selection\tCtrl+Down");
    menu->Append(ID_RAISE_TO_TOP, "Raise To Top\tCtrl+Shift+Up");
    menu->Append(ID_LOWER_TO_BOTTOM, "Lower To Bottom\tCtrl+Shift+Down");
    menu->AppendSeparator();
    menu->Append(ID_ADD_VERTEX, "Add Vertex");
    menu->Append(ID_REMOVE_VERTEX, "Remove Vertex");
    return menu;
}

wxMenu* CreateProjectMenu()
{
    wxMenu* menu = new wxMenu;
    menu->Append(ID_PROJECT_ADD_CIRCUIT, "Add Circuit...");
    menu->Append(ID_PROJECT_LOAD_LIBRARY, "Load Library...");
    menu->Append(ID_PROJECT_UNLOAD_LIBRARIES, "Unload Libraries...");
    menu->AppendSeparator();
    menu->Append(ID_PROJECT_MOVE_CIRCUIT_UP, "Move Circuit Up");
    menu->Append(ID_PROJECT_MOVE_CIRCUIT_DOWN, "Move Circuit Down");
    menu->Append(ID_PROJECT_SET_MAIN, "Set As Main");
    menu->Append(ID_PROJECT_REMOVE_CIRCUIT, "Remove Circuit");
    menu->AppendSeparator();
    menu->Append(ID_PROJECT_REVERT_APPEARANCE, "Revert Appearance");
    menu->AppendCheckItem(ID_PROJECT_VIEW_TOOLBOX, "View Toolbox");
    menu->AppendCheckItem(ID_PROJECT_VIEW_SIM_TREE, "View Simulation Tree");
    menu->AppendSeparator();
    menu->Append(ID_PROJECT_EDIT_LAYOUT, "Edit Layout");
    menu->Append(ID_PROJECT_EDIT_APPEARANCE, "Edit Appearance");
    menu->AppendSeparator();
    menu->Append(ID_PROJECT_ANALYZE, "Analyze Circuit");
    menu->Append(ID_PROJECT_STATISTICS, "Show Statistics");
    menu->Append(ID_PROJECT_OPTIONS, "Project Options...");
    return menu;
}

wxMenu* CreateSimulateMenu()
{
    wxMenu* simulateMenu = new wxMenu;

    wxMenuItem* simulationEnabledItem = new wxMenuItem(simulateMenu, ID_SIMULATION_ENABLED, "&Simulation Enabled\tCtrl+E", "", wxITEM_CHECK);
    //simulationEnabledItem->Check(true);
    simulateMenu->Append(simulationEnabledItem);

    simulateMenu->Append(ID_RESET_SIMULATION, "Reset &Simulation\tCtrl+R", "Reset the current simulation");
    simulateMenu->Append(ID_STEP_SIMULATION, "Step &Simulation\tCtrl+I", "Step through the simulation");

    wxMenu* goOutToStateMenu = new wxMenu;
    goOutToStateMenu->Append(wxID_ANY, "State 1");
    goOutToStateMenu->Append(wxID_ANY, "State 2");
    simulateMenu->AppendSubMenu(goOutToStateMenu, "Go Out To &State");

    wxMenu* goInToStateMenu = new wxMenu;
    goInToStateMenu->Append(wxID_ANY, "State 1");
    goInToStateMenu->Append(wxID_ANY, "State 2");
    simulateMenu->AppendSubMenu(goInToStateMenu, "Go In To &State");

    simulateMenu->AppendSeparator();
    simulateMenu->Append(ID_TICK_ONCE, "Tick &Once\tCtrl+T", "Perform a single tick of the simulation");

    wxMenuItem* ticksEnabledItem = new wxMenuItem(simulateMenu, ID_TICKS_ENABLED, "&Ticks Enabled\tCtrl+K", "", wxITEM_CHECK);
    simulateMenu->Append(ticksEnabledItem);

    wxMenu* tickFrequencyMenu = new wxMenu;
    tickFrequencyMenu->Append(wxID_ANY, "1 Hz");
    tickFrequencyMenu->Append(wxID_ANY, "10 Hz");
    tickFrequencyMenu->Append(wxID_ANY, "100 Hz");
    simulateMenu->AppendSubMenu(tickFrequencyMenu, "Tick &Frequency");

    simulateMenu->AppendSeparator();
    simulateMenu->Append(ID_LOGGING, "&Logging...", "Configure logging options");

    return simulateMenu;
}

wxMenu* CreateWindowMenu()
{
    wxMenu* windowMenu = new wxMenu;
    windowMenu->Append(ID_MINIMIZE, "&Minimize\tCtrl+M", "Minimize the application");
    windowMenu->Append(ID_MAXIMIZE, "&Maximize", "Maximize the application");
    windowMenu->Append(ID_CLOSE, "&Close\tCtrl+W", "Close the current window");
    windowMenu->AppendSeparator();
    windowMenu->Append(ID_COMBINATIONAL_ANALYSIS, "Combinational &Analysis", "Perform combinational analysis");
    windowMenu->Append(ID_PREFERENCES, "&Preferences", "Configure preferences");

    wxMenuItem* untitledItem = new wxMenuItem(windowMenu, ID_WINDOW_UNTITLED, "&Untitled", "", wxITEM_CHECK);
    //untitledItem->Check(true);
    windowMenu->Append(untitledItem);

    return windowMenu;
}

wxMenu* CreateHelpMenu()
{
    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(ID_TUTORIAL, "&Tutorial\tF1", "Open the tutorial");
    helpMenu->Append(ID_USERS_GUIDE, "&User's Guide", "Open the user's guide");
    helpMenu->Append(ID_LIBRARY_REFERENCE, "&Library Reference", "Open the library reference");
    helpMenu->AppendSeparator();
    helpMenu->Append(ID_ABOUT, "&About...\tF2", "Show about dialog");
    return helpMenu;
}