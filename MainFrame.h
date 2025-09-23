// MainFrame.h
#pragma once

#include <wx/frame.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>
#include <wx/panel.h>
#include <wx/menu.h>

// 先包含自定义头文件，确保ID和函数声明可用
#include "MenuUtils.h"
#include "CircuitCanvas.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void CreateControls();
    void CreateMenu();
    void CreateToolbar();
    void BindEvents();

    // 事件处理函数
    void OnExit(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnResetSimulation(wxCommandEvent& event);
    void OnStepSimulation(wxCommandEvent& event);
    void OnTickOnce(wxCommandEvent& event);
    void OnMinimize(wxCommandEvent& event);
    void OnMaximize(wxCommandEvent& event);
    void OnCloseWindow(wxCommandEvent& event);
    void OnTutorial(wxCommandEvent& event);
    void OnUsersGuide(wxCommandEvent& event);
    void OnLibraryReference(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    class WorkAreaPanel : public wxPanel
    {
    public:
        WorkAreaPanel(wxWindow* parent);
    private:
        void OnPaint(wxPaintEvent& event);
        DECLARE_EVENT_TABLE()
    };
    // ... 现有成员 ...
    CircuitCanvas* m_circuitCanvas = nullptr;
    ComponentType m_selectedComponentType;
    bool m_wireMode;
    wxSplitterWindow* m_splitter = nullptr;
    wxTreeCtrl* m_treeCtrl = nullptr;

    DECLARE_EVENT_TABLE()
};