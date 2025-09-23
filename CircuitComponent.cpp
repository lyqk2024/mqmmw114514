#include "CircuitComponent.h"

CircuitComponent::CircuitComponent(ComponentType type, wxPoint pos)
    : m_type(type), m_pos(pos), m_selected(false) {
}

ComponentType CircuitComponent::GetType() const { return m_type; }
wxPoint CircuitComponent::GetPosition() const { return m_pos; }
void CircuitComponent::SetPosition(wxPoint pos) { m_pos = pos; }
bool CircuitComponent::IsSelected() const { return m_selected; }
void CircuitComponent::SetSelected(bool selected) { m_selected = selected; }

wxString CircuitComponent::GetName() const {
    switch (m_type) {
    case COMPONENT_AND: return "AND";
    case COMPONENT_OR: return "OR";
    case COMPONENT_NOT: return "NOT";
    case COMPONENT_INPUT: return "IN";
    case COMPONENT_OUTPUT: return "OUT";
    default: return "?";
    }
}

bool CircuitComponent::HitTest(wxPoint point) const {
    return wxRect(m_pos.x - 20, m_pos.y - 15, 40, 30).Contains(point);
}

std::vector<wxPoint> CircuitComponent::GetConnectionPoints() const {
    std::vector<wxPoint> points;

    switch (m_type) {
    case COMPONENT_AND:
    case COMPONENT_OR:
        points.push_back(m_pos + wxPoint(-20, -8));
        points.push_back(m_pos + wxPoint(-20, 8));
        points.push_back(m_pos + wxPoint(20, 0));
        break;
    case COMPONENT_NOT:
        points.push_back(m_pos + wxPoint(-15, 0));
        points.push_back(m_pos + wxPoint(23, 0));
        break;
    case COMPONENT_INPUT:
        points.push_back(m_pos + wxPoint(15, 0));
        break;
    case COMPONENT_OUTPUT:
        points.push_back(m_pos + wxPoint(-15, 0));
        break;
    }
    return points;
}

int CircuitComponent::FindNearestConnectionPoint(wxPoint point, int& distance) const {
    std::vector<wxPoint> points = GetConnectionPoints();
    distance = 1000000;
    int nearestIndex = -1;

    for (size_t i = 0; i < points.size(); ++i) {
        int dx = point.x - points[i].x;
        int dy = point.y - points[i].y;
        int dist = dx * dx + dy * dy;

        if (dist < distance) {
            distance = dist;
            nearestIndex = i;
        }
    }
    return nearestIndex;
}