/***************************************************************
 * Name:      CTPTradingMain.h
 * Purpose:   Defines Application Frame
 * Author:    Richard (x7536110@outlook.com)
 * Created:   2017-02-20
 * Copyright: Richard ()
 * License:
 **************************************************************/

#ifndef CTPTRADINGMAIN_H
#define CTPTRADINGMAIN_H

//(*Headers(CTPTradingFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class CTPTradingFrame: public wxFrame
{
    public:

        CTPTradingFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CTPTradingFrame();

    private:

        //(*Handlers(CTPTradingFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(CTPTradingFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(CTPTradingFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CTPTRADINGMAIN_H
