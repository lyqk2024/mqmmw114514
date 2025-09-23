#pragma once
#include <wx/wx.h>
#include <vector>
#include "CircuitComponent.h"
#include "Wire.h"

class CircuitCanvas : public wxPanel {
public:
    CircuitCanvas(wxWindow* parent);

    void SetSelectedComponentType(ComponentType type);
    void SetWireMode(bool wireMode);
    void AddComponent(wxPoint pos);
    void AddWire(int startComponent, int startPoint, int endComponent, int endPoint);
    void RunSimulation();
    void DeleteSelectedComponent();

private:
    std::vector<CircuitComponent> m_components;
    std::vector<Wire> m_wires;
    ComponentType m_currentComponentType;
    bool m_dragging;
    int m_selectedComponent;
    wxPoint m_dragStart;
    bool m_wireMode;
    bool m_drawingWire;
    int m_startComponent;
    int m_startPoint;

    // 事件处理函数声明
    void OnPaint(wxPaintEvent& event);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnKeyDown(wxKeyEvent& event);

    // 绘图辅助函数声明
    void DrawGrid(wxDC& dc);
    void DrawAllWires(wxDC& dc);
    void DrawComponent(wxDC& dc, const CircuitComponent& comp);
    void DrawAndGate(wxDC& dc, wxPoint pos);
    void DrawOrGate(wxDC& dc, wxPoint pos);
    void DrawNotGate(wxDC& dc, wxPoint pos);
    void DrawPin(wxDC& dc, wxPoint pos, bool isInput);

    DECLARE_EVENT_TABLE()
};