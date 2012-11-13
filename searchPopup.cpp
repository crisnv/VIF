#include	"searchPopup.h"


#include "navegadorFGV.h"

//----------------------------------------------------------------------------
// SimpleTransientPopup
//----------------------------------------------------------------------------
IMPLEMENT_CLASS(SimpleTransientPopup,wxPopupWindow)

BEGIN_EVENT_TABLE(SimpleTransientPopup,wxPopupWindow)
//	EVT_KEY_DOWN    
//	EVT_MOUSE_EVENTS( SimpleTransientPopup::OnMouse )
	EVT_SIZE( SimpleTransientPopup::OnSize )
    EVT_SET_FOCUS( SimpleTransientPopup::OnSetFocus )
//    EVT_KILL_FOCUS( SimpleTransientPopup::OnKillFocus )
    EVT_BUTTON( Minimal_PopupButton, SimpleTransientPopup::OnButton )

END_EVENT_TABLE()

tComboDescritores 	*SimpleTransientPopup::m_combo_descritores = NULL; 

SimpleTransientPopup::SimpleTransientPopup(  wxWindow *parent )
                     :wxPopupWindow( parent, wxBORDER_SUNKEN )
	/*
	wxBORDER_NONE   = 0x00200000,
    wxBORDER_STATIC = 0x01000000,
    wxBORDER_SIMPLE = 0x02000000,
    wxBORDER_RAISED = 0x04000000,
    wxBORDER_SUNKEN = 0x08000000,
    wxBORDER_DOUBLE = 0x10000000, /* deprecated *	/
    wxBORDER_THEME  = wxBORDER_DOUBLE,
	*/
{
    m_panel = new wxScrolledWindow( this, wxID_ANY );
    m_panel->SetBackgroundColour( *wxLIGHT_GREY );

    // Keep this code to verify if mouse events work, they're required if
    // you're making a control like a combobox where the items are highlighted
    // under the cursor, the m_panel is set focus in the Popup() function
   /* m_panel->Connect(wxEVT_MOTION,
                     wxMouseEventHandler(SimpleTransientPopup::OnMouse),
                     NULL, this);
					 */
    wxStaticText *text = new wxStaticText( m_panel, wxID_ANY,  wxT("Filtrar por:\n") );

    m_buttonInsert = new wxButton(m_panel, Minimal_PopupButton, wxT("Inserir"));//wxOK
	m_buttonCancel = new wxButton(m_panel, Minimal_PopupButton, wxT("Fechar"));//wxOK

		
	
	wxArrayString choices; 
	((FacesMainFrame* )parent)->GetDescritores(choices); 


	m_combo_descritores = new tComboDescritores(m_panel,wxID_ANY,wxEmptyString,
                                   wxPoint(0,112), wxSize(160,24), choices, wxCB_SORT|wxCB_READONLY);


    wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
    topSizer->Add( text, 0, wxSHRINK, 5 );
    topSizer->Add( m_combo_descritores, 0, wxALL, 5 );
	wxBoxSizer *topHSizer = new wxBoxSizer( wxHORIZONTAL);
	topHSizer->Add( m_buttonInsert, 0, wxALL, 5 );
	topHSizer->Add( m_buttonCancel, 0, wxALL, 5 );

	topSizer->Add( topHSizer, 0, wxALL, 5 );


    m_panel->SetSizer( topSizer );
    topSizer->Fit(m_panel);
    topSizer->Fit(this);
}

SimpleTransientPopup::~SimpleTransientPopup()
{
}

void SimpleTransientPopup::Popup(wxWindow* WXUNUSED(focus))
{
	wxPopupWindow::Show();
	//wxPopupWindow::PopupMenup();
}
/*
void SimpleTransientPopup::OnDismiss()
{
//    wxPopupWindow::OnDismiss();
}

bool SimpleTransientPopup::ProcessLeftDown(wxMouseEvent& event)
{
	event.Skip();
  //  aqui determinar se clicou fora.. mas nao quero mais q saia
	return true;//false;//wxPopupWindow::ProcessLeftDown(event);
}
*/
bool SimpleTransientPopup::Show( bool show )
{
   return wxPopupWindow::Show(show);
}

void SimpleTransientPopup::OnSize(wxSizeEvent &event)
{
   event.Skip();
}

void SimpleTransientPopup::OnSetFocus(wxFocusEvent &event)
{
    event.Skip();
}

void SimpleTransientPopup::OnKillFocus(wxFocusEvent &event)
{
    event.Skip();
}

void SimpleTransientPopup::OnMouse(wxMouseEvent &event)
{
   

//    event.Skip();
}

void SimpleTransientPopup::OnButton(wxCommandEvent& event)
{
	wxButton *button = wxDynamicCast(event.GetEventObject(), wxButton);
    if (button->GetLabel() == wxT("Fechar")){
		Show(false);
		Disable();
	}
    else{
		wxString s;
		int n = m_combo_descritores->GetSelection(); 
		if( n>=0){
			s= m_combo_descritores->GetString(n);//GetStringSelection();
			((FacesMainFrame* )GetParent())->AddSearchFilter(s);
		}else{
			wxMessageBox(wxT("Escolha um nome para inserir."));
		}
	}
    event.Skip();
}

