#pragma once
#include <wx/wx.h>

class Wire {
public:
    // 构造函数
    Wire(int startComponent, int startPoint, int endComponent, int endPoint);

    // 访问器方法
    int GetStartComponent() const;
    int GetStartPoint() const;
    int GetEndComponent() const;
    int GetEndPoint() const;
    void SetTempEnd(wxPoint tempEnd);
    wxPoint GetTempEnd() const;
    bool IsConnectedToComponent(int componentIndex) const;

private:
    int m_startComponent;
    int m_startPoint;
    int m_endComponent;
    int m_endPoint;
    wxPoint m_tempEnd;
};