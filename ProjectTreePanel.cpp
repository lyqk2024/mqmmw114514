// ProjectTreePanel.cpp
#include "ProjectTreePanel.h"
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/log.h>

BEGIN_EVENT_TABLE(ProjectTreePanel, wxPanel)
EVT_TREE_ITEM_ACTIVATED(wxID_ANY, ProjectTreePanel::OnItemActivated)
END_EVENT_TABLE()

ProjectTreePanel::ProjectTreePanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_NONE)
{
    CreateTreeControl();
    BindEvents();
    InitSampleData();

    // 设置布局
    auto* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_treeCtrl, 1, wxEXPAND | wxALL, 5);
    SetSizer(sizer);
}

void ProjectTreePanel::CreateTreeControl()
{
    m_treeCtrl = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
        wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxBORDER_SUNKEN);
}

void ProjectTreePanel::BindEvents()
{
    // 可绑定更多事件如右键菜单、拖拽等
}

void ProjectTreePanel::InitSampleData()
{
    wxTreeItemId root = m_treeCtrl->AddRoot("Project");
    wxTreeItemId folder = m_treeCtrl->AppendItem(root, "Circuits", -1, -1, new wxTreeItemData());
    m_treeCtrl->AppendItem(folder, "Main Circuit");
    m_treeCtrl->AppendItem(folder, "Subroutine");
    m_treeCtrl->Expand(root);
}

void ProjectTreePanel::OnItemActivated(wxTreeEvent& event)
{
    wxTreeItemId item = event.GetItem();
    if (item.IsOk())
    {
        wxString label = m_treeCtrl->GetItemText(item);
        wxLogMessage("Double-clicked on: %s", label);
        // 这里可以触发打开电路图等操作
    }
}