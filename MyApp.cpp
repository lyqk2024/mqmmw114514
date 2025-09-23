// MyApp.cpp
#pragma warning(push)
#pragma warning(disable: 6011 26495 26439 28251)
#include <wx/wx.h>
#pragma warning(pop)

#include "MainFrame.h"

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