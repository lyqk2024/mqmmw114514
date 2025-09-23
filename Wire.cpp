#include "Wire.h"

Wire::Wire(int startComponent, int startPoint, int endComponent, int endPoint)
    : m_startComponent(startComponent), m_startPoint(startPoint),
    m_endComponent(endComponent), m_endPoint(endPoint), m_tempEnd(wxPoint(-1, -1)) {
}

int Wire::GetStartComponent() const { return m_startComponent; }
int Wire::GetStartPoint() const { return m_startPoint; }
int Wire::GetEndComponent() const { return m_endComponent; }
int Wire::GetEndPoint() const { return m_endPoint; }
void Wire::SetTempEnd(wxPoint tempEnd) { m_tempEnd = tempEnd; }
wxPoint Wire::GetTempEnd() const { return m_tempEnd; }
bool Wire::IsConnectedToComponent(int componentIndex) const {
    return m_startComponent == componentIndex || m_endComponent == componentIndex;
}