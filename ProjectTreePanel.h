// ProjectTreePanel.h
#pragma once

#include <wx/treectrl.h>
#include <wx/panel.h>

class ProjectTreePanel : public wxPanel
{
public:
    explicit ProjectTreePanel(wxWindow* parent);

    wxTreeCtrl* GetTreeCtrl() { return m_treeCtrl; }

private:
    void CreateTreeControl();
    void BindEvents();
    void InitSampleData();

    wxTreeCtrl* m_treeCtrl = nullptr;

    // 事件处理函数（可根据需要扩展）
    void OnItemActivated(wxTreeEvent& event);

    DECLARE_EVENT_TABLE()
};