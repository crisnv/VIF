#include "navegadorFGV.h"

void FacesMainFrame::CreateRightMainPanItens(void ){

	wxColour col1, col2, col3;
	col1.Set(wxT("#FFFFFF"));
	col2.Set(wxT("#CCCCCC"));
	col3.Set(wxT("#DDDDDD"));

	wxBoxSizer *vbox3 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *vbox31 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *vbox32 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *vbox33 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *vbox34 = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *vbox35 = new wxBoxSizer(wxVERTICAL);
	

	m_rightMainPan= new wxPanel(m_panel, 1000,0,m_thirdColumnSize,800,wxBORDER_SUNKEN);
	
	m_rightMainPanUp	= new wxPanel(m_rightMainPan, 0,0,
		m_thirdColumnSize,m_thirdColumnSize,wxBORDER_SUNKEN);
	m_rightMainPanUp->SetBackgroundColour(*wxLIGHT_GREY);//col3);

	if(!m_useMini){
	m_rightMainPanCombos= new wxPanel(m_rightMainPan, 0,0,m_thirdColumnSize,
										/*80*/128,wxBORDER_SUNKEN);
	}else{
	m_rightMainPanCombos= new wxPanel(m_rightMainPan, 0,0,m_thirdColumnSize,
										104,wxBORDER_SUNKEN);
	}
	m_rightMainPanCombos->SetBackgroundColour(*wxLIGHT_GREY);//col2);

	m_rightMainPanPerson	= new wxPanel(m_rightMainPan, 0,0,m_thirdColumnSize,300,wxBORDER_SUNKEN);
	m_rightMainPanPerson->SetBackgroundColour(*wxLIGHT_GREY);//col2);

	m_rightMainPanPhoto	= new wxPanel(m_rightMainPan, 0,0,m_thirdColumnSize,300,wxBORDER_SUNKEN);
	m_rightMainPanPhoto->SetBackgroundColour(*wxLIGHT_GREY);//col2);
	

	m_rightMainPanTagging = new wxPanel(m_rightMainPan, 0,0,m_thirdColumnSize,300,wxBORDER_SUNKEN);
	m_rightMainPanTagging->SetBackgroundColour(*wxLIGHT_GREY);//col2);
	

	
	
	if(!m_useMini){
		m_b3Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoPrevious, wxBitmap(wxT("icones/navigate/Button-Previous-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b4Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoNext, wxBitmap(wxT("icones/navigate/Button-Next-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b5Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoFirst,wxBitmap(wxT("icones/navigate/Button-First-icon.png"), 
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b6Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoLast, wxBitmap(wxT("icones/navigate/Button-Last-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	}else{
		m_b3Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoPrevious, wxBitmap(wxT("icones/navigate/mini_Button-Previous-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b4Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoNext, wxBitmap(wxT("icones/navigate/mini_Button-Next-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b5Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoFirst,wxBitmap(wxT("icones/navigate/mini_Button-First-icon.png"), 
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b6Photo = new wxBitmapButton(m_rightMainPanPhoto, CNavegFGV_Button_PhotoLast, wxBitmap(wxT("icones/navigate/mini_Button-Last-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	
	}


	m_b3Photo->SetToolTip(    hints[ HINT_BT_PHOTO3]   ) ; 
	m_b4Photo->SetToolTip(    hints[ HINT_BT_PHOTO4]   ) ; 
	m_b5Photo->SetToolTip(    hints[ HINT_BT_PHOTO5]   ) ;  
	m_b6Photo->SetToolTip(    hints[ HINT_BT_PHOTO6]   ) ; 





	wxGridSizer *gridBotoesNavega =  new wxGridSizer(2,2, 0, 0);	
	gridBotoesNavega->Add(m_b3Photo, 0, wxSHRINK );
	gridBotoesNavega->Add(m_b4Photo, 0, wxSHRINK );
	gridBotoesNavega->Add(m_b5Photo, 0, wxSHRINK );
	gridBotoesNavega->Add(m_b6Photo, 0, wxSHRINK );
	//m_rightMainPanPhoto->SetSizerAndFit(gridBotoesNavega);
	
	wxStaticText *naveg_photos = NULL;
	if(!m_useMini){
		naveg_photos= new wxStaticText(m_rightMainPanPhoto, -1,
			wxT("Navegação de Fotos"),wxPoint(0,0),wxSize(m_thirdColumnSize, m_tagSize));
	}else{
		naveg_photos= new wxStaticText(m_rightMainPanPhoto, -1,
			wxT("Navegação de Fotos"),wxPoint(0,0),wxSize(m_thirdColumnSize, 1.0*m_tagSize));

	}

	vbox34->Add(naveg_photos,0, wxEXPAND);	
	vbox34->Add(gridBotoesNavega, 0,	wxSHRINK);
	m_rightMainPanPhoto->SetSizerAndFit(vbox34);


	
	if(!m_useMini){
		m_b1Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoCheck, wxBitmap(wxT("icones/navigate/Check-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b2Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoInprogress, wxBitmap(wxT("icones/navigate/Check-iconYellow.png"), //Delete-icon
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b7Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoDelete, wxBitmap(wxT("icones/navigate/Check-iconRed.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b8Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoApprove, wxBitmap(wxT("icones/navigate/Check-iconBlue.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	}else{
		m_b1Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoCheck, wxBitmap(wxT("icones/navigate/mini_Check-icon.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b2Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoInprogress, wxBitmap(wxT("icones/navigate/mini_Check-iconYellow.png"), //Delete-icon
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b7Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoDelete, wxBitmap(wxT("icones/navigate/mini_Check-iconRed.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b8Photo = new wxBitmapButton(m_rightMainPanTagging, CNavegFGV_Button_PhotoApprove, wxBitmap(wxT("icones/navigate/mini_Check-iconBlue.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	}


	m_b1Photo->SetToolTip(    hints[HINT_BT_PHOTO1 ]   ) ; 
	m_b2Photo->SetToolTip(    hints[HINT_BT_PHOTO2 ]   ) ; 
	m_b7Photo->SetToolTip(    hints[HINT_BT_PHOTO7 ]   ) ; 
	m_b8Photo->SetToolTip(    hints[HINT_BT_PHOTO8 ]   ) ;  




	wxGridSizer *gridBotoesTagging =  new wxGridSizer(2,2, 0, 0);	
	gridBotoesTagging->Add(m_b1Photo, 0, wxSHRINK );
	gridBotoesTagging->Add(m_b2Photo, 0, wxSHRINK );
	gridBotoesTagging->Add(m_b7Photo, 0, wxSHRINK );
	gridBotoesTagging->Add(m_b8Photo, 0, wxSHRINK );
	
	wxStaticText *marca_photos= new wxStaticText(m_rightMainPanTagging, -1,
		wxT("Marcação de Fotos"),wxPoint(0,0),wxSize(m_thirdColumnSize, m_tagSize));

	if(m_useMini){
		wxFont font= naveg_photos->GetFont();
		//if(csize.GetWidth() <= 800)
			font.SetPointSize(font.GetPointSize() -2);	

		naveg_photos->SetFont(font);
		marca_photos->SetFont(font);
	}
		
	vbox35->Add(marca_photos,0, wxEXPAND);
	vbox35->Add(gridBotoesTagging, 0,	wxSHRINK);
	m_rightMainPanTagging->SetSizerAndFit(vbox35);

	
		
	if(!m_useMini){
		m_b1Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonCheck, wxBitmap(wxT("icones/personNavigate/CheckPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b2Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonDelete, wxBitmap(wxT("icones/personNavigate/DeletePerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b3Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonPrevious, wxBitmap(wxT("icones/personNavigate/PreviousPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b4Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonNext, wxBitmap(wxT("icones/personNavigate/NextPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b5Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonFirst, wxBitmap(wxT("icones/personNavigate/FirstPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b6Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonLast, wxBitmap(wxT("icones/personNavigate/LastPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	}else{
		m_b1Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonCheck, wxBitmap(wxT("icones/personNavigate/mini_CheckPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b2Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonDelete, wxBitmap(wxT("icones/personNavigate/mini_DeletePerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b3Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonPrevious, wxBitmap(wxT("icones/personNavigate/mini_PreviousPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b4Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonNext, wxBitmap(wxT("icones/personNavigate/mini_NextPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b5Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonFirst, wxBitmap(wxT("icones/personNavigate/mini_FirstPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_b6Person = new wxBitmapButton(m_rightMainPanPerson, CNavegFGV_Button_PersonLast, wxBitmap(wxT("icones/personNavigate/mini_LastPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	}
	



	m_b1Person->SetToolTip(    hints[	HINT_BT_PERSON1	]);
	m_b2Person->SetToolTip(    hints[	HINT_BT_PERSON2	]);
	m_b3Person->SetToolTip(    hints[	HINT_BT_PERSON3	]);
	m_b4Person->SetToolTip(    hints[	HINT_BT_PERSON4	]);
	m_b5Person->SetToolTip(    hints[	HINT_BT_PERSON5	]);
	m_b6Person->SetToolTip(    hints[	HINT_BT_PERSON6	]);
	

	




	wxGridSizer *gridBotoesPerson =  new wxGridSizer(3,2, 0, 0);	
	gridBotoesPerson->Add(m_b1Person, 0, wxSHRINK);//wxEXPAND);
	gridBotoesPerson->Add(m_b2Person, 0, wxSHRINK);//wxEXPAND);
	gridBotoesPerson->Add(m_b3Person, 0, wxSHRINK);//wxEXPAND);
	gridBotoesPerson->Add(m_b4Person, 0, wxSHRINK);//wxEXPAND);
	gridBotoesPerson->Add(m_b5Person, 0, wxSHRINK);//wxEXPAND);
	gridBotoesPerson->Add(m_b6Person, 0, wxSHRINK);//wxEXPAND);

	wxStaticText *naveg_faces= NULL;
	if(!m_useMini){
		naveg_faces= new wxStaticText(m_rightMainPanPerson, -1,
			wxT("Navegação de Faces"),wxPoint(0,0),wxSize(m_thirdColumnSize, m_tagSize));
	}else{
		naveg_faces= new wxStaticText(m_rightMainPanPerson, -1,
			wxT("Navegação de Faces"),wxPoint(0,0),wxSize(m_thirdColumnSize, 1.0*m_tagSize));


		wxFont font= naveg_faces->GetFont();
		//if(csize.GetWidth() <= 800)
			font.SetPointSize(font.GetPointSize() - 2);	

		naveg_faces->SetFont(font);
	}
	vbox33->Add(naveg_faces,0, wxEXPAND);		
	vbox33->Add(gridBotoesPerson, 0,	wxSHRINK);
	m_rightMainPanPerson->SetSizerAndFit(vbox33);

	//m_rightMainPanPerson->SetSizerAndFit(gridBotoesPerson);



	/**/
	m_miniCanvas= new CanvasFace(m_rightMainPanUp, wxPoint(0, 0), 
		wxSize(m_thirdColumnSize, m_thirdColumnSize));

	vbox31->Add(m_miniCanvas,0, wxSHRINK);
	m_rightMainPanUp->SetSizerAndFit(vbox31);


	wxStaticText *t_nomes= new wxStaticText(m_rightMainPanCombos, -1,
		wxT("Nomes Livres"));
	
	wxStaticText *t_personagem = new wxStaticText(m_rightMainPanCombos, -1,
		wxT("Personagens"));
		
	wxStaticText *t_descritor = new wxStaticText(m_rightMainPanCombos, -1, 
		wxT("Descritores"));
	
	if(m_useMini){
		wxFont font= t_nomes->GetFont();
		//if(csize.GetWidth() <= 800)
			font.SetPointSize(font.GetPointSize() -2);	

		t_nomes->SetFont(font);
		t_personagem->SetFont(font);
		t_descritor->SetFont(font);
	}



	wxArrayString choices;

	m_combo_nomes = new tComboPersonagens(m_rightMainPanCombos,wxID_ANY,wxEmptyString,
                                   wxPoint(0,24), wxSize(m_comboW,m_comboH), choices, wxCB_SORT|wxCB_READONLY);
		
	m_combo_personagens = new tComboPersonagens(m_rightMainPanCombos,wxID_ANY,wxEmptyString,
                                   wxPoint(0,68), wxSize(m_comboW,m_comboH), choices, wxCB_SORT|wxCB_READONLY);
		
	m_combo_descritores = new tComboDescritores(m_rightMainPanCombos,wxID_ANY,wxEmptyString,
                                   wxPoint(0,112), wxSize(m_comboW,m_comboH), choices, wxCB_SORT|wxCB_READONLY);
	

	if(m_useMini){
		wxFont font= m_combo_nomes->GetFont();
		//if(csize.GetWidth() <= 800)
			font.SetPointSize(font.GetPointSize() -2);	

		m_combo_nomes->SetFont(font);
		m_combo_personagens->SetFont(font);
		m_combo_descritores->SetFont(font);
#if (NAVEGADOR_VERSION > 1)
			m_listbox_search->SetFont(font);
#endif
	}


	vbox32->Add(t_nomes,0, wxEXPAND);
	vbox32->Add(m_combo_nomes,0, wxEXPAND);
	vbox32->Add(t_personagem,0, wxEXPAND);
	vbox32->Add(m_combo_personagens,0, wxEXPAND);
	vbox32->Add(t_descritor,0, wxEXPAND);
	vbox32->Add(m_combo_descritores,0, wxEXPAND);
	m_rightMainPanCombos->SetSizer(vbox32);

		
	wxStaticText *text_miniCanvas= 
		new wxStaticText(m_rightMainPan, -1,
		wxT("Navegador de Faces"),wxPoint(0,0),wxSize(m_thirdColumnSize, m_tagSize));

	if(m_useMini){
		wxFont font= text_miniCanvas->GetFont();
		//if(csize.GetWidth() <= 800)
			font.SetPointSize(font.GetPointSize() -2);	

		text_miniCanvas->SetFont(font);
	}

	vbox3->Add(text_miniCanvas,0, wxEXPAND);
	vbox3->Add(m_rightMainPanUp,0, wxSHRINK);
	vbox3->Add(m_rightMainPanCombos,0, wxEXPAND);
	vbox3->Add(m_rightMainPanPerson,0,wxEXPAND);// wxSHRINK); //
	vbox3->Add(m_rightMainPanPhoto,0, wxEXPAND);//wxSHRINK);	//
	vbox3->Add(m_rightMainPanTagging,0, wxEXPAND);//wxSHRINK);	//

	m_rightMainPan->SetSizer(vbox3);
}
