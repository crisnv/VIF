#include "searchPersonagens.h"

SearchPeople::SearchPeople(wxWindow *parent, wxWindowID id,
                      const wxString& label,
                      const wxPoint& pos ,
                      const wxSize& size ,
                      long style ,
                      const wxString& name)
					  :wxEditableListBox(parent,  id,
                      label, pos , size ,style , name )
{
	
	
	
	/*wxString strMsg;
		strMsg.Printf(_("(%s)"), (GetDelButton())->GetId()  );	
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING| wxOK ) ;
	(GetDelButton())->SetId(ID_OnDelItem);
	//(GetDownButton())->SetId(ID_OnDownItem);
	(GetEditButton())->SetId(ID_OnEditItem);
	
	*/
//	(GetDelButton())->Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(SearchPeople::OnRMouseDClick));
//	(GetNewButton())->Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(SearchPeople::OnRMouseDClick));
//	(GetListCtrl())->Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(SearchPeople::OnRMouseDClick));
//	(GetListCtrl())->Connect(wxEVT_COMMAND_LIST_END_LABEL_EDIT,  wxObjectEventFunction(SearchPeople::OnDelItem ));
}



SearchPeople::SearchPeople(): wxEditableListBox( )
{

	(GetDelButton())->Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(SearchPeople::OnRMouseDClick));
	(GetNewButton())->Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(SearchPeople::OnRMouseDClick));
	(GetListCtrl())->Connect(wxEVT_LEFT_DOWN,wxMouseEventHandler(SearchPeople::OnRMouseDClick));

}


void SearchPeople::OnItemSelected(wxListEvent& event){
	wxBitmapButton* db = ((wxEditableListBox	*)this)->GetDelButton();
    wxBitmapButton* eb = ((wxEditableListBox	*)this)->GetEditButton();
	
	m_index = event.GetIndex();
	db->Enable();
	eb->Enable();
}

void SearchPeople::OnEndLabelEdit(wxListEvent& event){

}
void SearchPeople::OnNewItem(wxCommandEvent& event){

}

void SearchPeople::OnDelItem(wxCommandEvent& event){
		
	wxString strMsg;
		strMsg.Printf(_("(%s)"), this->GetLabel());	
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING| wxOK ) ;
	
}
void SearchPeople::OnEditItem(wxCommandEvent& event){

}
void SearchPeople::OnUpItem(wxCommandEvent& event){
}
void SearchPeople::OnDownItem(wxCommandEvent& event){

}

void SearchPeople::OnCheckBox(wxCommandEvent& WXUNUSED(event))
{
    
}

enum
{
	CSearchPeople_ItemSelected = 500,
};

void SearchPeople::OnRMouseDClick( wxMouseEvent& event){
	
	wxString strMsg;
		strMsg.Printf(_("Nao abriu log da imagem (erro 2) (%s)"), this->GetLabel());	
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING| wxOK ) ;
		
}



BEGIN_EVENT_TABLE(SearchPeople, wxEditableListBox)
	
//	EVT_RIGHT_DOWN(/*	ID_OnItemSelected,SearchPeople::OnRMouseDClick)*/ 
	
//	EVT_CHOICE(/*	ID_OnItemSelected,*/ SearchPeople::OnRMouseDClick)

EVT_BUTTON(ID_Search,     SearchPeople::OnDelItem)
    /*
	EVT_LISTBOX   (ID_LISTBOX,              MyPanel::OnListBox)
EVT_LISTBOX   (ID_LISTBOX_SORTED,       MyPanel::OnListBox)
EVT_LISTBOX_DCLICK(ID_LISTBOX,          MyPanel::OnListBoxDoubleClick)
EVT_BUTTON    (ID_LISTBOX_SEL_NUM,      MyPanel::OnListBoxButtons)

EVT_BUTTON    (ID_LISTBOX_CLEAR,        MyPanel::OnListBoxButtons)
EVT_BUTTON    (ID_LISTBOX_APPEND,       MyPanel::OnListBoxButtons)
EVT_BUTTON    (ID_LISTBOX_DELETE,       MyPanel::OnListBoxButtons)
EVT_BUTTON    (ID_LISTBOX_FONT,         MyPanel::OnListBoxButtons)
EVT_CHECKBOX  (ID_LISTBOX_ENABLE,       MyPanel::OnListBoxButtons)

	ID_OnEndLabelEdit,
    ID_OnNewItem,
    ID_OnDelItem,
    ID_OnEditItem,
    ID_OnUpItem,
    ID_OnDownItem,
	*/

//	EVT_KEY_DOWN(FacesMainFrame::Onkeyboard)
/*	EVT_LIST_DELETE_ITEM(wxID_ANY, SearchPeople::OnItemSelected)
	EVT_CHECKBOX(wxID_ANY,SearchPeople::OnCheckBox)
	EVT_CHOICE(wxID_ANY, SearchPeople::OnCheckBox)
/*	EVT_CHECKLISTBOX
	
*/	
	EVT_LIST_ITEM_SELECTED(wxID_ANY, SearchPeople::OnItemSelected)
END_EVENT_TABLE()
/*  


    EVT_RIGHT_DOWN(MyTreeCtrl::OnRMouseDown)
    EVT_RIGHT_UP(MyTreeCtrl::OnRMouseUp)
    EVT_RIGHT_DCLICK(MyTreeCtrl::OnRMouseDClick)

#define EVT_COMMAND_LEFT_CLICK(winid, func) wx__DECLARE_EVT1(wxEVT_COMMAND_LEFT_CLICK, winid, wxCommandEventHandler(func))
#define EVT_COMMAND_LEFT_DCLICK(winid, func) wx__DECLARE_EVT1(wxEVT_COMMAND_LEFT_DCLICK, winid, wxCommandEventHandler(func))
#define EVT_COMMAND_RIGHT_CLICK(winid, func) wx__DECLARE_EVT1(wxEVT_COMMAND_RIGHT_CLICK, winid, wxCommandEventHandler(func))
#define EVT_COMMAND_RIGHT_DCLICK(winid, func) wx__DECLARE_EVT1(wxEVT_COMMAND_RIGHT_DCLICK, winid, wxCommandEventHandler(func))

*/