#ifndef CPLOT_H
#define CPLOT_H

#include "base_include.h"

#include <cfloat>
#include <list>
#include <map>

class TGraph
{
private:
public:
    TGraph(){};
    ~TGraph(){};

    double m_maxX;
    double m_minX;

    double m_maxY;
    double m_minY;

    std::map<double, double> m_xy;

    void SetPoints(const double& x, const double& y)
    {
        m_xy.insert(std::make_pair(x, y));
    }

    void Init()
    {
        m_maxX = -DBL_MAX;
        m_minX = DBL_MAX;
        m_maxY = -DBL_MAX;
        m_minY = DBL_MAX;

        for(auto& p : m_xy) {
            if(p.first > m_maxX)
                m_maxX = p.first;
            if(p.first < m_minX)
                m_minX = p.first;
            if(p.second > m_maxY)
                m_maxY = p.second;
            if(p.second < m_minY)
                m_minY = p.second;
        }
    }
};

class CPlotGraph : public wxPanel
{
private:
    typedef void (CPlotGraph::*iFunc)();

    std::vector<std::pair<bool, iFunc>> m_listFunction;
    std::list<TGraph> m_list;

    wxPoint m_mousePosition;
    wxSize m_screen;

    void DrawGrid(wxDC& dc);
    void DrawAxis(wxDC& dc);
    void DrawGraph(wxDC& dc);
    void HighlightPoint(wxDC& dc);
    void DrowMouseCursor(wxDC& dc);
    void DrowMousePosition(wxDC& dc);

    void PaintBackground(wxDC& dc);

    void OnPaintEvent(wxPaintEvent& event);
    void OnMouseMoved(wxMouseEvent& event);

    void OnChangeSize(wxSizeEvent& event);
    void OnFlickerFreeOff(wxEraseEvent& event);

    // void MouseDown(wxMouseEvent& event);
    // void MouseReleased(wxMouseEvent& event);
    // void MouseWheelMoved(wxMouseEvent& event);
    // void RightClick(wxMouseEvent& event);
    // void MouseLeftWindow(wxMouseEvent& event);
    // void KeyPressed(wxKeyEvent& event);
    // void KeyReleased(wxKeyEvent& event);

    DECLARE_EVENT_TABLE()

public:
    CPlotGraph(wxWindow* parent);
    ~CPlotGraph();

    void SetGraph(TGraph* graph);
};

#endif // CPLOT_H
