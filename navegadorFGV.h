#ifndef _NAVEGADOR_FGV_
#define _NAVEGADOR_FGV_

#include <vector>

#include "wx/wx.h"

/*
#include "wx/listbox.h"
#include "wx/listctrl.h"
#include "wx/editlbox.h"
*/


#include "wx/treectrl.h"

/*
#include "wx/combo.h"
#include "wx/odcombo.h"
*/
#include "defs.h"

#include "menuAndControlsIds.h"
#include "legenda.h"
#include "arvoreFundos.h"
#include "canvas.h"
#include "canvasFace.h"
#include "comboDescritores.h"
#include "comboPersonagens.h"
#include "hintTexts.h"
#if (NAVEGADOR_VERSION > 1)
#include "searchPersonagens.h"
#endif



// Define a new frame
class CanvasFoto;
class CanvasFace;
class MyTreeItemData;
class MyTreeCtrl;
class SimpleTransientPopup;


void LogKeyEvent(const wxChar *name, const wxKeyEvent& event);


class FacesApp : public wxApp
{
public:
    FacesApp(){ m_showImages = true; m_showButtons = false; }


    bool OnInit();
    void SetShowImages(bool show) { m_showImages = show; }
    bool ShowImages() const { return m_showImages; }

    void SetShowButtons(bool show) { m_showButtons = show; }
    bool ShowButtons() const { return m_showButtons; }

	static FacesApp *getFacesApp(){return (FacesApp *)GetInstance();};
	static wxFrame* getFacesMainFrame();

private:
	static wxFrame* m_frame;
	bool m_showImages, m_showButtons;
};



// Define a new frame type
class FacesMainFrame: public wxFrame
{
public:

    // ctor and dtor
    FacesMainFrame(const wxString& title, int x, int y, int w, int h);
    
	virtual ~FacesMainFrame();

	static CanvasFoto *m_canvas;
	static CanvasFace *m_miniCanvas;
	static wxTextCtrl* m_textLegenda;
	
	void AtualizaMiniCanvas(void);	

	void AtualizaSelecaoArvore(const char * bbName);


    // menu callbacks
    void OnQuit(wxCommandEvent& event);
	void OnHelp(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

	//Diretorios:
	void OnLoadDir(wxCommandEvent& event);
	
	void OnCloseDir(wxCommandEvent& event);
		
	//Images:
	void OnLoadImgFile(wxCommandEvent& event);
    void OnSaveImgFile(wxCommandEvent& event);
    
	//menu Faces:
	void OnViewPersonagens(wxCommandEvent& event);
	void OnViewFaces(wxCommandEvent& event);    
	void OnDetectFaces(wxCommandEvent& event);
	void OnDetectPersonagens(wxCommandEvent& event);

    void OnResetStyle(wxCommandEvent& WXUNUSED(event)){ /*CreateTreeWithDefStyle();*/ }
    void OnHighlight(wxCommandEvent& event);
    //void OnCollapseAndReset(wxCommandEvent& event);
    void OnCount(wxCommandEvent& event);
    void OnCountRec(wxCommandEvent& event);

    void OnSort(wxCommandEvent& WXUNUSED(event)) { DoSort(); }
    void OnSortRev(wxCommandEvent& WXUNUSED(event)) { DoSort(true); }

	
#if   (NAVEGADOR_VERSION > 1)
	void OnBtSortByStatus( wxCommandEvent& event );
	void OnBtSortByName( wxCommandEvent& event );

	/*
	void OnSearch_ITEM_SELECTED(	wxListEvent& event) ;
	void OnSearch_END_LABEL_EDIT(	wxListEvent& event) ;
	void OnSearch_INSERT_ITEM(		wxListEvent& event) ;
	void OnSearch_ITEM_DELETEDbt(wxCommandEvent& event);
	void OnSearch_END_LABEL_EDIT_txt(wxCommandEvent& event);
	void OnLMouseClick( wxMouseEvent& event);
	*/
	void OnSearch_BEGIN_LABEL_EDIT(	wxListEvent& event) ;
	void OnSearch_ITEM_DELETED(		wxListEvent& event) ;
	

	void OnStartSimplePopup(wxCommandEvent& event);
	
	void AddSearchFilter(wxString s);

#endif	


    void OnInsertItem(wxCommandEvent& event);
    void OnIdle(wxIdleEvent& event);
    void OnSize(wxSizeEvent& event);

	void OnBtPhotoPrevious(wxCommandEvent& event);
	void OnBtPhotoNext(wxCommandEvent& event);
	void OnBtPhotoFirst(wxCommandEvent& event);
	void OnBtPhotoLast(wxCommandEvent& event);

	void OnBtPhotoCheck(wxCommandEvent& event);
	void OnBtPhotoInprogress(wxCommandEvent& event);
	void OnBtPhotoDelete(wxCommandEvent& event);
	void OnBtPhotoApprove(wxCommandEvent& event);

	void OnBtCollapseFaces(wxCommandEvent& event);
	void OnBtExpandFaces(wxCommandEvent& event);
	
	void OnBtPersonCheck(wxCommandEvent& event);
	void OnBtPersonDelete(wxCommandEvent& event);
	void OnBtPersonPrevious(wxCommandEvent& event);
	void OnBtPersonNext(wxCommandEvent& event);
	void OnBtPersonFirst(wxCommandEvent& event);
	void OnBtPersonLast(wxCommandEvent& event);

	void UpdateCursor(void);
	void OnBtDefautCursor(wxCommandEvent& event);
	void OnBtMoveCursor(wxCommandEvent& event);
	void OnBtAutoDetect(wxCommandEvent& event);
	void OnBtPersonDraw(wxCommandEvent& event);
	void OnBtPersonDraw34(wxCommandEvent& event);
	void OnBtZoomIn(wxCommandEvent& event);
	void OnBtZoomOut(wxCommandEvent& event);

	void OnEraseBackGround(wxEraseEvent& event) {};

	void UpdateDescritorCombo(wxString selDirName);

	void Onkeyboard( wxKeyEvent& event);

	void UpdateBBSelectedByName(wxString name);
	void UpdateComboItemSelectedByName(wxString name);

	void GetDescritores(wxArrayString & as);
	void SetLegend(wxString s);
	bool FrameAlterarImagem(const char *imgname, const char *dir=NULL);
	
	void InitDir(void );

private:
	
	bool m_useMini ;
	int m_buttonW , m_buttonH;
	int m_comboW, m_comboH;
	int m_firstColumnSize, m_secondColumnSize, m_thirdColumnSize;
	int m_firstRowSize, m_secondRowSize, m_thirdRowSize;
	int m_tagSize;


	cursorType m_selectedCursor;
	
	static std::vector<tlegenda> m_legendList;

	char m_lastDir[256];	
	
	void ProcessLoadDir(const char * f );

    void DoSort(bool reverse = false);
    void Resize();
    void CreateTreeWithDefStyle( int w, int h);
    void CreateTree(long style, int w, int h);

	void CreateLeftMainPanItens( void);
	void CreateCenterMainPanItens( void);
	void CreateRightMainPanItens(void);

    wxPanel *m_panel, *m_leftMainPan, *m_centerMainPan, *m_centerPanCmds, *m_centerPanLeg,
		*m_rightMainPan, 
		*m_rightMainPanUp, *m_rightMainPanCombos, *m_rightMainPanPerson, 
		*m_rightMainPanCursor,*m_rightMainPanPhoto, *m_rightMainPanTagging;
    wxPanel *m_panelLegenda;

    static MyTreeCtrl *m_treeCtrl;

	
	static tComboDescritores 	*m_combo_descritores; 
	// 
	static tComboPersonagens *m_combo_personagens;
	static tComboPersonagens *m_combo_nomes;
#if (NAVEGADOR_VERSION > 1)
	//static wxEditableListBox	
	static	SearchPeople	*m_listbox_search;
	//	wxArrayString   m_arrItems;
#endif
	wxBitmapButton *m_btMinimizePers,*m_btMaximizePers,
#if (NAVEGADOR_VERSION > 1)		
		*m_btOrderByName, *m_btOrderByStatus,
#endif		
		* m_btAutoDetect, * m_btPencil,* m_btPencil34,*m_btCursor, *m_btZoomIn, *m_btZoomOut, *m_btMove;

	wxBitmapButton *m_b1Photo , *m_b2Photo , *m_b3Photo , *m_b4Photo , *m_b5Photo, *m_b6Photo, *m_b7Photo, *m_b8Photo;	
	wxBitmapButton *m_b1Person , *m_b2Person , *m_b3Person , *m_b4Person ,*m_b5Person , *m_b6Person ;


	wxCursor *m_curPencil,*m_curPencil34,*m_curDefault,
		*m_curZoomIn,*m_curZoomOut,
		*m_curHand,*m_curDrag, *m_curMove;

#if wxUSE_LOG
//#ifdef _DEBUG
    wxTextCtrl *m_textCtrl;
//#endif
#endif // wxUSE_LOG

	
	void DoSetBold(bool bold = true);

#if (NAVEGADOR_VERSION > 1)		
	SimpleTransientPopup *m_simplePopup;
#endif
	
	DECLARE_EVENT_TABLE()
	public:
		cursorType getSelectedCursor(void){return m_selectedCursor;}
    
};





#endif