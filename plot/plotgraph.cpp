#include "plotgraph.h"

#include <thread>

#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE(CPlotGraph, wxPanel)
EVT_MOTION(CPlotGraph::OnMouseMoved)
EVT_PAINT(CPlotGraph::OnPaintEvent)
EVT_SIZE(CPlotGraph::OnChangeSize)
EVT_ERASE_BACKGROUND(CPlotGraph::OnFlickerFreeOff)

// EVT_LEFT_DOWN(CPlotGraph::MouseDown)
// EVT_LEFT_UP(CPlotGraph::MouseReleased)
// EVT_RIGHT_DOWN(CPlotGraph::RightClick)
// EVT_LEAVE_WINDOW(CPlotGraph::MouseLeftWindow)
// EVT_KEY_DOWN(CPlotGraph::KeyPressed)
// EVT_KEY_UP(CPlotGraph::KeyReleased)
// EVT_MOUSEWHEEL(CPlotGraph::MouseWheelMoved)

END_EVENT_TABLE()

CPlotGraph::CPlotGraph(wxWindow* parent)
    : wxPanel(parent, NewControlId())
{
    this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));
    this->SetBackgroundColour(wxColor(0xFF, 0xFF, 0xFF));

    m_screen = this->GetSize();

    // m_listFunction.push_back(std::make_pair(false, &HighlightPoint));

    // this->SetDoubleBuffered(true);
}

CPlotGraph::~CPlotGraph()
{
}

void CPlotGraph::OnFlickerFreeOff(wxEraseEvent& event)
{
}

void CPlotGraph::OnChangeSize(wxSizeEvent& event)
{
    m_screen = this->GetSize();
    Refresh();
}

void CPlotGraph::OnMouseMoved(wxMouseEvent& event)
{
    m_mousePosition = event.GetPosition();

    Refresh();

    // RefreshRect(wxRect(wxPoint(m_mousePosition.x - 100, 0), wxSize(200, m_screen.y)));
    // RefreshRect(wxRect(wxPoint(0, m_mousePosition.y - 100), wxSize(m_screen.x, 200)));
    std::cout << "mouese x=" << m_mousePosition.x << " y=" << m_mousePosition.y << std::endl;
}

void CPlotGraph::OnPaintEvent(wxPaintEvent& event)
{
    // std::this_thread::sleep_for(std::chrono::milliseconds(50));

    wxBufferedPaintDC dc(this);
    dc.Clear();

    DrowMouseCursor(dc);
    DrowMousePosition(dc);

    DrawAxis(dc);
    DrawGraph(dc);
    HighlightPoint(dc);
}

void CPlotGraph::DrowMousePosition(wxDC& dc)
{
    wxString temp = wxString::Format(wxT("%d, %d"), m_mousePosition.x, m_mousePosition.y);
    dc.DrawText(temp, m_mousePosition.x + 10, m_mousePosition.y - 10);
}

void CPlotGraph::DrowMouseCursor(wxDC& dc)
{
    dc.SetPen(wxPen(wxColour(0x8D, 0x8D, 0x8D), 1));
    dc.DrawLine(m_mousePosition.x, 0, m_mousePosition.x, m_screen.GetY());
    dc.DrawLine(0, m_mousePosition.y, m_screen.GetX(), m_mousePosition.y);
}

void CPlotGraph::DrawAxis(wxDC& dc)
{
    dc.SetPen(wxPen(wxColour(0x69, 0x69, 0x69), 1, wxPENSTYLE_SHORT_DASH));
    dc.DrawLine(m_screen.GetX() / 2, 0, m_screen.GetX() / 2, m_screen.GetY());
    dc.DrawLine(0, m_screen.GetY() / 2, m_screen.GetX(), m_screen.GetY() / 2);
}

void CPlotGraph::DrawGraph(wxDC& dc)
{
    for(auto& p : m_list) {
        auto itr = p.m_xy.begin();
        while(1) {
            double x1 = m_screen.GetX() * itr->first / (p.m_maxX - p.m_minX);
            double y1 = m_screen.GetY() / (p.m_maxY - p.m_minY) * itr->second;

            dc.DrawCircle(x1, y1, wxCoord(2));

            itr++;
            double x2 = m_screen.GetX() * itr->first / (p.m_maxX - p.m_minX);
            double y2 = m_screen.GetY() / (p.m_maxY - p.m_minY) * itr->second;

            if(itr != p.m_xy.end())
                dc.DrawLine(x1, y1, x2, y2);
            else
                return;
        }
    }
}

void CPlotGraph::HighlightPoint(wxDC& dc)
{
    for(auto& l : m_list) {
        double localMousePositionX = m_mousePosition.x * (l.m_maxX - l.m_minX) / m_screen.x;
        auto itr = l.m_xy.lower_bound(localMousePositionX);
        if(itr != l.m_xy.end()) {
            double x = m_screen.GetX() * itr->first / (l.m_maxX - l.m_minX);
            double y = m_screen.GetY() / (l.m_maxY - l.m_minY) * itr->second;
            if(m_mousePosition.y > (y - 10) && m_mousePosition.y < (y + 10)) {
                if(m_mousePosition.y != (int)y && m_mousePosition.x != (int)x) {
                    wxMouseEvent event;
                    event.SetPosition(wxPoint(x, y));
                    this->OnMouseMoved(event);
                }

                dc.DrawCircle(x, y, wxCoord(15));
            }
        }
    }
}

void CPlotGraph::DrawGrid(wxDC& dc)
{
}

void CPlotGraph::SetGraph(TGraph* graph)
{
    if(graph != nullptr)
        m_list.push_back(*graph);
}

/*void CPlotGraph::MouseDown(wxMouseEvent& event)
{
}

void CPlotGraph::MouseWheelMoved(wxMouseEvent& event)
{
}

void CPlotGraph::MouseReleased(wxMouseEvent& event)
{
}

void CPlotGraph::RightClick(wxMouseEvent& event)
{
}

void CPlotGraph::MouseLeftWindow(wxMouseEvent& event)
{
}

void CPlotGraph::KeyPressed(wxKeyEvent& event)
{
}

void CPlotGraph::KeyReleased(wxKeyEvent& event)
{
}*/