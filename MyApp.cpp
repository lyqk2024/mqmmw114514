// MyApp.cpp
#include "MainFrame.h"
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MainFrame* frame = new MainFrame("Logisim: main of Untitled");
    frame->Show(true);
    return true;
}