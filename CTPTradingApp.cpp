/***************************************************************
 * Name:      CTPTradingApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Richard (x7536110@outlook.com)
 * Created:   2017-02-20
 * Copyright: Richard ()
 * License:
 **************************************************************/

#include "CTPTradingApp.h"

//(*AppHeaders
#include "CTPTradingMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CTPTradingApp);

bool CTPTradingApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CTPTradingFrame* Frame = new CTPTradingFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
