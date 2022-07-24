#include "mainframe.h"

#include <parse_string_v2/parsestring_v2.h>

#include "check/brackets.h"
#include "check/sign.h"
#include "check/validator.h"

CMainFrame::CMainFrame()
    : wxFrame(NULL, NewControlId(), wxT("Graph Manager"))
{
    SetIcon(wxICON(DarthVader));

    m_plotGraph = new CPlotGraph(this);
    m_plotTree = new CPlotTree();
    m_plotTree->Show();

    m_txtFormula = new wxTextCtrl(
        this, NewControlId(), wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER | wxTE_RICH2);

    m_txtFormula->SetValue(wxT("1+8"));

    wxButton* btnPlot = new wxButton(this, NewControlId(), wxT("Plot"));

    wxBoxSizer* main_box = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* h_box = new wxBoxSizer(wxHORIZONTAL);
    h_box->Add(m_txtFormula, 1);
    h_box->Add(btnPlot);

    main_box->Add(h_box, 0, wxEXPAND);
    main_box->Add(m_plotGraph, 1, wxEXPAND);
    SetSizerAndFit(main_box);
    this->SetSize(wxSize(700, 500));

    Bind(wxEVT_TEXT_ENTER, &CMainFrame::OnPlotFormulaEnter, this, m_txtFormula->GetId());
    // Bind(wxEVT_TEXT, &CMainFrame::OnEditTextFormula, this, m_txtFormula->GetId());
    m_txtFormula->Bind(wxEVT_KEY_DOWN, &CMainFrame::OnTxtFormulaKeyDown, this, m_txtFormula->GetId());
    Bind(wxEVT_BUTTON, &CMainFrame::OnPlotFormulaButton, this, btnPlot->GetId());

    TGraph gr;
    // gr.TXYData.insert(std::make_pair(0.0, 4.0));
    // gr.TXYData.insert(std::make_pair(1.0, 3.0));
    // gr.TXYData.insert(std::make_pair(2.0, 2.0));
    // gr.TXYData.insert(std::make_pair(3.0, 1.0));
    // gr.TXYData.insert(std::make_pair(4.0, 3.0));
    // gr.TXYData.insert(std::make_pair(5.0, 0.0));

    gr.SetPoints(0.0, 4.0);
    gr.SetPoints(1.0, 3.0);
    gr.SetPoints(2.0, 2.0);
    gr.SetPoints(3.0, 1.0);
    gr.SetPoints(4.0, 3.0);
    gr.SetPoints(5.0, 0.0);
    gr.Init();

    m_plotGraph->SetGraph(&gr);
}

CMainFrame::~CMainFrame()
{
}

void CMainFrame::OnTxtFormulaKeyDown(wxKeyEvent& event)
{
    HighlightErrorSymbol(0, m_txtFormula->GetLastPosition(), *wxWHITE);
    event.Skip();
}

void CMainFrame::OnPlotFormulaButton(wxCommandEvent& event)
{
    Plot();
}

void CMainFrame::OnPlotFormulaEnter(wxCommandEvent& event)
{
    Plot();
}

void CMainFrame::HighlightErrorSymbol(uint8_t begin, uint8_t end, wxColour colour)
{
    wxTextAttr attr;
    attr.SetBackgroundColour(colour);
    m_txtFormula->SetStyle(begin, end, attr);
}

void CMainFrame::Plot()
{
    int iSizeString = m_txtFormula->GetLastPosition();
    if(iSizeString == 0)
        return;

    TParseResult parseResult;

    bool result = false;
    int number = 0;
    char pString[iSizeString + 1] = { 0 };
    CheckError resVal = SUCCESS;

    // check name graph and replace $

    // check max($), min($), avg($), mdn($), cnt($), sum($) and replace $

    // validator
    result = ValidatorBool(m_txtFormula->GetValue().mb_str(), pString, number);
    if(result == false)
        return HighlightErrorSymbol(number - 1, number, *wxRED);

    // check brackets
    result = BracketsBool(pString, number);
    if(result == false)
        return HighlightErrorSymbol(number - 1, number, *wxRED);

    // check sign and point
    resVal = SignCompactError(pString, number);
    if(resVal != SUCCESS)
        return HighlightErrorSymbol(number - 1, number, *wxRED);

    // check name graph and link pointer x1, x2, x3

    // Начиная отсюда происходит перерасчет формул

    // check max, min, avg, mdn, cnt, sum and calculation and replace in string formula // avg - среднее

    // parse formula
    CParseStringV2 parse;
    // parse.Make(pString, parseResult);
    parse.Make("2*50+(4-(1-2)+(3-4)*(-1))", parseResult);

    m_plotTree->ShowTree(parseResult.stringTree);

    // calculate formula

    // plot
}

wxString CMainFrame::CalculateWXString(const wxString& sA, const wxString& sB, const wxString& sign)
{
    COperations op;
    double dA(0), dB(0);

    sA.ToDouble(&dA);
    sB.ToDouble(&dB);

    double result = op.Calculate(dA, dB, sign.mb_str());
    return wxString::Format(wxT("%.2f"), result);
}

/*void CMainFrame::GetRound(StringTree* node)
{
    if(node != nullptr) {
        GetRound(node->GetRight());
        GetRound(node->GetLeft());
        if(node->m_data == '*' || node->m_data == '/' || node->m_data == '-' || node->m_data == '+')
            node->m_data = CalculateWXString(node->GetRight()->m_data, node->GetLeft()->m_data, node->m_data);
    }
}*/
