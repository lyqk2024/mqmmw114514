#include "MainFrame.h"
#include "ProjectTreePanel.h"
#include <wx/artprov.h>
#include <wx/dcbuffer.h>
#include <wx/aboutdlg.h>
#include "MenuUtils.h"
#include <wx/accel.h>
#include <wx/gdicmn.h>
#include <wx/dcgraph.h>

BEGIN_EVENT_TABLE(MainFrame::WorkAreaPanel, wxPanel)
EVT_PAINT(MainFrame::WorkAreaPanel::OnPaint)
END_EVENT_TABLE()

MainFrame::WorkAreaPanel::WorkAreaPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
}

void MainFrame::WorkAreaPanel::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    dc.SetBackground(*wxWHITE_BRUSH);
    dc.Clear();

    const int dotSpacing = 10; // 调整这个值可以改变点之间的间距

    wxSize size = GetClientSize();

    // 使用 wxGraphicsContext 支持透明度和更精细的控制
    std::unique_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));

    if (gc) {
        // 创建 wxPen 对象并设置画笔颜色为黑色，透明度为64（半透明）
        wxPen wxPenObj(wxColour(0, 0, 0, 64), 1);
        wxGraphicsPen pen = gc->CreatePen(wxPenObj);
        gc->SetPen(pen);

        for (int x = 0; x <= size.GetWidth(); x += dotSpacing) {
            for (int y = 0; y <= size.GetHeight(); y += dotSpacing) {
                // 绘制小圆点
                gc->DrawEllipse(x - 0.5, y - 0.5, 1, 1); // 小圆点的大小可以通过调整椭圆的尺寸来改变
            }
        }
    }
    else {
        // 如果不支持 wxGraphicsContext，则回退到普通 DC
        dc.SetPen(wxPen(wxColour(128, 128, 128), 1)); // 灰色点
        for (int x = 0; x <= size.GetWidth(); x += dotSpacing) {
            for (int y = 0; y <= size.GetHeight(); y += dotSpacing) {
                dc.DrawPoint(x, y);
            }
        }
    }
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
// 事件表可以留空，因为我们使用 Bind() 方式
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 700))
{
    CreateControls();
    CreateMenu();
    CreateToolbar();
    BindEvents();
}

void MainFrame::CreateControls()
{
    m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxSP_LIVE_UPDATE | wxSP_3D);

    // 创建左侧容器
    wxPanel* leftContainerPanel = new wxPanel(m_splitter);
    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);

    // 添加工具栏（保留原逻辑）
    wxToolBar* firstRowToolbar = new wxToolBar(leftContainerPanel, wxID_ANY);
    firstRowToolbar->SetToolBitmapSize(wxSize(24, 24));
    firstRowToolbar->AddTool(wxID_ANY, "Pointer", wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_TOOLBAR));
    firstRowToolbar->AddTool(wxID_ANY, "Text", wxArtProvider::GetBitmap(wxART_EDIT, wxART_TOOLBAR));
    firstRowToolbar->AddSeparator();
    firstRowToolbar->AddTool(wxID_ANY, "Play", wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_TOOLBAR));
    firstRowToolbar->Realize();
    leftSizer->Add(firstRowToolbar, 0, wxEXPAND | wxALL, 5);

    wxToolBar* secondRowToolbar = new wxToolBar(leftContainerPanel, wxID_ANY);
    secondRowToolbar->SetToolBitmapSize(wxSize(24, 24));
    secondRowToolbar->AddTool(wxID_ANY, "+", wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR));
    secondRowToolbar->AddTool(wxID_ANY, "×", wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR));
    secondRowToolbar->Realize();
    leftSizer->Add(secondRowToolbar, 0, wxEXPAND | wxALL, 5);

    // 👉 使用我们封装好的项目树面板
    auto* projectTreePanel = new ProjectTreePanel(leftContainerPanel);
    leftSizer->Add(projectTreePanel, 1, wxEXPAND | wxALL, 5);

    leftContainerPanel->SetSizer(leftSizer);

    // 右侧工作区
    auto* workArea = new WorkAreaPanel(m_splitter);

    // 分割窗口
    m_splitter->SplitVertically(leftContainerPanel, workArea, 200);
    m_splitter->SetMinimumPaneSize(50);

    // 主布局
    SetSizerAndFit(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(m_splitter, 1, wxEXPAND);

    SetSize(1200, 800);
    Center();
}

void MainFrame::CreateMenu()
{
    wxMenuBar* menuBar = new wxMenuBar;
    AddMenuToBar(menuBar, CreateFileMenu(), "&File");
    AddMenuToBar(menuBar, CreateEditMenu(), "&Edit");
    AddMenuToBar(menuBar, CreateProjectMenu(), "&Project");
    AddMenuToBar(menuBar, CreateSimulateMenu(), "&Simulate");
    AddMenuToBar(menuBar, CreateWindowMenu(), "&Window");
    AddMenuToBar(menuBar, CreateHelpMenu(), "&Help");
    SetMenuBar(menuBar);
}

void MainFrame::CreateToolbar()
{
    wxToolBar* toolbar = CreateToolBar(wxTB_FLAT | wxTB_NODIVIDER);
    toolbar->SetToolBitmapSize(wxSize(24, 24));

    toolbar->AddTool(wxID_ANY, "Pointer", wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_TOOLBAR));
    toolbar->AddTool(wxID_ANY, "Text", wxArtProvider::GetBitmap(wxART_EDIT, wxART_TOOLBAR));
    toolbar->AddSeparator();
    toolbar->AddTool(wxID_ANY, "Play", wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_TOOLBAR));
    toolbar->AddTool(wxID_ANY, "Pause", wxArtProvider::GetBitmap(wxART_TIP, wxART_TOOLBAR));
    toolbar->AddTool(wxID_ANY, "Stop", wxArtProvider::GetBitmap(wxART_ERROR, wxART_TOOLBAR));
    toolbar->AddSeparator();
    toolbar->AddTool(wxID_ANY, "Step Forward", wxArtProvider::GetBitmap(wxART_GO_UP, wxART_TOOLBAR));
    toolbar->AddTool(wxID_ANY, "Step Back", wxArtProvider::GetBitmap(wxART_GO_DOWN, wxART_TOOLBAR));

    toolbar->Realize();
}

void MainFrame::BindEvents()
{
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnNew, this, wxID_NEW);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnResetSimulation, this, ID_RESET_SIMULATION);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnStepSimulation, this, ID_STEP_SIMULATION);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnTickOnce, this, ID_TICK_ONCE);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnMinimize, this, ID_MINIMIZE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnMaximize, this, ID_MAXIMIZE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnCloseWindow, this, ID_CLOSE);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnTutorial, this, ID_TUTORIAL);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnUsersGuide, this, ID_USERS_GUIDE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnLibraryReference, this, ID_LIBRARY_REFERENCE);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, ID_ABOUT);
}

// 事件处理函数（空实现，可后续填充）
void MainFrame::OnExit(wxCommandEvent& event) { Close(true); }
void MainFrame::OnNew(wxCommandEvent& event) {}
void MainFrame::OnOpen(wxCommandEvent& event) {}
void MainFrame::OnSave(wxCommandEvent& event) {}
void MainFrame::OnResetSimulation(wxCommandEvent& event) {}
void MainFrame::OnStepSimulation(wxCommandEvent& event) {}
void MainFrame::OnTickOnce(wxCommandEvent& event) {}
void MainFrame::OnMinimize(wxCommandEvent& event) { Iconize(true); }
void MainFrame::OnMaximize(wxCommandEvent& event) { Maximize(); }
void MainFrame::OnCloseWindow(wxCommandEvent& event) { Close(true); }
void MainFrame::OnTutorial(wxCommandEvent& event) {}
void MainFrame::OnUsersGuide(wxCommandEvent& event) {}
void MainFrame::OnLibraryReference(wxCommandEvent& event) {}
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("Logisim-like App\nVersion 1.0\n© 2025", "About", wxOK | wxICON_INFORMATION);
}
