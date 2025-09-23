#include "CircuitCanvas.h"
#include <wx/dcclient.h>    // 包含wxAutoBufferedPaintDC定义
#include <wx/graphics.h>    // 图形绘制相关定义
#include <cmath>       
#include <wx/dcbuffer.h>
BEGIN_EVENT_TABLE(CircuitCanvas, wxPanel)
EVT_PAINT(CircuitCanvas::OnPaint)
EVT_LEFT_DOWN(CircuitCanvas::OnMouseDown)
EVT_LEFT_UP(CircuitCanvas::OnMouseUp)
EVT_MOTION(CircuitCanvas::OnMouseMove)
EVT_KEY_DOWN(CircuitCanvas::OnKeyDown)
END_EVENT_TABLE()

CircuitCanvas::CircuitCanvas(wxWindow* parent)
    : wxPanel(parent),
    m_dragging(false),
    m_selectedComponent(-1),
    m_wireMode(false),
    m_drawingWire(false),
    m_startComponent(-1),
    m_startPoint(-1),
    m_currentComponentType(COMPONENT_AND) {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    SetBackgroundColour(*wxWHITE); // 明确设置为白色背景
}

void CircuitCanvas::SetSelectedComponentType(ComponentType type) {
    m_currentComponentType = type;
    m_wireMode = false;
}

void CircuitCanvas::SetWireMode(bool wireMode) {
    m_wireMode = wireMode;
}

void CircuitCanvas::AddComponent(wxPoint pos) {
    m_components.emplace_back(m_currentComponentType, pos);
    Refresh();
}

void CircuitCanvas::AddWire(int startComponent, int startPoint, int endComponent, int endPoint) {
    m_wires.emplace_back(startComponent, startPoint, endComponent, endPoint);
    Refresh();
}

void CircuitCanvas::RunSimulation() {
    Refresh();
}

void CircuitCanvas::DeleteSelectedComponent() {
    if (m_selectedComponent != -1 && m_selectedComponent < (int)m_components.size()) {
        for (auto it = m_wires.begin(); it != m_wires.end(); ) {
            if (it->IsConnectedToComponent(m_selectedComponent)) {
                it = m_wires.erase(it);
            }
            else {
                ++it;
            }
        }
        m_components.erase(m_components.begin() + m_selectedComponent);
        m_selectedComponent = -1;
        Refresh();
    }
}

void CircuitCanvas::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    DrawGrid(dc);
    DrawAllWires(dc);

    for (const auto& comp : m_components) {
        DrawComponent(dc, comp);
    }

    if (m_drawingWire && m_startComponent != -1 && m_startPoint != -1) {
        wxPoint start = m_components[m_startComponent].GetConnectionPoints()[m_startPoint];
        dc.SetPen(wxPen(*wxBLUE, 2));
        dc.DrawLine(start, m_dragStart);
    }
}

void CircuitCanvas::DrawGrid(wxDC& dc) {
    dc.SetPen(wxPen(wxColour(220, 220, 220), 1));
    wxSize size = GetClientSize();

    for (int y = 0; y < size.y; y += 20) {
        dc.DrawLine(0, y, size.x, y);
    }
    for (int x = 0; x < size.x; x += 20) {
        dc.DrawLine(x, 0, x, size.y);
    }
}

void CircuitCanvas::DrawAllWires(wxDC& dc) {
    dc.SetPen(wxPen(*wxBLUE, 2));

    for (const auto& wire : m_wires) {
        if (wire.GetEndComponent() != -1 && wire.GetEndComponent() < (int)m_components.size()) {
            wxPoint start = m_components[wire.GetStartComponent()].GetConnectionPoints()[wire.GetStartPoint()];
            wxPoint end = m_components[wire.GetEndComponent()].GetConnectionPoints()[wire.GetEndPoint()];
            dc.DrawLine(start, end);
        }
        else if (wire.GetTempEnd().x != -1) {
            wxPoint start = m_components[wire.GetStartComponent()].GetConnectionPoints()[wire.GetStartPoint()];
            dc.DrawLine(start, wire.GetTempEnd());
        }
    }
}

void CircuitCanvas::DrawComponent(wxDC& dc, const CircuitComponent& comp) {
    wxPoint pos = comp.GetPosition();
    wxFont font = dc.GetFont();
    font.SetPointSize(5);
    dc.SetFont(font);

    dc.SetBrush(comp.IsSelected() ? *wxLIGHT_GREY : *wxWHITE);
    dc.SetPen(wxPen(*wxBLACK, 2));

    switch (comp.GetType()) {
    case COMPONENT_AND: DrawAndGate(dc, pos); break;
    case COMPONENT_OR: DrawOrGate(dc, pos); break;
    case COMPONENT_NOT: DrawNotGate(dc, pos); break;
    case COMPONENT_INPUT:
    case COMPONENT_OUTPUT: DrawPin(dc, pos, comp.GetType() == COMPONENT_INPUT); break;
    }

    wxString name = comp.GetName();
    wxSize textSize = dc.GetTextExtent(name);
    if (comp.GetType() == COMPONENT_NOT || comp.GetType() == COMPONENT_OUTPUT) {
        dc.DrawText(name, pos.x - textSize.x / 2 - 5, pos.y - textSize.y / 2);
    }
    else {
        dc.DrawText(name, pos.x - textSize.x, pos.y - textSize.y / 2);
    }

    if (comp.IsSelected()) {
        dc.SetPen(wxPen(*wxGREEN, 1));
        dc.SetBrush(*wxGREEN_BRUSH);
        for (const auto& p : comp.GetConnectionPoints()) {
            dc.DrawCircle(p, 3);
        }
    }
}

void CircuitCanvas::DrawAndGate(wxDC& dc, wxPoint pos) {
    wxPoint points[] = {
        pos + wxPoint(-20, -15),
        pos + wxPoint(20, 0),
        pos + wxPoint(-20, 15)
    };
    dc.DrawPolygon(3, points);
}

void CircuitCanvas::DrawOrGate(wxDC& dc, wxPoint pos) {
    wxPoint points[] = {
        pos + wxPoint(-15, -15),
        pos + wxPoint(20, 0),
        pos + wxPoint(-15, 15)
    };
    dc.DrawPolygon(3, points);
}

void CircuitCanvas::DrawNotGate(wxDC& dc, wxPoint pos) {
    wxPoint points[] = {
        pos + wxPoint(-15, -15),
        pos + wxPoint(15, 0),
        pos + wxPoint(-15, 15)
    };
    dc.DrawPolygon(3, points);
    dc.DrawCircle(pos + wxPoint(18, 0), 5);
}

void CircuitCanvas::DrawPin(wxDC& dc, wxPoint pos, bool isInput) {
    dc.DrawRectangle(pos.x - 15, pos.y - 15, 30, 30);
}

void CircuitCanvas::OnMouseDown(wxMouseEvent& event) {
    wxPoint pos = event.GetPosition();
    int hitIndex = -1;

    for (int i = m_components.size() - 1; i >= 0; i--) {
        if (m_components[i].HitTest(pos)) {
            hitIndex = i;
            break;
        }
    }

    if (m_wireMode) {
        if (hitIndex != -1) {
            int distance;
            int pointIndex = m_components[hitIndex].FindNearestConnectionPoint(pos, distance);
            if (pointIndex != -1 && distance < 40) {
                if (!m_drawingWire) {
                    m_drawingWire = true;
                    m_startComponent = hitIndex;
                    m_startPoint = pointIndex;
                    m_dragStart = pos;
                }
                else {
                    if (hitIndex != m_startComponent) {
                        AddWire(m_startComponent, m_startPoint, hitIndex, pointIndex);
                    }
                    m_drawingWire = false;
                    m_startComponent = -1;
                    m_startPoint = -1;
                }
                Refresh();
            }
        }
        else if (m_drawingWire) {
            m_drawingWire = false;
            m_startComponent = -1;
            m_startPoint = -1;
            Refresh();
        }
    }
    else if (hitIndex != -1) {
        m_selectedComponent = hitIndex;
        m_dragging = true;
        m_dragStart = pos;

        for (size_t i = 0; i < m_components.size(); i++) {
            m_components[i].SetSelected(i == hitIndex);
        }
        Refresh();
    }
    else {
        AddComponent(pos);
    }
}

void CircuitCanvas::OnMouseUp(wxMouseEvent& event) {
    m_dragging = false;
}

void CircuitCanvas::OnMouseMove(wxMouseEvent& event) {
    if (m_drawingWire) {
        m_dragStart = event.GetPosition();
        Refresh();
    }
    else if (m_dragging && m_selectedComponent != -1) {
        wxPoint delta = event.GetPosition() - m_dragStart;
        wxPoint newPos = m_components[m_selectedComponent].GetPosition() + delta;
        m_components[m_selectedComponent].SetPosition(newPos);
        m_dragStart = event.GetPosition();
        Refresh();
    }
}

void CircuitCanvas::OnKeyDown(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_DELETE) {
        DeleteSelectedComponent();
    }
    else {
        event.Skip();
    }
}