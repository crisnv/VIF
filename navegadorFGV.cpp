// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/log.h"
#endif

#include "wx/colordlg.h"
#include "wx/numdlg.h"

#include "wx/image.h"
#include "wx/imaglist.h"
#include "wx/math.h"

#include "wx/image.h"



/*
enum MyItens {
MY_CURSOR_HAND           ,
MY_CURSOR_BULLSEYE       ,
MY_CURSOR_PENCIL         ,
MY_CURSOR_MAGNIFIER      ,
MY_CURSOR_ROLLER         ,
MY_CURSOR_PBRUSH         ,
MY_CURSOR_PLEFT          ,
MY_CURSOR_PRIGHT         ,
MY_CURSOR_BLANK          ,
MY_CURSOR_RIGHT_ARROW    ,
MY_CURSOR_CROSS          
};
#define MY_CURSOR_CROSS wxStockGDI::GetCursor(wxStockGDI::CURSOR_CROSS)
*/

#ifdef __WIN32__
    // this is not supported by native control
    #define NO_VARIABLE_HEIGHT
#endif


#include "fotografia.h"
#include "fundo.h"
#include "gerenciador.h"
#include "dicionario.h"
#include "legenda.h"
//#include "arvoreFundos.h"
#include "canvas.h"
#include "canvasFace.h"

#include "navegadorFGV.h"
#include "dirProcessing.h"


#if  (NAVEGADOR_VERSION >1)
#include	"searchPopup.h"
#endif


#ifndef __WXMSW__
    #include "../sample.xpm"
#endif

#include <vector>
using namespace std;




#define MENU_LINK(name) EVT_MENU(CNavegFGV_##name, FacesMainFrame::On##name)

BEGIN_EVENT_TABLE(FacesMainFrame, wxFrame)

	EVT_IDLE(FacesMainFrame::OnIdle)
    EVT_SIZE(FacesMainFrame::OnSize)
	//
	EVT_KEY_DOWN(FacesMainFrame::Onkeyboard)

	EVT_ERASE_BACKGROUND(FacesMainFrame::OnEraseBackGround)

	EVT_BUTTON(CNavegFGV_Button_PersonCheck, FacesMainFrame::OnBtPersonCheck)
	EVT_BUTTON(CNavegFGV_Button_PersonDelete, FacesMainFrame::OnBtPersonDelete)
	EVT_BUTTON(CNavegFGV_Button_PersonPrevious, FacesMainFrame::OnBtPersonPrevious)
	EVT_BUTTON(CNavegFGV_Button_PersonNext, FacesMainFrame::OnBtPersonNext)
	EVT_BUTTON(CNavegFGV_Button_PersonFirst, FacesMainFrame::OnBtPersonFirst)
	EVT_BUTTON(CNavegFGV_Button_PersonLast, FacesMainFrame::OnBtPersonLast)

	EVT_BUTTON(CNavegFGV_Button_DefautCursor, FacesMainFrame::OnBtDefautCursor)
	EVT_BUTTON(CNavegFGV_Button_MoveCursor, FacesMainFrame::OnBtMoveCursor)
	EVT_BUTTON(CNavegFGV_Button_AutoDetect, FacesMainFrame::OnBtAutoDetect)
	EVT_BUTTON(CNavegFGV_Button_PersonDraw, FacesMainFrame::OnBtPersonDraw)
	EVT_BUTTON(CNavegFGV_Button_PersonDraw34, FacesMainFrame::OnBtPersonDraw34)
	EVT_BUTTON(CNavegFGV_Button_ZoomIn, FacesMainFrame::OnBtZoomIn)
	EVT_BUTTON(CNavegFGV_Button_ZoomOut, FacesMainFrame::OnBtZoomOut)
	
	EVT_BUTTON(CNavegFGV_Button_PhotoCheck, FacesMainFrame::OnBtPhotoCheck)
	EVT_BUTTON(CNavegFGV_Button_PhotoInprogress, FacesMainFrame::OnBtPhotoInprogress)
	EVT_BUTTON(CNavegFGV_Button_PhotoApprove, FacesMainFrame::OnBtPhotoApprove)
	EVT_BUTTON(CNavegFGV_Button_PhotoDelete, FacesMainFrame::OnBtPhotoDelete)
	
	EVT_BUTTON(CNavegFGV_Button_PhotoPrevious, FacesMainFrame::OnBtPhotoPrevious)
	EVT_BUTTON(CNavegFGV_Button_PhotoNext, FacesMainFrame::OnBtPhotoNext)
	EVT_BUTTON(CNavegFGV_Button_PhotoFirst, FacesMainFrame::OnBtPhotoFirst)
	EVT_BUTTON(CNavegFGV_Button_PhotoLast, FacesMainFrame::OnBtPhotoLast)

#if  (NAVEGADOR_VERSION > 1)
	EVT_BUTTON(	CNavegFGV_Button_SortByName, FacesMainFrame::OnBtSortByName)
	EVT_BUTTON( CNavegFGV_Button_SortByStatus, FacesMainFrame::OnBtSortByStatus)

	EVT_LIST_BEGIN_LABEL_EDIT(ID_Search, FacesMainFrame::OnSearch_BEGIN_LABEL_EDIT) 
	EVT_LIST_DELETE_ITEM(ID_Search, FacesMainFrame::OnSearch_ITEM_DELETED)
	
	/*
	EVT_TEXT_ENTER(ID_Search, FacesMainFrame::OnSearch_END_LABEL_EDIT_txt)
//	EVT_KEY_DOWN(
	EVT_LIST_ITEM_SELECTED(ID_Search, FacesMainFrame::OnSearch_ITEM_SELECTED)
	EVT_LIST_END_LABEL_EDIT(ID_Search, FacesMainFrame::OnSearch_END_LABEL_EDIT) 
	EVT_LIST_INSERT_ITEM(ID_Search, FacesMainFrame::OnSearch_INSERT_ITEM)   
	EVT_BUTTON(ID_Search, FacesMainFrame::OnSearch_ITEM_DELETEDbt) 
	EVT_LIST_ITEM_ACTIVATED( ID_Search,		 FacesMainFrame::OnSearch_END_LABEL_EDIT )
	EVT_LIST_ITEM_FOCUSED(ID_Search,		 FacesMainFrame::OnSearch_END_LABEL_EDIT )
	EVT_LIST_KEY_DOWN( ID_Search,		 FacesMainFrame::OnSearch_END_LABEL_EDIT )
	*/

	//    EVT_BUTTON(Minimal_StartSimplePopup, MyDialog::OnStartSimplePopup)
 


#endif	
	EVT_BUTTON(	CNavegFGV_Button_CollapseFaces, FacesMainFrame::OnBtCollapseFaces)
	EVT_BUTTON( CNavegFGV_Button_ExpandFaces, FacesMainFrame::OnBtExpandFaces)



	MENU_LINK(LoadDir)
	MENU_LINK(CloseDir)
	MENU_LINK(LoadImgFile)
	MENU_LINK(SaveImgFile)

	MENU_LINK(Quit)
	MENU_LINK(Help)
    MENU_LINK(About)
    
	MENU_LINK(ViewPersonagens)
    MENU_LINK(ViewFaces)
    
	MENU_LINK(DetectFaces)
    MENU_LINK(DetectPersonagens)
    
    MENU_LINK(Highlight)
	
#undef MENU_LINK

END_EVENT_TABLE()

IMPLEMENT_APP(FacesApp)

Fotografia *fotoAtual = NULL;

Gerenciador *g_ger = Gerenciador::GetInstance();

wxTextCtrl* FacesMainFrame::m_textLegenda = NULL;
CanvasFoto *FacesMainFrame::m_canvas= NULL;
CanvasFace *FacesMainFrame::m_miniCanvas= NULL;

tComboPersonagens	*FacesMainFrame::m_combo_personagens = NULL;
tComboPersonagens	*FacesMainFrame::m_combo_nomes = NULL;
tComboDescritores 	*FacesMainFrame::m_combo_descritores = NULL; 
//tComboPersonagens	*FacesMainFrame::m_combo_search = NULL; 
#if  (NAVEGADOR_VERSION > 1)
SearchPeople *FacesMainFrame::m_listbox_search = NULL; 
#endif

vector<tlegenda> FacesMainFrame::m_legendList;

MyTreeCtrl *FacesMainFrame::m_treeCtrl;

wxFrame* FacesApp::m_frame = NULL;



wxFrame* FacesApp::getFacesMainFrame(){
	return m_frame;
}

bool FacesApp::OnInit(){

	wxImage::AddHandler(new wxPNGHandler);
	wxImage::AddHandler(new wxBMPHandler);
	wxImage::AddHandler(new wxJPEGHandler);
	wxImage::AddHandler(new wxTIFFHandler);
	
    // Create the main frame window
    m_frame = new FacesMainFrame( wxT("Navegador de Cadastro de Personagens Históricos (CPDOC-FGV)"),
							0, 0, 1280, 1024);

    // Show the frame
    m_frame->Show(true);
    SetTopWindow(m_frame);
	//	m_frame->Maximize();	

    return true;
}


// My frame constructor
FacesMainFrame::FacesMainFrame(const wxString& title, int x, int y, int w, int h)
       : wxFrame((wxFrame *)NULL, wxID_ANY, title, wxPoint(x, y), wxSize(w, h)) //, m_treeCtrl(NULL)
#if wxUSE_LOG
#ifdef _DEBUG
       //  , m_textCtrl(NULL)
#endif
#endif // wxUSE_LOG
{
	Maximize();
	
	wxSize csize = GetClientSize();
   
	m_useMini = true;
	if(csize.GetWidth() > 800 && csize.GetHeight() >800 ){
		m_useMini = false;	
	}

	// This reduces flicker effects - even better would be to define
    // OnEraseBackground to do nothing. When the tree control's scrollbars are
    // show or hidden, the frame is sent a background erase event.
	//coloquei alfa 0 para diminuir o flick
    SetBackgroundColour(*wxWHITE);//wxColour(255, 255, 255,0));

    // Give it an icon
    SetIcon(wxICON(sample));
				
	//m_curDefault= new wxCursor(wxT(""),wxBITMAP_TYPE_CUR);
	m_curPencil = new wxCursor(wxT("cur/cross.cur"),wxBITMAP_TYPE_CUR);
	m_curPencil34 = new wxCursor(wxT("cur/cross34.cur"),wxBITMAP_TYPE_CUR);
	m_curMove	= new wxCursor(wxT("cur/move2.ico"),wxBITMAP_TYPE_ICO);
	m_curZoomIn	= new wxCursor(wxT("cur/zoomin.cur"),wxBITMAP_TYPE_CUR);
	m_curZoomOut= new wxCursor(wxT("cur/zoomout.cur"),wxBITMAP_TYPE_CUR);
	m_curHand	= new wxCursor(wxT("cur/hand.ico"),wxBITMAP_TYPE_ICO);
	m_curDrag	= new wxCursor(wxT("cur/drag.ico"),wxBITMAP_TYPE_ICO);
	
		
	if((m_curPencil ==NULL)|| 	(m_curPencil34 ==NULL)|| (m_curMove ==NULL)||
		(m_curZoomIn ==NULL)|| (m_curZoomOut==NULL) ||	(m_curHand	==NULL)|| 	(m_curDrag	==NULL)
		){
		printf("Erro");
	}

#if wxUSE_MENUS
    // Make a menubar
    wxMenu *file_menu = new wxMenu,
		   *tree_menu = new wxMenu,
           *item_menu = new wxMenu,
		   *view_menu = new wxMenu,
		   *face_menu = new wxMenu;
	
		
	file_menu->Append(CNavegFGV_LoadDir, _T("A&brir diretório\tAlt+B"), _T("Abrir diretorio"));
	file_menu->Append(CNavegFGV_CloseDir, _T("&Fechar diretório\tAlt+C"), _T("Fechar diretorio"));
	file_menu->AppendSeparator();
	file_menu->Append(CNavegFGV_Help, wxT("&Ajuda..."));
    file_menu->AppendSeparator();
	file_menu->Append(CNavegFGV_About, wxT("&Sobre..."));
    file_menu->AppendSeparator();
    file_menu->Append(CNavegFGV_Quit, wxT("Sai&r\tAlt-X"));
   

	face_menu->AppendCheckItem(CNavegFGV_DetectFaces, wxT("Detectar faces automaticamente\tAlt+D"));
	face_menu->Check(CNavegFGV_DetectFaces, true);
	/*
	face_menu->AppendCheckItem(CNavegFGV_DetectPersonagens, wxT("Detectar personagens automaticamente"));
	face_menu->AppendSeparator();
	*/
   	face_menu->AppendCheckItem(CNavegFGV_ViewPersonagens, wxT("Visualizar &Personagens\tAlt+P"));
	face_menu->Check(CNavegFGV_ViewPersonagens, true);
	face_menu->AppendCheckItem(CNavegFGV_ViewFaces, wxT("Visualizar &Faces\tAlt+F"));
	face_menu->Check(CNavegFGV_ViewFaces, true);
    face_menu->AppendSeparator();
   
	view_menu->Append(CNavegFGV_ViewCharacter, wxT("Visualizar &Personagem\tAlt+F"));
	view_menu->AppendSeparator();
	view_menu->Append(CNavegFGV_ViewRelations, wxT("Visualizar &Relações\tAlt+F"));

    wxMenuBar *menu_bar = new wxMenuBar;
    menu_bar->Append(file_menu, wxT("&Arquivo"));
	menu_bar->Append(face_menu, wxT("&Face"));
	menu_bar->Append(view_menu, wxT("&Visualizações"));
    SetMenuBar(menu_bar);
	
#endif // wxUSE_MENUS

	
#if	(NAVEGADOR_VERSION > 1)
	m_simplePopup = NULL;
#endif

	

	//geal no qual os 3 principais sao incluidos:
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);

	

	int framew=0,frameh=0;
	this->GetSize(&framew,&frameh);
	
	m_firstColumnSize = 300;
	m_thirdColumnSize	=128;
	if(m_useMini){
		m_firstColumnSize = 200;// 136;
		m_thirdColumnSize	=100;
	}
	m_secondColumnSize = framew- m_firstColumnSize - m_thirdColumnSize;

	m_buttonW=60;
	m_buttonH=54;
	if(m_useMini){
		m_buttonW=30;
		m_buttonH=27;
	}
	
	m_firstRowSize = m_buttonH;
	m_thirdRowSize = 128;
	m_secondRowSize = frameh-m_thirdRowSize - m_firstRowSize;

	m_tagSize = 18;
	if(m_useMini){
		m_tagSize = 12;
	}
	
	if(!m_useMini){
		m_comboW = 160;
		m_comboH = 24;
	}
	else{
		m_comboW = 80;
		m_comboH = 18;	
	}

	
	wxColour col1, col2, col3;
	col1.Set(wxT("#FFFFFF"));
	col2.Set(wxT("#CCCCCC"));
	col3.Set(wxT("#DDDDDD"));
	m_panel = new wxPanel(this,0,0,framew,frameh);//,wxEXPAND
	m_panel->SetBackgroundColour(*wxLIGHT_GREY);//col1);

	CreateLeftMainPanItens( );
	m_leftMainPan->SetBackgroundColour(*wxLIGHT_GREY);//col2);
	
	CreateCenterMainPanItens( );
	m_centerMainPan->SetBackgroundColour(*wxLIGHT_GREY);//col3);

	CreateRightMainPanItens( );
	m_rightMainPan->SetBackgroundColour(*wxLIGHT_GREY);//col3);

	CreateStatusBar(2);

	hbox1->Add(m_leftMainPan,2, wxEXPAND);
	hbox1->Add(m_centerMainPan,4, wxEXPAND);
	hbox1->Add(m_rightMainPan,1, wxEXPAND);
	m_panel->SetSizerAndFit(hbox1);

	m_panel->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));

	m_treeCtrl->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
#ifdef	 _DEBUG	
	m_textCtrl->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
#endif	
	m_btMinimizePers->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btMaximizePers->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
#if  (NAVEGADOR_VERSION > 1)		
	m_btOrderByName->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btOrderByStatus->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
#endif	

	m_canvas->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	
	m_textLegenda->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	
	m_btAutoDetect->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btPencil->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btPencil34->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btCursor->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btZoomIn->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btZoomOut->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_btMove->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));

	m_b1Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b2Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b3Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b4Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b5Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b6Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b7Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b8Photo->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	
	m_b1Person->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b2Person->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b3Person->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b4Person->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b5Person->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	m_b6Person->Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	

	/*
	Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard));
	Connect( wxEVT_KEY_DOWN, wxKeyEventHandler(FacesMainFrame::Onkeyboard),NULL, this);	
	Connect(wxEVT_KEY_UP, wxKeyEventHandler(FacesMainFrame::Onkeyboard),NULL, this);
    Connect(wxEVT_CHAR, wxKeyEventHandler(FacesMainFrame::Onkeyboard),NULL, this);
   */
 
	UpdateCursor();

	this->Refresh();
	this->Resize();
	/*
	m_canvas->AcceptFocus(true);
	m_canvas->SetFocus();
	*/
}




FacesMainFrame::~FacesMainFrame()
{
	delete g_ger;

#if wxUSE_LOG
    delete wxLog::SetActiveTarget(NULL);
#endif // wxUSE_LOG
}

void FacesMainFrame::CreateTreeWithDefStyle(int w, int h)
{
    long style = wxTR_DEFAULT_STYLE ;
/*		|
#ifndef NO_VARIABLE_HEIGHT
                 wxTR_HAS_VARIABLE_ROW_HEIGHT |
#endif
              wxTR_EDIT_LABELS;
*/

    CreateTree(style | wxSUNKEN_BORDER, w, h);

}

void FacesMainFrame::CreateTree(long style, int w, int h)
{
	if(m_leftMainPan){
		m_treeCtrl = new MyTreeCtrl(m_leftMainPan, CNavegFGV_Ctrl,wxPoint(0,0),
									wxSize(w,h), style);

		//m_treeCtrl->ExpandAll();
		//m_treeCtrl->SetBestFittingSize();

	}

}


void FacesMainFrame::OnIdle(wxIdleEvent& event)
{
	static bool firstTime = true;
#if wxUSE_STATUSBAR
    if ( m_treeCtrl )
    {
        wxTreeItemId idRoot = m_treeCtrl->GetRootItem();
        wxString status;
        if (idRoot.IsOk())
        {
            wxTreeItemId idLast = m_treeCtrl->GetLastChild(idRoot);
            status = wxString::Format(
                _T("Root/last item is %svisible/%svisible"),
                m_treeCtrl->IsVisible(idRoot) ? _T("") : _T("not "),
                idLast.IsOk() && m_treeCtrl->IsVisible(idLast)
                    ? _T("") : _T("not "));
        }
        else
            status = _T("No root item");

        SetStatusText(status, 1);
		if(firstTime )
			InitDir();
		firstTime =false;
    }
#endif // wxUSE_STATUSBAR

  // 
	event.Skip();
}

void FacesMainFrame::OnSize(wxSizeEvent& event)
{
    if ( m_treeCtrl
#if wxUSE_LOG
	#ifdef _DEBUG
           && m_textCtrl
	#endif
#endif // wxUSE_LOG
                                  )
    {
        Resize();		
    }
	
   // 
	event.Skip();
}

void FacesMainFrame::Resize()
{

	/*
    wxSize size = GetClientSize();
    m_treeCtrl->SetSize(0, 0, size.x, size.y
#if !wxUSE_LOG
                                            );
#else
                                            *2/3);
	m_textCtrl->SetSize(0, 2*size.y/3, size.x, size.y/3);
#endif
	*/
}

void FacesMainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void FacesMainFrame::OnHelp(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxT("Navegador de Cadastro de Personagens Históricos (CPDOC-FGV)\n")
                wxT("VIF: Very important faces"),
                wxT("Help VIF"),
                wxOK | wxICON_INFORMATION, this);
}
void FacesMainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxMessageBox(wxT("Navegador de Cadastro de Personagens Históricos (CPDOC-FGV)\n")
                 wxT("VIF: Very important faces"),
                 wxT("About VIF"),
                 wxOK | wxICON_INFORMATION, this);
}

void FacesMainFrame::DoSort(bool reverse)
{
    wxTreeItemId item = m_treeCtrl->GetSelection();

    CHECK_ITEM( item );

    m_treeCtrl->DoSortChildren(item, reverse);
}




void FacesMainFrame::OnHighlight(wxCommandEvent& WXUNUSED(event))
{
    wxTreeItemId id = m_treeCtrl->GetSelection();

    CHECK_ITEM( id );

    wxRect r;
    if ( !m_treeCtrl->GetBoundingRect(id, r, true /* text, not full row */) )
    {
#ifdef _DEBUG
		wxLogMessage(_T("Failed to get bounding item rect"));
#endif
		
        return;
    }

    wxClientDC dc(m_treeCtrl);
    dc.SetBrush(*wxRED);
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(r);
    m_treeCtrl->Update();
}

void FacesMainFrame::DoSetBold(bool bold)
{
    wxTreeItemId item = m_treeCtrl->GetSelection();

    CHECK_ITEM( item );

    m_treeCtrl->SetItemBold(item, bold);
}




void FacesMainFrame::OnCloseDir(wxCommandEvent& event){
	//falta salvar
	wxTreeItemId item_id, parent_id, parent_parent_id ;
	
	if(m_treeCtrl){
		item_id = m_treeCtrl->GetSelection();

		int level = m_treeCtrl->CheckNodeLevel(item_id);
	
		switch (level){
		 
			case L_ROOT :
				//wxWindowList filhos = m_treeCtrl->GetChildren();
				//emitir uma msg de alerta q vai fechar todos!
				m_treeCtrl->DeleteChildren(m_treeCtrl->m_rootId);
				break;
			case L_DIR  :
				m_treeCtrl->Delete(item_id);
				break;
			case L_PHOTO  :
				parent_id= m_treeCtrl->GetItemParent(item_id);
				m_treeCtrl->Delete(parent_id);
				break;
			case L_FACES  :
				parent_id= m_treeCtrl->GetItemParent(item_id);
				parent_parent_id = m_treeCtrl->GetItemParent(parent_id);
				m_treeCtrl->Delete(parent_parent_id);
				break;

		 }	
	}
}






bool FacesMainFrame::FrameAlterarImagem(const char *imgfile, const char *dir){
	
	static char last_imgfile[128]="";
	static char last_dir[256]="";

	/*Antes de mudar de foto, salva anterior*/	
	g_ger->SaveCurrentPhoto();
	
	//muda a foto so se nao é a mesma:
	if(	imgfile == NULL		||		
		dir == NULL		||
		(strcmp(imgfile, last_imgfile) !=0 )
		|| (strcmp(dir, last_dir) !=0 )){
		g_ger->SetCurrentPhotoByName(imgfile, dir);
		m_canvas->AlterarImagem();
	}
	strcpy_s(last_imgfile, 128, imgfile);
	strcpy_s(last_dir, 256 ,dir) ;
	AtualizaMiniCanvas();
	
	return true;
}


void FacesMainFrame::OnLoadImgFile(wxCommandEvent& event){
// Show file selector.
    wxString f = wxFileSelector(wxT("Open Image"), (const wxChar *) NULL,
                                    (const wxChar *) NULL, wxT("png|bmp|jpg|jpeg|tif|tiff"),
                                    wxT("PNG files (*.png)|*.png|BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif|JPEG files (*.jpg)|*.jpg|TIFF files (*.tif)|*.tif"									
									));

    if (f.empty())
        return;

	//particionar em img e diretorio
	FrameAlterarImagem(f.c_str());

	Refresh();

}

void FacesMainFrame::OnSaveImgFile(wxCommandEvent& event){

	wxString f = wxFileSelector( wxT("Save Image"), (const wxChar *)NULL,
                                 (const wxChar *)NULL,
                                 wxT("png"), wxT("PNG files (*.png)|*.png") );

    if (f.empty())  return;

    wxBitmap *backstore = new wxBitmap( 150, 150 );

    wxMemoryDC memDC;
    memDC.SelectObject( *backstore );
    memDC.Clear();
    memDC.SetBrush( *wxBLACK_BRUSH );
    memDC.SetPen( *wxWHITE_PEN );
    memDC.DrawRectangle( 0, 0, 150, 150 );
    memDC.SetPen( *wxBLACK_PEN );
    memDC.DrawLine( 0, 0, 0, 10 );
    memDC.SetTextForeground( *wxWHITE );
    memDC.DrawText( _T("This is a memory dc."), 10, 10 );

    memDC.SelectObject( wxNullBitmap );

    backstore->SaveFile( f, wxBITMAP_TYPE_PNG, (wxPalette*)NULL );

    delete backstore;
}

void FacesMainFrame::GetDescritores(wxArrayString &as){

	as =  m_combo_descritores->GetStrings();
}
//ex:EGfoto1047_1
void FacesMainFrame::SetLegend(wxString s){

	int i=0, j=0, cod=0, num=0;
	char scod[16], snum[16], c, sigla[18];
	bool isPersonagem;

	
	m_combo_personagens->Clear();
	m_combo_nomes->Clear();
	m_textLegenda->SetLabel("Legenda:");

//retirar: so teste
	wxArrayString as = m_combo_descritores->GetStrings();


	if(s.IsEmpty()){
		return;
	}

	//pula as letras do nome (pos 0 tem uma aspas)
	i=1;
	while (s[i] != '\0' &&  (isalpha(s[i])|| (s[i]>=128 && s[i]<=165) ) ){
		i++;
	}

	j=0;
	while(i<strlen(s) && s[i]!='_'&& s[i]!='.'){
		scod[j]=s[i];
		j++;
		i++;
	}
	scod[j]='\0';
	cod = atoi(scod);
	
	//se ja esta no ponto, nao tem numero, se nao, pula o _
	if(s[i]!='.'){
		i++;//pula _
		j=0;
		while(i<strlen(s) && s[i]!='.'){
			snum[j]=s[i];
			j++;
			i++;
		}
		snum[j]='\0';
		num = atoi(snum);
	}else{
		num = -1;
	}

	int si;
	for(i=0; i<m_legendList.size(); i++){

		if(  m_legendList[i].cod == cod &&  (m_legendList[i].num == num || num==-1))
		{
			/*descobrir a sigla:*/
			si=0;
			do{
				if(toupper(m_legendList[i].sigla[si]) != toupper(s[si+1]) )//s tem aspas
					break;//continue;
				si++;
			}while(m_legendList[i].sigla[si] != '\0' );
			
			
			m_combo_personagens->Clear(); 
			m_combo_nomes->Clear(); 
			wxString leg;
			leg<<"Legenda: "<<m_legendList[i].legenda;
			m_textLegenda->SetLabel(leg);


			wxArrayString s_nomes;
			wxArrayString s_personagens;
			char buf[50] = "", c=' ';
			int l1=0, l2=0;
			
			do{
				l1=0;

				c= m_legendList[i].legendaProcessada[l2];
				while( c==' '|| c==';'|| c=='.')//c !='\n' && c!='\0')
					c= m_legendList[i].legendaProcessada[++l2];

				while( c!=';'
					 && c!='.'
					 && c!='\0')
				{				
					buf[l1] = c;
					l1++;
					l2++;
					c= m_legendList[i].legendaProcessada[l2];
				}
				
				if(buf[0]!= '\0'){
					while(l1>0 && buf[l1-1] == ' ')
						l1--;
					
					if(l1>0 && (buf[l1-1]=='.' ||buf[l1-1]==';')){
						buf[l1-1]='\0';
					}else{
						buf[l1]='\0';
					}
					if(buf[0]!= '\0'){
						if( strcmp(buf,"Ao centro") &&
							strcmp(buf,"Dir") && strcmp(buf,"dir") &&
							strcmp(buf,"Esq") && strcmp(buf,"esq")
						){
						//testar se eh nova
							int r =0;
							isPersonagem = g_ger->isPersonagem(buf);
							if(isPersonagem)
								s_personagens.Add(buf);
							else{
								const wxString cbuf = buf;
								r =m_combo_descritores->FindString( cbuf, true ); 
								if(r>=0)
									s_nomes.Add(buf);
								
							}
							//returns a pointer to the first instance of string s2 in s1.  Returns a NULL pointer if s2 is not encountered in s1.
							if( r<0){
								char* p=0;
								p=strstr( buf, " e ");
								if( p!=NULL ){
									//uso de e no fim da frase
									*p ='\0';
									r =m_combo_descritores->FindString( buf, true ); 
									if(r>=0)
										s_nomes.Add(buf);
									//anda pra frente
									r =m_combo_descritores->FindString( p+3 , true ); 
									if(r>=0)
										s_nomes.Add( p+3 );
								}
							}
						}

					}
				}
			}while( m_legendList[i].legendaProcessada[l2]!='\0' );
	
			if(!s_nomes.IsEmpty()){
				m_combo_nomes->Append(s_nomes);
				//aqui coloca tbm nos personagens se ja ta lendo personagens
			}
			if(!s_personagens.IsEmpty()){
				m_combo_personagens->Append(s_personagens);
				//aqui coloca tbm nos personagens se ja ta lendo personagens
			}


			break;
		}
	}

}


void FacesMainFrame::UpdateDescritorCombo(wxString selDirName){

	Fundo *d=NULL;

	if(m_combo_descritores){
		d=g_ger->GetFundo(selDirName.c_str());
			
		if(d!=NULL){
			m_combo_descritores->UpdateDescritorItens(d);
		}
	}
}
	


void FacesMainFrame::OnBtPersonCheck(wxCommandEvent& event){
	
	int n;	
	wxString s;
	bool fromCaption = true;
	
	//se esta selecionado na lista de nomes livres, usa esse:
	n = m_combo_nomes->GetSelection();	
	if(n>=0 ){		
		s= m_combo_nomes->GetString(n);
		m_combo_nomes->DeleteOneItem(n);
	}else{
				
		//se nao, testo se existe descritor selecionado:
		n = m_combo_descritores->GetSelection();		
		if(n>=0){			
			
			s= m_combo_descritores->GetString(n);

			//se existe na lista de nomes livres, 
			//apaga e passa a usá-lo como personagem, sem precisar perguntar:
			n = m_combo_nomes->FindString(s.c_str(), false);						
			if(n>=0){
				m_combo_nomes->DeleteOneItem(n);		
			}
			//se nao esta na lista de nomes livres, pergunta se ainda assim quer usar,
			
			else{
				
				if(wxMessageBox(wxT("Deseja utilizar este descritor como nome?"), wxT("Atenção"),
					wxICON_QUESTION | wxYES_NO ) == wxYES){
									
					//neste caso estara inserindo informação que nao esta na legenda
					fromCaption = false;
				}			
				else{		
					return;
				}
			}

		}
		//nao eh nome livre, nem descritor, entao ta sem nome
		// testar X nome legenda:
		else{
			wxMessageBox(wxT("Selecione algum nome livre primeiro."), wxT("Erro"), wxOK | wxICON_EXCLAMATION );
			return;
		}
	}

	
	n = m_combo_personagens->FindString(s.c_str(), false);
	if(n<0)		
		n = m_combo_personagens->Append(s);
	m_combo_personagens->Select( n );

	g_ger->CheckBB(s.c_str());
	m_treeCtrl->AtualizaBBValidas(g_ger->GetCurrentPhoto());	
	m_treeCtrl->SelFaceByName(s);
	m_canvas->Refresh();
	//UpdateComboItemSelectedByName	
					
}
void FacesMainFrame::OnBtPersonDelete(wxCommandEvent& event){
	//colocar de novo o nome livre:

	int n;
	n = m_combo_personagens->GetSelection();
	if(n >=0){
		wxString s= m_combo_personagens->GetString(n);//GetStringSelection();
		m_combo_personagens->DeleteOneItem(n);
		m_combo_personagens->Select(-1);

		n = m_combo_nomes->Append(s);
		m_combo_nomes->Select(-1);
	}

	g_ger->DeleteBB();
	
	
	m_treeCtrl->AtualizaBBValidas(g_ger->GetCurrentPhoto());		
		
	AtualizaMiniCanvas();
	m_canvas->Refresh();

	const char * s = g_ger->GetCurrentPhotoBBName();
	n = m_combo_personagens->FindString(s);
	m_combo_personagens->Select( n );
}



void FacesMainFrame::OnBtPersonPrevious(wxCommandEvent& event){
	m_treeCtrl->SelPrevFace();
	/*
	g_ger->PreviousBB();
	AtualizaMiniCanvas();
	m_canvas->Refresh();
	*/
}
void FacesMainFrame::OnBtPersonNext(wxCommandEvent& event){
	
	m_treeCtrl->SelNextFace();
	/*
	g_ger->NextBB();
	AtualizaMiniCanvas();
	m_canvas->Refresh();
	*/
}
void FacesMainFrame::OnBtPersonFirst(wxCommandEvent& event){
	m_treeCtrl->SelFirstFace();
	/*
	g_ger->FirstBB();
	AtualizaMiniCanvas();
	m_canvas->Refresh();
	*/
}
void FacesMainFrame::OnBtPersonLast(wxCommandEvent& event){
	m_treeCtrl->SelLastFace();
	/*
	g_ger->LastBB();
	AtualizaMiniCanvas();
	m_canvas->Refresh();
	*/
}


void FacesMainFrame::UpdateCursor(void){

	const static wxColor oldColor= m_btPencil->GetBackgroundColour();
	const wxColor selectionColor(wxColor(150,150,150,30));
	
	//wxBackgroundStyle	m_btCursor->SetBackgroundStyle(

	m_btCursor->SetBackgroundColour(oldColor);
	m_btAutoDetect->SetBackgroundColour(oldColor);
	m_btMove->SetBackgroundColour(oldColor);
	m_btZoomOut->SetBackgroundColour(oldColor);
	m_btZoomIn->SetBackgroundColour(oldColor);
	m_btPencil->SetBackgroundColour(oldColor);
	m_btPencil34->SetBackgroundColour(oldColor);
	

	switch(m_selectedCursor){
	
		case CUR_DEFAULT:
			SetCursor(*	wxSTANDARD_CURSOR);
			m_btCursor->SetBackgroundColour(selectionColor);
			break;
		case CUR_MOVE:
			SetCursor(*	m_curMove);		
			m_btMove->SetBackgroundColour(selectionColor);
			break;
		case CUR_ZOOMOUT:
			SetCursor(*m_curZoomOut);
			m_btZoomOut->SetBackgroundColour(selectionColor);
			break;
		case CUR_ZOOMIN:
			SetCursor(*m_curZoomIn);
			m_btZoomIn->SetBackgroundColour(selectionColor);
			break;
		case CUR_EDIT:
			SetCursor(*m_curPencil);//*wxCROSS_CURSOR);
			m_btPencil->SetBackgroundColour(selectionColor);
			break;
		case CUR_EDIT34:
			SetCursor(*m_curPencil34);//*wxCROSS_CURSOR);
			m_btPencil34->SetBackgroundColour(selectionColor);
			break;
		default:
			m_selectedCursor =CUR_DEFAULT;
			m_btCursor->SetBackgroundColour(selectionColor);
			SetCursor(*	wxSTANDARD_CURSOR);
			break;
	}

/*
Para mudar a imagem
m_btCursor->SetBitmapLabel( wxBitmap(wxT("icones/Move.png"), 
		wxBITMAP_TYPE_PNG));
*/
}
	

void FacesMainFrame::OnBtZoomOut(wxCommandEvent& event){
	if(m_canvas==NULL || !(m_canvas->hasBitmap())){
	
		wxMessageBox(wxT("Abra alguma fotografia primeiro."), 
			wxT("Operação Inválida"),wxOK | wxICON_EXCLAMATION,this);
		return;
	}
	m_selectedCursor = CUR_ZOOMOUT;
	UpdateCursor();
}
void FacesMainFrame::OnBtZoomIn(wxCommandEvent& event){
	if(m_canvas==NULL || !(m_canvas->hasBitmap())){
	
		wxMessageBox(wxT("Abra alguma fotografia primeiro."), 
			wxT("Operação Inválida"),wxOK | wxICON_EXCLAMATION,this);
		return;
	}
	m_selectedCursor = CUR_ZOOMIN;
	UpdateCursor();
}




void FacesMainFrame::OnBtDefautCursor(wxCommandEvent& event){
	m_selectedCursor = CUR_DEFAULT;
	UpdateCursor();
}

void FacesMainFrame::OnBtMoveCursor(wxCommandEvent& event){
	m_selectedCursor = CUR_MOVE;
	UpdateCursor();
}


void FacesMainFrame::OnBtAutoDetect(wxCommandEvent& event){

	if( m_canvas==NULL || !(m_canvas->hasBitmap()) ){
		wxMessageBox(wxT("Abra alguma fotografia primeiro."), 
			wxT("Operação Inválida"),wxOK | wxICON_EXCLAMATION,this);
		return;
	}
	g_ger->DetectFaces();
	m_canvas->Refresh();
	/**/
	m_selectedCursor = CUR_DEFAULT;
	UpdateCursor();
	
}
void FacesMainFrame::OnBtPersonDraw(wxCommandEvent& event){

	if(m_canvas==NULL || !(m_canvas->hasBitmap())){
	
		wxMessageBox(wxT("Abra alguma fotografia primeiro."), 
			wxT("Operação Inválida"),wxOK | wxICON_EXCLAMATION,this);
		return;
	}
	m_selectedCursor = CUR_EDIT;
	UpdateCursor();
}
void FacesMainFrame::OnBtPersonDraw34(wxCommandEvent& event){

	if(m_canvas==NULL || !(m_canvas->hasBitmap())){
	
		wxMessageBox(wxT("Abra alguma fotografia primeiro."), 
			wxT("Operação Inválida"),wxOK | wxICON_EXCLAMATION,this);
		return;
	}
	m_selectedCursor = CUR_EDIT34;
	UpdateCursor();
}

void FacesMainFrame::AtualizaMiniCanvas(void){
	m_miniCanvas->AlterarImagem();
	m_miniCanvas->Refresh();
}



void FacesMainFrame::AtualizaSelecaoArvore(const char * bbName){

	m_treeCtrl->SelFaceByName(bbName);

}







void FacesMainFrame::OnDetectFaces(wxCommandEvent& event){

	if(event.IsChecked()){
		g_ger->m_DoFaceDetection= true;
		//repassar o detector de faces
	}else{
		g_ger->m_DoFaceDetection= false;
	}

}

void FacesMainFrame::OnDetectPersonagens(wxCommandEvent& event){

}

void FacesMainFrame::OnViewPersonagens(wxCommandEvent& event){
	if(event.IsChecked()){
		g_ger->m_ShowPersonagensBB= true;
		//repassar o detector de faces
	}else{
		g_ger->m_ShowPersonagensBB= false;
	}
	m_canvas->Refresh();
}

void FacesMainFrame::OnViewFaces(wxCommandEvent& event){
	
	if(event.IsChecked()){
		g_ger->m_ShowFacesBB= true;
		//repassar o detector de faces
	}else{
		g_ger->m_ShowFacesBB= false;
	}
	m_canvas->Refresh();
}
    

void FacesMainFrame::OnBtPhotoCheck(wxCommandEvent& event){
	g_ger->ValidaFoto();
	//m_treeCtrl->AtualizaBBValidas(g_ger->GetCurrentPhoto());	
	m_treeCtrl->AtualizaFotoAprovada();	

	m_canvas->Refresh();
	
	AtualizaMiniCanvas();

}
void FacesMainFrame::OnBtPhotoDelete(wxCommandEvent& event){
	wxString strMsg;
	strMsg.Printf(_("Deseja apagar a marcação VIF da imagem?")); 	//('%s')"), m_lastDir);	
	if( wxMessageBox(strMsg, _("Question"), wxICON_QUESTION | wxYES_NO ) == wxYES){
		
	g_ger->DesfazMarcacaoFoto();	
	m_treeCtrl->AtualizaFotoDesmarcada();	
	
	//while( m_combo_personagens->GetString
	wxArrayString ss= m_combo_personagens->GetStrings();
	m_combo_personagens->Clear();
	for(int i=0; i<ss.size(); i++)
		m_combo_nomes->Append(ss[i]);
	


	m_canvas->Refresh();
	AtualizaMiniCanvas();
	}
}
void FacesMainFrame::OnBtPhotoApprove(wxCommandEvent& event){

	wxMessageBox(wxT("Marcação de aprovação exclusiva ao modo administrador."));
	//if( wxMessageBox(strMsg, _("Question"), wxICON_QUESTION | wxYES_NO ) == wxYES)
#if  (NAVEGADOR_VERSION > 1)
	//fazer autenticacao :

	g_ger->RevisaFoto();
	m_treeCtrl->AtualizaFotoRevisada();	
	m_canvas->Refresh();
	AtualizaMiniCanvas();

#endif
}
void FacesMainFrame::OnBtPhotoInprogress(wxCommandEvent& event){
	//marca como em analise de novo g_ger->
	g_ger->DesfazValidaFoto();	
	m_treeCtrl->AtualizaFotoDesaprovada();	
}

void FacesMainFrame::OnBtPhotoPrevious(wxCommandEvent& event){
	m_treeCtrl->SelPrev();
}

void FacesMainFrame::OnBtPhotoNext(wxCommandEvent& event){
	m_treeCtrl->SelNext();
}

void FacesMainFrame::OnBtPhotoFirst(wxCommandEvent& event){
	m_treeCtrl->SelFirst();
}

void FacesMainFrame::OnBtPhotoLast(wxCommandEvent& event){
	m_treeCtrl->SelLast();
}

void FacesMainFrame::OnBtCollapseFaces(wxCommandEvent& event){
	m_treeCtrl->CollapseFaces();
}

void FacesMainFrame::OnBtExpandFaces(wxCommandEvent& event){
	m_treeCtrl->ExpandFaces();
}

void FacesMainFrame::UpdateComboItemSelectedByName(wxString name){
	//m_combo_personagens->DoGetItemClientData
	int n = m_combo_personagens->FindString(name.c_str(), false);
	//	if(n>=0)
	m_combo_personagens->SetSelection(n);

	n = m_combo_nomes->FindString(name.c_str(), false);
	//if(n>=0)		
	m_combo_nomes->SetSelection(n);
	

	n = m_combo_descritores->FindString(name.c_str(), false);
	//if(n>=0)		
	m_combo_descritores->SetSelection(n);
}

void FacesMainFrame::UpdateBBSelectedByName(wxString name){
	
	//aqui:
	g_ger->SelectBBforName(name.c_str());
	
	m_canvas->Refresh();
	AtualizaMiniCanvas();
}



/*
comandos:
	GetKeyName(event),
    event.GetKeyCode(),
    event.ControlDown() ? 'C' : '-',
    event.AltDown()     ? 'A' : '-',
    event.ShiftDown()   ? 'S' : '-',
*/
void FacesMainFrame::Onkeyboard( wxKeyEvent& event){
	wxString key;
	long keycode = event.GetKeyCode();
	wxCommandEvent  event2;
	
#ifdef _DEBUG
	LogKeyEvent(wxT("key down "), event );
#endif

    switch ( keycode )
    {
		case WXK_NUMPAD_LEFT:
		case WXK_LEFT:
			key = wxT("NUMPAD_LEFT"); 
			if( event.ShiftDown() ){
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->m_treeCtrl->SelFirst();
			}
			else{				
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->m_treeCtrl->SelPrev();
			}								
			break;
            
		case WXK_NUMPAD_RIGHT: 
		case WXK_RIGHT:
			key = wxT("NUMPAD_RIGHT");
			if( event.ShiftDown() ){
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->m_treeCtrl->SelLast();
			}
			else{				
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->m_treeCtrl->SelNext();
			}
			break;



		case WXK_ADD: key = wxT("ADD"); break;
        case WXK_SEPARATOR: key = wxT("SEPARATOR"); break;
        case WXK_SUBTRACT: key = wxT("SUBTRACT"); break;
        case WXK_DECIMAL: key = wxT("DECIMAL"); break;
        case WXK_DIVIDE: key = wxT("DIVIDE"); break;
        case WXK_F1: key = wxT("F1"); break;
			
		case 'V':case 'v':
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtMoveCursor(event2);
		break;
			
		case 'S':case 's':
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtDefautCursor(event2);
		break;

			
		case 'D':case 'd':
			//3x4:
			if(event.ControlDown() && event.ShiftDown()){
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtAutoDetect(event2);
			}else if(event.ControlDown()){
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtPersonDraw34(event2);
			}
			else{
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtPersonDraw(event2);
			}
		break;

			
		case 'Z':case 'z':
			//in X out:
			if(event.ControlDown()){
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtZoomOut(event2);			
			}
			else{
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtZoomIn(event2);
			}
		break;



		case WXK_RETURN: case WXK_NUMPAD_ENTER: 
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtPhotoCheck(event2);
		
		break;

		case  WXK_NUMPAD_DELETE: case  WXK_DELETE :

			((FacesMainFrame *)FacesApp::getFacesMainFrame())->OnBtPersonDelete(event2);
		break;

	}
	
}
	




void LogKeyEvent(const wxChar *name, const wxKeyEvent& event)
{
    wxString key;
    long keycode = event.GetKeyCode();
    {
        switch ( keycode )
        {
            case WXK_BACK: key = wxT("BACK"); break;
            case WXK_TAB: key = wxT("TAB"); break;
            case WXK_RETURN: key = wxT("RETURN"); break;
            case WXK_ESCAPE: key = wxT("ESCAPE"); break;
            case WXK_SPACE: key = wxT("SPACE"); break;
            case WXK_DELETE: key = wxT("DELETE"); break;
            case WXK_START: key = wxT("START"); break;
            case WXK_LBUTTON: key = wxT("LBUTTON"); break;
            case WXK_RBUTTON: key = wxT("RBUTTON"); break;
            case WXK_CANCEL: key = wxT("CANCEL"); break;
            case WXK_MBUTTON: key = wxT("MBUTTON"); break;
            case WXK_CLEAR: key = wxT("CLEAR"); break;
            case WXK_SHIFT: key = wxT("SHIFT"); break;
            case WXK_ALT: key = wxT("ALT"); break;
            case WXK_CONTROL: key = wxT("CONTROL"); break;
            case WXK_MENU: key = wxT("MENU"); break;
            case WXK_PAUSE: key = wxT("PAUSE"); break;
            case WXK_CAPITAL: key = wxT("CAPITAL"); break;
            case WXK_END: key = wxT("END"); break;
            case WXK_HOME: key = wxT("HOME"); break;
            case WXK_LEFT: key = wxT("LEFT"); break;
            case WXK_UP: key = wxT("UP"); break;
            case WXK_RIGHT: key = wxT("RIGHT"); break;
            case WXK_DOWN: key = wxT("DOWN"); break;
            case WXK_SELECT: key = wxT("SELECT"); break;
            case WXK_PRINT: key = wxT("PRINT"); break;
            case WXK_EXECUTE: key = wxT("EXECUTE"); break;
            case WXK_SNAPSHOT: key = wxT("SNAPSHOT"); break;
            case WXK_INSERT: key = wxT("INSERT"); break;
            case WXK_HELP: key = wxT("HELP"); break;
            case WXK_NUMPAD0: key = wxT("NUMPAD0"); break;
            case WXK_NUMPAD1: key = wxT("NUMPAD1"); break;
            case WXK_NUMPAD2: key = wxT("NUMPAD2"); break;
            case WXK_NUMPAD3: key = wxT("NUMPAD3"); break;
            case WXK_NUMPAD4: key = wxT("NUMPAD4"); break;
            case WXK_NUMPAD5: key = wxT("NUMPAD5"); break;
            case WXK_NUMPAD6: key = wxT("NUMPAD6"); break;
            case WXK_NUMPAD7: key = wxT("NUMPAD7"); break;
            case WXK_NUMPAD8: key = wxT("NUMPAD8"); break;
            case WXK_NUMPAD9: key = wxT("NUMPAD9"); break;
            case WXK_MULTIPLY: key = wxT("MULTIPLY"); break;
            case WXK_ADD: key = wxT("ADD"); break;
            case WXK_SEPARATOR: key = wxT("SEPARATOR"); break;
            case WXK_SUBTRACT: key = wxT("SUBTRACT"); break;
            case WXK_DECIMAL: key = wxT("DECIMAL"); break;
            case WXK_DIVIDE: key = wxT("DIVIDE"); break;
            case WXK_F1: key = wxT("F1"); break;
            case WXK_F2: key = wxT("F2"); break;
            case WXK_F3: key = wxT("F3"); break;
            case WXK_F4: key = wxT("F4"); break;
            case WXK_F5: key = wxT("F5"); break;
            case WXK_F6: key = wxT("F6"); break;
            case WXK_F7: key = wxT("F7"); break;
            case WXK_F8: key = wxT("F8"); break;
            case WXK_F9: key = wxT("F9"); break;
            case WXK_F10: key = wxT("F10"); break;
            case WXK_F11: key = wxT("F11"); break;
            case WXK_F12: key = wxT("F12"); break;
            case WXK_F13: key = wxT("F13"); break;
            case WXK_F14: key = wxT("F14"); break;
            case WXK_F15: key = wxT("F15"); break;
            case WXK_F16: key = wxT("F16"); break;
            case WXK_F17: key = wxT("F17"); break;
            case WXK_F18: key = wxT("F18"); break;
            case WXK_F19: key = wxT("F19"); break;
            case WXK_F20: key = wxT("F20"); break;
            case WXK_F21: key = wxT("F21"); break;
            case WXK_F22: key = wxT("F22"); break;
            case WXK_F23: key = wxT("F23"); break;
            case WXK_F24: key = wxT("F24"); break;
            case WXK_NUMLOCK: key = wxT("NUMLOCK"); break;
            case WXK_SCROLL: key = wxT("SCROLL"); break;
            case WXK_PAGEUP: key = wxT("PAGEUP"); break;
            case WXK_PAGEDOWN: key = wxT("PAGEDOWN"); break;
            case WXK_NUMPAD_SPACE: key = wxT("NUMPAD_SPACE"); break;
            case WXK_NUMPAD_TAB: key = wxT("NUMPAD_TAB"); break;
            case WXK_NUMPAD_ENTER: key = wxT("NUMPAD_ENTER"); break;
            case WXK_NUMPAD_F1: key = wxT("NUMPAD_F1"); break;
            case WXK_NUMPAD_F2: key = wxT("NUMPAD_F2"); break;
            case WXK_NUMPAD_F3: key = wxT("NUMPAD_F3"); break;
            case WXK_NUMPAD_F4: key = wxT("NUMPAD_F4"); break;
            case WXK_NUMPAD_HOME: key = wxT("NUMPAD_HOME"); break;
        
           
			case WXK_NUMPAD_UP: key = wxT("NUMPAD_UP"); break;
            case WXK_NUMPAD_DOWN: key = wxT("NUMPAD_DOWN"); break;



            case WXK_NUMPAD_PAGEUP: key = wxT("NUMPAD_PAGEUP"); break;
            case WXK_NUMPAD_PAGEDOWN: key = wxT("NUMPAD_PAGEDOWN"); break;
            case WXK_NUMPAD_END: key = wxT("NUMPAD_END"); break;
            case WXK_NUMPAD_BEGIN: key = wxT("NUMPAD_BEGIN"); break;
            case WXK_NUMPAD_INSERT: key = wxT("NUMPAD_INSERT"); break;
            case WXK_NUMPAD_DELETE: key = wxT("NUMPAD_DELETE"); break;
            case WXK_NUMPAD_EQUAL: key = wxT("NUMPAD_EQUAL"); break;
            case WXK_NUMPAD_MULTIPLY: key = wxT("NUMPAD_MULTIPLY"); break;
            case WXK_NUMPAD_ADD: key = wxT("NUMPAD_ADD"); break;
            case WXK_NUMPAD_SEPARATOR: key = wxT("NUMPAD_SEPARATOR"); break;
            case WXK_NUMPAD_SUBTRACT: key = wxT("NUMPAD_SUBTRACT"); break;
            case WXK_NUMPAD_DECIMAL: key = wxT("NUMPAD_DECIMAL"); break;

            default:
            {
               if ( keycode < 128 && wxIsprint((int)keycode) )
                   key.Printf(wxT("'%c'"), (char)keycode);
               else if ( keycode > 0 && keycode < 27 )
                   key.Printf(_("Ctrl-%c"), wxT('A') + keycode - 1);
               else
                   key.Printf(wxT("unknown (%ld)"), keycode);
            }
        }
    }

    
#ifdef _DEBUG
	wxLogMessage( wxT("%s event: %s (flags = %c%c%c%c)"),
                  name,
                  key.c_str(),
                  event.ControlDown() ? wxT('C') : wxT('-'),
                  event.AltDown() ? wxT('A') : wxT('-'),
                  event.ShiftDown() ? wxT('S') : wxT('-'),
                  event.MetaDown() ? wxT('M') : wxT('-'));
#endif
}




#if   (NAVEGADOR_VERSION > 1)

void FacesMainFrame::OnBtSortByStatus( wxCommandEvent& event ){
	static bool reverse = true;
	reverse = !reverse;
	m_treeCtrl->DoSortByStatus( reverse );
}

void FacesMainFrame::OnBtSortByName( wxCommandEvent& event ){
	static bool reverse = true;
	reverse = !reverse;
	m_treeCtrl->DoSortByName( reverse );
}

void FacesMainFrame::OnSearch_BEGIN_LABEL_EDIT(wxListEvent& event) 
{ 
	static int cnt = 0;
	wxArrayString strings;
	wxListItem li = event.GetItem();
	long idx = event.GetIndex();
	
	m_listbox_search->SetCurrentIndex(idx);

	//event.Skip();

	/*Se o texto veio vazio ~e nova entrada se nao eh edicao*/

	
	/*
	wxString msg = wxString::Format("Selected : %d %s %s", event.GetIndex(), li.GetText(), ((wxEditableListBox*)m_listbox_search)->GetLabel());
    wxMessageBox(msg, "ListBox begin", wxOK | wxICON_INFORMATION, this); 
	
((wxEditableListBox*)m_listbox_search)->GetStrings(strings);
	if(li.GetText().IsEmpty()){
		wxString testestr = wxString::Format("teste: %d", cnt);
		strings.Add( testestr );//
		cnt++;
	}else{
		strings[idx].sprintf("troca");
	}
	((wxEditableListBox*)m_listbox_search)->SetStrings(strings);	
	*/

	//(((wxEditableListBox*)m_listbox_search)->GetListCtrl())->DoBind...
	
	OnStartSimplePopup(event);

	
	
}

void FacesMainFrame::OnSearch_ITEM_DELETED(wxListEvent& event) 
{ 
   wxString msg = wxString::Format("Selected : %d", event.GetIndex());
    wxMessageBox(msg, "ListBox ITEM DELETED", wxOK | wxICON_INFORMATION, this); 
}
/*

void FacesMainFrame::OnSearch_ITEM_DELETEDbt(wxCommandEvent& event){

}

void FacesMainFrame::OnSearch_END_LABEL_EDIT_txt(wxCommandEvent& event) 
{ 
	wxString msg = wxString::Format("Selected : %d", event.GetSelection());
    wxMessageBox(msg, "ListBox end txt", wxOK | wxICON_INFORMATION, this); 
}

void FacesMainFrame::OnSearch_END_LABEL_EDIT(wxListEvent& event) 
{ 
   wxString msg = wxString::Format("Selected : %d", event.GetIndex());
    wxMessageBox(msg, "ListBox end", wxOK | wxICON_INFORMATION, this); 
}
void FacesMainFrame::OnSearch_INSERT_ITEM(wxListEvent& event) 
{ 
   wxString msg = wxString::Format("Selected : %d", event.GetIndex());
    wxMessageBox(msg, "ListBox insert", wxOK | wxICON_INFORMATION, this); 
}
void FacesMainFrame::OnSearch_ITEM_SELECTED(wxListEvent& event) 
{ 
   wxString msg = wxString::Format("Selected : %d", event.GetIndex());
    wxMessageBox(msg, "ListBox selected", wxOK | wxICON_INFORMATION, this); 
}


void FacesMainFrame::OnLMouseClick( wxMouseEvent& event)
{ 
   wxString msg = wxString::Format("Selected : %d", event.GetButton());
    wxMessageBox(msg, "ListBox selected", wxOK | wxICON_INFORMATION, this); 
}
*/

 
void  FacesMainFrame::OnStartSimplePopup(wxCommandEvent& event)
{
	
	if(m_simplePopup==NULL || ( ! m_simplePopup->IsEnabled())){
		
		delete m_simplePopup;
		m_simplePopup = new SimpleTransientPopup( this);//->GetParent() );
		wxWindow *btn = (wxWindow*) event.GetEventObject();
		wxPoint pos = btn->ClientToScreen( wxPoint(0,0) );
		pos.x=0;
		wxSize sz = btn->GetSize();
		m_simplePopup->Position( pos, sz );
		m_simplePopup->Popup();

	}
} 


void   FacesMainFrame::AddSearchFilter(wxString s){
/*
// Gets the item text
wxString GetItemText(long item, int col = 0) const;
// Sets the item text
void SetItemText(long item, const wxString& str);
*/
	long idx = m_listbox_search->GetCurrentIndex();
	
	wxArrayString strings;
	((wxEditableListBox*)m_listbox_search)->GetStrings(strings);
	
	if(idx <strings.size()){

		(((wxEditableListBox*)m_listbox_search)->GetListCtrl())->SetItemText(idx, s);
		//para ver se fechar edicao
	}
	else{
		(((wxEditableListBox*)m_listbox_search)->GetListCtrl())->InsertItem(idx, s);
		/*
		strings.Add(s);
		((wxEditableListBox*)m_listbox_search)->SetStrings(strings);
		*/
	}
	m_listbox_search->SetCurrentIndex(idx+1);
}

#endif //versao 2