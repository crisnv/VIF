#ifndef _COMBO_PERSONAGENS_
#define _COMBO_PERSONAGENS_

#include "wx/combo.h"
#include "wx/odcombo.h"
#include "string.h"




class tComboPersonagens: public wxOwnerDrawnComboBox
{
	private: 
		char m_imgname[256];

	public:

	tComboPersonagens(		wxWindow *parent, wxWindowID id, const wxString& value,
		const wxPoint& pos, const wxSize& size, const wxArrayString& choices,
        long style, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxComboBoxNameStr ) ;

	void DeleteOneItem(int n){DoDeleteOneItem(n);};

};



#endif