#ifndef CMAINFRAME_H
#define CMAINFRAME_H

// #include <wx/glcanvas.h>
// #include <wx/sizer.h>

#include <wx/frame.h>

#include "plot/plotgraph.h"
#include "plot/plottree.h"

class CMainFrame : public wxFrame
{
private:
    CPlotTree* m_plotTree;
    CPlotGraph* m_plotGraph;
    wxTextCtrl* m_txtFormula;

    void Plot();
    // void GetRound(StringTree* node);
    void HighlightErrorSymbol(uint8_t begin, uint8_t end, wxColour colour);
    wxString CalculateWXString(const wxString& sA, const wxString& sB, const wxString& sign);

    void OnTxtFormulaKeyDown(wxKeyEvent& event);
    void OnPlotFormulaEnter(wxCommandEvent& event);
    void OnPlotFormulaButton(wxCommandEvent& event);

public:
    CMainFrame();
    ~CMainFrame();
};

#endif // CMAINFRAME_H
