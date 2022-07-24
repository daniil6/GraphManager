#include "plottree.h"

#include <wx/dcbuffer.h>

BEGIN_EVENT_TABLE(CPlotTree, wxPanel)
EVT_PAINT(CPlotTree::OnPaintEvent)
EVT_SIZE(CPlotTree::OnResize)
EVT_ERASE_BACKGROUND(CPlotTree::OnFlickerFreeOff)
END_EVENT_TABLE()

// расстояния между звеньями
#define HEIGHT_BETWEEN_NODE 50
#define LENGHT_BETWEEN_NODE 70

// пареметры эллипса
#define ELLIPSE_RADIUS_X 55
#define ELLIPSE_RADIUS_Y 25

CPlotTree::CPlotTree()
    : wxFrame(NULL, NewControlId(), wxT("Tree View"))
{
    m_tree = nullptr;
    this->SetBackgroundColour(wxColor(150, 85, 195));
    this->SetSize(500, 500);
}

CPlotTree::~CPlotTree()
{
}

void CPlotTree::OnResize(wxSizeEvent& event)
{
    m_delta_x = 0;
    Refresh();
}

void CPlotTree::OnFlickerFreeOff(wxEraseEvent& event)
{
}

void CPlotTree::OnPaintEvent(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);
    dc.Clear();

    wxFont font = dc.GetFont();
    font.SetPointSize(font.GetPointSize() + 10);
    dc.SetFont(font);

    m_sizeFontY = dc.GetFont().GetPointSize();
    m_sizeFontX = m_sizeFontY * 72 / 100 / 2;
    m_sizeFontY /= 2 + 1;

    GetRound(m_tree, dc, 0);
}

void CPlotTree::PlotElement(wxDC& dc)
{
    // dc.DrawEllipse(wxPoint(node->m_xy.x, node->m_xy.y), wxSize(radiusX * 2, radiusY * 2));
    //
    // dc.DrawText(wxString(node->m_pSurname.first),
    // wxPoint(node->m_xy.x + radiusX - node->m_pSurname.second, node->m_xy.y + 1 * space));
}

// int CPlotTree::GetRound(StringTree* tree, wxDC& dc, int delta_x, int delta_y)
void CPlotTree::GetRound(StringTree* tree, wxDC& dc, int delta_y)
{
    if(tree != nullptr) {

        // GetRound(tree->GetLeft(), dc, delta_x - LENGHT_BETWEEN_NODE, delta_y + HEIGHT_BETWEEN_NODE);
        // GetRound(tree->GetRight(), dc, delta_x + LENGHT_BETWEEN_NODE, delta_y + HEIGHT_BETWEEN_NODE);
        GetRound(tree->GetLeft(), dc, delta_y + HEIGHT_BETWEEN_NODE);

        dc.DrawEllipse(wxPoint(m_delta_x, delta_y), wxSize(ELLIPSE_RADIUS_X * 2, ELLIPSE_RADIUS_Y * 2));
        dc.DrawText(tree->GetData(), m_delta_x + ELLIPSE_RADIUS_X - m_sizeFontX * tree->GetData().size(),
            delta_y + m_sizeFontY);

        dc.SetPen(wxPen(wxColor(255, 0, 0)));
        dc.DrawLine(m_delta_x, delta_y, m_delta_x + ELLIPSE_RADIUS_X * 2, delta_y + ELLIPSE_RADIUS_Y * 2);
        dc.DrawLine(m_delta_x, delta_y + ELLIPSE_RADIUS_Y * 2, m_delta_x + ELLIPSE_RADIUS_X * 2, delta_y);
        dc.SetPen(wxPen(wxColor(0, 0, 0)));

        m_delta_x += LENGHT_BETWEEN_NODE;

        GetRound(tree->GetRight(), dc, delta_y + HEIGHT_BETWEEN_NODE);
    }
}

void CPlotTree::ShowTree(StringTree* tree)
{
    m_delta_x = 0;
    m_tree = tree;
    Refresh();
}