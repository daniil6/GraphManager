#include "mainframe.h"

class wxMainApp : public wxApp
{
private:
    virtual bool OnInit();
};

IMPLEMENT_APP(wxMainApp)

bool wxMainApp::OnInit()
{
    CMainFrame* mainframe = new CMainFrame;
    mainframe->Show();
    return true;
}