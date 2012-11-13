#include "comboPersonagens.h"



tComboPersonagens::tComboPersonagens( wxWindow *parent, wxWindowID id, const wxString& value,
		const wxPoint& pos, const wxSize& size, const wxArrayString& choices,
        long style, const wxValidator& validator , const wxString& name )
	 : wxOwnerDrawnComboBox( 
	 	parent, id, value, pos, size, choices, style, validator , name ){
	

/*			SetForegroundColour(wxColour(0, 255, 0));
			SetBackgroundColour(wxColour(255, 0, 0));
			SetOwnForegroundColour(wxColour(0,255, 0));
			SetEditable(false); 
			*/

	};
