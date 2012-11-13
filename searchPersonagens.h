#ifndef _SEARCH_PERSONAGENS_
#define _SEARCH_PERSONAGENS_

#include "wx/wx.h"
#include "wx/listbox.h"
#include "wx/listctrl.h"
#include "wx/editlbox.h"


enum
{

	ID_Search= 1500,
    ID_OnItemSelected ,
	ID_OnEndLabelEdit,
    ID_OnNewItem,
    ID_OnDelItem,
    ID_OnEditItem,
    ID_OnUpItem,
    ID_OnDownItem,
};


class SearchPeople : public wxEditableListBox
{
public:
	SearchPeople();
	SearchPeople(wxWindow *parent, wxWindowID id,
                      const wxString& label,
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxDefaultSize,
                      long style = wxEL_DEFAULT_STYLE,
                      const wxString& name = wxEditableListBoxNameStr);

	long  GetCurrentIndex(){return m_index;};
	void  SetCurrentIndex(long  id){m_index = id;};

protected:

	long m_index;
	
	void OnItemSelected(wxListEvent& event);
	void OnEndLabelEdit(wxListEvent& event);
	void OnNewItem(wxCommandEvent& event);
	void OnDelItem(wxCommandEvent& event);
	void OnEditItem(wxCommandEvent& event);
	void OnUpItem(wxCommandEvent& event);
	void OnDownItem(wxCommandEvent& event);
	void OnRMouseDClick( wxMouseEvent& event);
//GetClassInfo(void)
	void OnCheckBox(wxCommandEvent& WXUNUSED(event));
	
private:
	//DECLARE_DYNAMIC_CLASS(SearchPeople)
	//DECLARE_CLASS(SearchPeople) 
	DECLARE_EVENT_TABLE()
};




#endif