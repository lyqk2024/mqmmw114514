#pragma once
#include <wx/wx.h>
#include <vector>

enum ComponentType {
    COMPONENT_AND,
    COMPONENT_OR,
    COMPONENT_NOT,
    COMPONENT_INPUT,
    COMPONENT_OUTPUT
};

class CircuitComponent {
public:
    CircuitComponent(ComponentType type, wxPoint pos);

    ComponentType GetType() const;
    wxPoint GetPosition() const;
    void SetPosition(wxPoint pos);
    bool IsSelected() const;
    void SetSelected(bool selected);
    wxString GetName() const;
    bool HitTest(wxPoint point) const;
    std::vector<wxPoint> GetConnectionPoints() const;
    int FindNearestConnectionPoint(wxPoint point, int& distance) const;

private:
    ComponentType m_type;
    wxPoint m_pos;
    bool m_selected;
};
