#ifndef CPLOTTREE_H
#define CPLOTTREE_H

#include "base_include.h"
#include "parse_string_v2/type.h"

class CPlotTree : public wxFrame
{
private:
    int m_delta_x;
    int m_sizeFontX;
    int m_sizeFontY;
    StringTree* m_tree;

    void OnFlickerFreeOff(wxEraseEvent& event);
    void OnPaintEvent(wxPaintEvent& event);
    void OnResize(wxSizeEvent& event);

    // void GetRound(StringTree* tree, wxDC& dc, int delta_x, int delta_y);
    void GetRound(StringTree* tree, wxDC& dc, int delta_y);

    void PlotElement(wxDC& dc);

    DECLARE_EVENT_TABLE()

public:
    CPlotTree();
    ~CPlotTree();

    void ShowTree(StringTree* tree);
};

#endif // CPLOTTREE_H