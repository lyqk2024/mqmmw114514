#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
    public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

};

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("demo01", wxPoint(100, 100), wxSize(400, 300));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
}

wxIMPLEMENT_APP(MyApp);