#ifndef		_SEARCHPOPUP_
#define		_SEARCHPOPUP_


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include "wx/popupwin.h"
//#include "wx/spinctrl.h"

#include "comboDescritores.h"


// IDs for the controls and the menu commands
enum
{
    Minimal_Quit = wxID_EXIT,
    Minimal_About = wxID_ABOUT,
    Minimal_TestDialog,
    Minimal_StartSimplePopup,
    Minimal_StartScrolledPopup,
    Minimal_LogWindow,
    Minimal_PopupButton,
    Minimal_PopupSpinctrl
};


//----------------------------------------------------------------------------
// SimpleTransientPopup
//----------------------------------------------------------------------------
class SimpleTransientPopup: public wxPopupWindow //wxPopupTransientWindow	//
{
public:
    SimpleTransientPopup(  wxWindow *parent );
    virtual ~SimpleTransientPopup();

    // wxPopupTransientWindow virtual methods are all overridden to log them
    virtual void Popup(wxWindow *focus = NULL);
//    virtual void OnDismiss();
//    virtual bool ProcessLeftDown(wxMouseEvent& event);
    virtual bool Show( bool show = true );

    wxScrolledWindow* GetChild() { return m_panel; }


	static tComboDescritores 	*m_combo_descritores; 

private:
    wxScrolledWindow *m_panel;
    wxButton *m_buttonInsert, *m_buttonCancel;
private:
    void OnMouse( wxMouseEvent &event );
    void OnSize( wxSizeEvent &event );
    void OnSetFocus( wxFocusEvent &event );
    void OnKillFocus( wxFocusEvent &event );
    void OnButton( wxCommandEvent& event );
    void OnSpinCtrl( wxSpinEvent& event );

private:
    DECLARE_CLASS(SimpleTransientPopup)
    DECLARE_EVENT_TABLE()
};


#endif