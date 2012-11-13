#include "navegadorFGV.h"

void FacesMainFrame::CreateCenterMainPanItens(void ){

	wxColour col1, col2, col3;
	col1.Set(wxT("#FFFFFF"));
	col2.Set(wxT("#CCCCCC"));
	col3.Set(wxT("#DDDDDD"));

	int framew=0,frameh=0;
	this->GetSize(&framew,&frameh);

	m_centerMainPan		= new wxPanel(m_panel, m_firstColumnSize, 0,
								m_secondColumnSize,frameh,wxBORDER_SUNKEN);
	
	
	m_centerPanCmds = new wxPanel(m_centerMainPan, m_firstColumnSize,0,							
							m_secondColumnSize,m_buttonH,wxBORDER_STATIC);//wxBORDER_SUNKEN);
	m_centerPanCmds->SetBackgroundColour(*wxLIGHT_GREY);//col3);
		
	m_centerPanLeg = new wxPanel(m_centerMainPan, m_firstColumnSize,
		//mudar aqui:					
							m_firstRowSize+m_secondRowSize,
							m_secondColumnSize,
							m_thirdRowSize ,wxBORDER_SUNKEN);
	m_centerPanLeg->SetBackgroundColour(*wxLIGHT_GREY);//col3);

	


/********************************************/
	if(!m_useMini){
		m_btCursor = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_DefautCursor, wxBitmap(wxT("icones/bottom/Cursor.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btMove= new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_MoveCursor, wxBitmap(wxT("icones/bottom/Move.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btAutoDetect = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_AutoDetect, wxBitmap(wxT("icones/bottom/FaceDetect.png"), 
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btPencil = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_PersonDraw, wxBitmap(wxT("icones/bottom/EditPerson.png"), 
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btPencil34 = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_PersonDraw34, wxBitmap(wxT("icones/bottom/EditPerson34.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btZoomIn = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_ZoomIn, wxBitmap(wxT("icones/bottom/ZoomIn.png"),
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btZoomOut = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_ZoomOut, wxBitmap(wxT("icones/bottom/ZoomOut.png"),
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	}else {
		m_btCursor = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_DefautCursor, wxBitmap(wxT("icones/bottom/mini_Cursor.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btMove= new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_MoveCursor, wxBitmap(wxT("icones/bottom/mini_Move.png"),
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btAutoDetect = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_AutoDetect, wxBitmap(wxT("icones/bottom/mini_FaceDetect.png"), 
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btPencil = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_PersonDraw, wxBitmap(wxT("icones/bottom/mini_EditPerson.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btPencil34 = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_PersonDraw34, wxBitmap(wxT("icones/bottom/mini_EditPerson34.png"), 
		  wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btZoomIn = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_ZoomIn, wxBitmap(wxT("icones/bottom/mini_ZoomIn.png"),
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
		m_btZoomOut = new wxBitmapButton(m_centerPanCmds, CNavegFGV_Button_ZoomOut, wxBitmap(wxT("icones/bottom/mini_ZoomOut.png"),
			wxBITMAP_TYPE_PNG),wxDefaultPosition,wxSize( m_buttonW, m_buttonH));
	}

	m_btCursor->SetToolTip(    hints[HINT_BT_CURSOR]   ) ;
	m_btMove->SetToolTip(    hints[HINT_BT_MOVE]    ) ; 
	m_btAutoDetect->SetToolTip(    hints[HINT_BT_AUTO_DETECT]    ) ; 
	m_btPencil->SetToolTip(  hints[HINT_BT_PENCIL]   )  ;
	m_btPencil34->SetToolTip(  hints[HINT_BT_PENCIL34]   ) ;
	m_btZoomIn->SetToolTip(  hints[HINT_BT_ZOOMIN]   )  ;
	m_btZoomOut->SetToolTip(  hints[HINT_BT_ZOOMOUT]   )  ;

	
	
	wxBoxSizer *hbox21 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox31 = new wxBoxSizer(wxHORIZONTAL);

	hbox21->Add(m_btCursor, 0, wxSHRINK);//wxEXPAND);
	hbox21->Add(m_btMove, 0, wxSHRINK);//wxEXPAND);
	hbox21->Add(m_btZoomIn, 0, wxSHRINK);//wxEXPAND);
	hbox21->Add(m_btZoomOut, 0, wxSHRINK);//wxEXPAND);
	
	hbox21->Add(m_btPencil, 0, wxSHRINK);//wxEXPAND);
	hbox21->Add(m_btPencil34, 0, wxSHRINK);//wxEXPAND);
	hbox21->Add(m_btAutoDetect, 0, wxSHRINK);//wxEXPAND);
	

	m_centerPanCmds->SetSizerAndFit(hbox21);




	m_canvas = new CanvasFoto(m_centerMainPan, wxPoint(0, m_firstRowSize),
		wxSize(m_secondColumnSize, m_secondRowSize));
	// Give it scrollbars: the virtual canvas is 20 * 50 = 1000 pixels in each direction
	


	m_textLegenda = new wxTextCtrl(m_centerPanLeg, wxID_ANY, wxT(""), 
								wxPoint(0,m_firstRowSize+m_secondRowSize),
								wxSize(m_secondColumnSize, m_thirdRowSize),
							 wxTE_MULTILINE|wxSUNKEN_BORDER);


	if(m_useMini){
		wxFont font= m_textLegenda->GetFont();
		//if(csize.GetWidth() <= 800)
			font.SetPointSize(font.GetPointSize() );//-2);	
		
		m_textLegenda->SetFont(font);
	}
	
	m_textLegenda->SetValue(_T("Legenda:"));
	m_textLegenda->SetToolTip( hints[HINT_LEGEND]);
	m_textLegenda->SetEditable(false);
	

	hbox31->Add(m_textLegenda);
	

	m_centerPanLeg->SetSizerAndFit(hbox31);

	wxBoxSizer *vbox2 = new wxBoxSizer(wxVERTICAL);
	vbox2->Add(m_canvas,6,wxSHRINK);
	vbox2->Add(m_centerPanCmds, 1, wxEXPAND);
	vbox2->Add(m_centerPanLeg, 1, wxEXPAND);
	m_centerMainPan->SetSizer(vbox2);

	
	/*
	m_centerMainPan->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_centerPanCmds->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_centerPanLeg->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_canvas->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	*/


}

