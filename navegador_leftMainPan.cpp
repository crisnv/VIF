#include "navegadorFGV.h"



void FacesMainFrame::CreateLeftMainPanItens( void){

	wxColour col1, col2, col3;
	col1.Set(wxT("#FFFFFF"));
	col2.Set(wxT("#CCCCCC"));
	col3.Set(wxT("#DDDDDD"));
	
	int framew=0,frameh=0;
	this->GetSize(&framew,&frameh);

	m_leftMainPan		= new wxPanel(m_panel, 0,0,m_firstColumnSize,frameh,wxBORDER_SUNKEN);
	
	//navegacao:
	wxBoxSizer *hbox11 = new wxBoxSizer(wxHORIZONTAL);
	//pesquisa:
#if (NAVEGADOR_VERSION > 1)
	wxBoxSizer *hbox12 = new wxBoxSizer(wxVERTICAL);//wxHORIZONTAL);
#endif

	
	wxStaticText *naveg_fundo= NULL;
	wxValidator v;
	if( !m_useMini){

		m_btMinimizePers	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_CollapseFaces, wxBitmap(wxT("icones/acervo/mini_Min-icon.png"),
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW/2, m_buttonH/2),4l, wxDefaultValidator, "Teste");
		m_btMaximizePers	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_ExpandFaces, wxBitmap(wxT("icones/acervo/mini_Max-icon.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW/2, m_buttonH/2));
#if (NAVEGADOR_VERSION > 1)				
		m_btOrderByName	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_SortByName, wxBitmap(wxT("icones/acervo/mini_orderByName.png"),
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW/2, m_buttonH/2));
		m_btOrderByStatus	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_SortByStatus, wxBitmap(wxT("icones/acervo/mini_orderByStatus.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW/2, m_buttonH/2));
		naveg_fundo= new wxStaticText(m_leftMainPan, -1,
			wxT("Navegador de Acervo"),wxPoint(0,0), 
			wxSize(m_firstColumnSize -4*(m_buttonW/2) ,m_tagSize));
#else
		naveg_fundo= new wxStaticText(m_leftMainPan, -1,
			wxT("Navegador de Acervo"),wxPoint(0,0), 
			wxSize(m_firstColumnSize -2*(m_buttonW/2) ,m_tagSize));	
#endif	

	}else {
		
		m_btMinimizePers	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_CollapseFaces, wxBitmap(wxT("icones/acervo/mini2_Min-icon.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW*3/4, m_buttonH*3/4));
		m_btMaximizePers	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_ExpandFaces, wxBitmap(wxT("icones/acervo/mini2_Max-icon.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW*3/4, m_buttonH*3/4));
#if (NAVEGADOR_VERSION > 1)				
		m_btOrderByName	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_SortByName, wxBitmap(wxT("icones/acervo/mini2_orderByName.png"),
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize(m_buttonW*3/4, m_buttonH*3/4));
		m_btOrderByStatus	= new wxBitmapButton(m_leftMainPan, CNavegFGV_Button_SortByStatus, wxBitmap(wxT("icones/acervo/mini2_orderByStatus.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW*3/4, m_buttonH*3/4));
		naveg_fundo= new wxStaticText(m_leftMainPan, -1,
			wxT("Navegador de Acervo"),wxPoint(0,0), 
			wxSize(m_firstColumnSize -4*(m_buttonW*3/4) ,m_tagSize));
#else
		naveg_fundo= new wxStaticText(m_leftMainPan, -1,
			wxT("Navegador de Acervo"),wxPoint(0,0), 
			wxSize(m_firstColumnSize -2*(m_buttonW*3/4) ,m_tagSize));
#endif		
	
	}
#if (NAVEGADOR_VERSION > 1)		
	m_btOrderByName->SetToolTip( hints[HINT_BT_ORDERBYNAME] );
	m_btOrderByStatus->SetToolTip( hints[HINT_BT_ORDERBYSTATUS] );
#endif
	m_btMinimizePers->SetToolTip( hints[HINT_BT_MINIMIZEPERS] );
	m_btMaximizePers->SetToolTip( hints[HINT_BT_MAXIMIZEPERS] );


		
	if(m_useMini){
		wxFont font= naveg_fundo->GetFont();
		//if(csize.GetWidth() <= 800)
			font.SetPointSize(font.GetPointSize() -2);	
		naveg_fundo->SetFont(font);
	}
	
	

#ifdef _DEBUG
	m_textCtrl = new wxTextCtrl(m_leftMainPan, wxID_ANY, wxT(""),
		wxPoint(0,m_firstRowSize+m_secondRowSize), wxSize(m_firstColumnSize, m_thirdRowSize),
                                wxTE_MULTILINE | wxSUNKEN_BORDER);

#else
//o log ficou no release por conta dos warnings do wxwidgets
	m_textCtrl = new wxTextCtrl(m_leftMainPan, wxID_ANY, wxT(""),
		wxPoint(0,m_firstRowSize+m_secondRowSize+10*m_buttonH), wxSize(m_firstColumnSize, m_thirdRowSize),
                                wxTE_MULTILINE | wxSUNKEN_BORDER);
	
#endif
	m_textCtrl->SetValue(_T("Log:"));
	m_textCtrl->SetEditable(false);

	
	

	CreateTreeWithDefStyle(m_firstColumnSize, m_firstRowSize + m_secondRowSize-m_buttonH/**/ -m_tagSize);
/*
#else
	CreateTreeWithDefStyle(m_firstColumnSize, frameh-m_tagSize);
#endif
	*/


	m_treeCtrl->SetToolTip( hints[HINT_TREE]);

//#ifdef _DEBUG
	// set our text control as the log target
    wxLogTextCtrl *logWindow = new wxLogTextCtrl(m_textCtrl);
//#endif

	hbox11->Add(naveg_fundo,0, wxEXPAND);
#if (NAVEGADOR_VERSION > 1)		
	hbox11->Add(m_btOrderByName,0, wxSHRINK);
	hbox11->Add(m_btOrderByStatus,0, wxSHRINK);
#endif
	hbox11->Add(m_btMinimizePers,0, wxSHRINK);
	hbox11->Add(m_btMaximizePers,0, wxSHRINK);
	
	
#if (NAVEGADOR_VERSION > 1)
	m_listbox_search = new SearchPeople//wxEditableListBox
		(m_leftMainPan,ID_Search, _("Busca Personagem:"),
		wxPoint(0,24), wxSize(m_firstColumnSize,2*m_buttonH),
		wxEL_ALLOW_EDIT|	wxEL_ALLOW_NEW|	wxEL_ALLOW_DELETE|wxEL_NO_REORDER,//|1792L,		
					wxEditableListBoxNameStr);
	/*
	
    wxListCtrl* GetListCtrl()       { return m_listCtrl; }
    wxBitmapButton* GetDelButton()  { 
		return m_bDel; }
    wxBitmapButton* GetNewButton()  { return m_bNew; }
    wxBitmapButton* GetUpButton()   { return m_bUp; }
    wxBitmapButton* GetDownButton() { return m_bDown; }
    wxBitmapButton* GetEditButton() { return m_bEdit; }
	wxBitmapButton* pbb = ((wxEditableListBox*)m_listbox_search)->GetEditButton();
	*/
	 
	Bind(wxEVT_COMMAND_LIST_BEGIN_LABEL_EDIT,   &FacesMainFrame::OnSearch_BEGIN_LABEL_EDIT, this);
	Bind(wxEVT_COMMAND_LIST_DELETE_ITEM,		&FacesMainFrame::OnSearch_ITEM_DELETED, this);
	/*
	Bind(wxEVT_COMMAND_LIST_END_LABEL_EDIT,		&FacesMainFrame::OnSearch_END_LABEL_EDIT, this);
	Bind(wxEVT_COMMAND_LIST_INSERT_ITEM,		&FacesMainFrame::OnSearch_INSERT_ITEM, this);
	Bind(wxEVT_COMMAND_LIST_ITEM_SELECTED,		&FacesMainFrame::OnSearch_ITEM_SELECTED, this);
	//Bind(wxEVT_COMMAND_LIST_DELETE_ALL_ITEMS
	Bind(wxEVT_COMMAND_LIST_ITEM_ACTIVATED,		&FacesMainFrame::OnSearch_END_LABEL_EDIT, this);
	Bind(wxEVT_COMMAND_LIST_ITEM_FOCUSED,		&FacesMainFrame::OnSearch_END_LABEL_EDIT, this);
	Bind(wxEVT_COMMAND_LIST_KEY_DOWN,			&FacesMainFrame::OnSearch_END_LABEL_EDIT, this);
	Bind(wxEVT_COMMAND_LIST_ITEM_DESELECTED,		&FacesMainFrame::OnSearch_END_LABEL_EDIT, this);
	 */



	hbox12->Add(m_listbox_search,0,wxEXPAND);
#endif

	wxBoxSizer *vbox1 = new wxBoxSizer(wxVERTICAL);

	vbox1->Add(hbox11,0, wxSHRINK);
	vbox1->Add(m_treeCtrl,6, wxEXPAND);
#if (NAVEGADOR_VERSION > 1)
	vbox1->Add(hbox12,0, wxSHRINK);
#endif

	//log:
//
#ifdef _DEBUG
	vbox1->Add(m_textCtrl,1, wxEXPAND); 
//
#endif

	m_leftMainPan->SetSizerAndFit(vbox1);
	
//ativa o log:
//#ifdef _DEBUG
	delete wxLog::SetActiveTarget(logWindow);
//#endif
}
