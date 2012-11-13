#ifndef _COMBO_DESCRITORES_
#define _COMBO_DESCRITORES_

#include "wx/combo.h"
#include "wx/odcombo.h"
#include "string.h"

#include "fundo.h"

class tComboDescritores: public wxOwnerDrawnComboBox
{
	private: 
		char m_dirname[256];

	public:

	tComboDescritores(
		wxWindow *parent, wxWindowID id, const wxString& value,
		const wxPoint& pos, const wxSize& size, const wxArrayString& choices,
        long style, const wxValidator& validator = wxDefaultValidator, const wxString& name = wxComboBoxNameStr)
	 : wxOwnerDrawnComboBox( 
	 	parent, id, value, pos, size, choices, style, validator , name ){};

	void SetDirname(const char dir[]){strcpy(m_dirname, dir);};
	char *GetDirname(void){return m_dirname;};

	void UpdateDescritorItens(Fundo *d);
};

#endif