#ifndef _NFGV_ARVORE_FUNDOS
#define _NFGV_ARVORE_FUNDOS

#include "wx/treectrl.h"
#include "wx/wx.h"

#include "fundo.h"
#include "defs.h"


#define USE_GENERIC_TREECTRL 0

#if USE_GENERIC_TREECTRL
#include "wx/generic/treectlg.h"
#ifndef wxTreeCtrl
#define wxTreeCtrl wxGenericTreeCtrl
#define sm_classwxTreeCtrl sm_classwxGenericTreeCtrl
#endif
#endif


// verify that the item is ok and insult the user if it is not
#define CHECK_ITEM( item ) if ( !item.IsOk() ) {                                 \
                             wxMessageBox(wxT("Por favor, selecione algum item primeiro!"), \
                                          wxT("Erro"),              \
                                          wxOK | wxICON_EXCLAMATION,             \
                                          this);                                 \
                             return;                                             \
                           }


class MyTreeItemData : public wxTreeItemData
{
public:
    MyTreeItemData(const wxString& desc) : m_desc(desc) { }

    void ShowInfo(wxTreeCtrl *tree);
    const wxChar *GetDesc() const { return m_desc.c_str(); }

private:
    wxString m_desc;
};



//nodes levels
enum {
L_ROOT = 0,
L_DIR ,
L_PHOTO ,
L_FACES 
};



class MyTreeCtrl : public wxTreeCtrl
{
public:
	
	wxTreeItemId m_rootId;

    enum
    {
        TreeCtrlIcon_File,
        TreeCtrlIcon_FileSelected,
        TreeCtrlIcon_Folder,
        TreeCtrlIcon_FolderSelected,
        TreeCtrlIcon_FolderOpened,
		TreeCtrlIcon_New, //red
		TreeCtrlIcon_Approved, //green
		TreeCtrlIcon_InAnalisys, //yellow
		TreeCtrlIcon_Revised, //blue
		TreeCtrlIcon_BB
    };


    MyTreeCtrl() { }
    MyTreeCtrl(wxWindow *parent, const wxWindowID id,
               const wxPoint& pos, const wxSize& size,
               long style);
    virtual ~MyTreeCtrl(){};

	//crisnv:
	int CheckNodeLevel(wxTreeItemId item_id);

    void OnBeginDrag(wxTreeEvent& event);
    void OnBeginRDrag(wxTreeEvent& event);
    void OnEndDrag(wxTreeEvent& event);
    void OnBeginLabelEdit(wxTreeEvent& event);
    void OnEndLabelEdit(wxTreeEvent& event);
    void OnDeleteItem(wxTreeEvent& event);
    void OnContextMenu(wxContextMenuEvent& event);
    void OnItemMenu(wxTreeEvent& event);
    void OnGetInfo(wxTreeEvent& event);
    void OnSetInfo(wxTreeEvent& event);
    void OnItemExpanded(wxTreeEvent& event);
    void OnItemExpanding(wxTreeEvent& event);
    void OnItemCollapsed(wxTreeEvent& event);
    void OnItemCollapsing(wxTreeEvent& event);
    //void OnSelChanged(wxTreeEvent& event);
    //crisnv:	void OnSelChanging(wxTreeEvent& event);
    //void OnTreeKeyDown(wxTreeEvent& event);
    void OnItemActivated(wxTreeEvent& event);
    void OnItemRClick(wxTreeEvent& event);

    void OnRMouseDown(wxMouseEvent& event);
    void OnRMouseUp(wxMouseEvent& event);
    void OnRMouseDClick(wxMouseEvent& event);

	//virtual void Collapse(const wxTreeItemId& item);


    void GetItemsRecursively(const wxTreeItemId& idParent,
                             wxTreeItemIdValue cookie = 0);

    void CreateImageList(int size = 16);
    void CreateButtonsImageList(int size = 11);

    void AddTestItemsToTree(size_t numChildren, size_t depth);

    void DoSortChildren(const wxTreeItemId& item, bool reverse = false)
        { m_reverseSort = reverse; wxTreeCtrl::SortChildren(item); }

#if (NAVEGADOR_VERSION >1) 
	void DoSortByStatus( bool reverse);
	void DoSortByName( bool reverse );
#endif


    void DoEnsureVisible() { if (m_lastItem.IsOk()) EnsureVisible(m_lastItem); }



    void ShowMenu(wxTreeItemId id, const wxPoint& pt);

    int ImageSize(void) const { return m_imageSize; }

    void SetLastItem(wxTreeItemId id) { m_lastItem = id; }

	int AddDir(Fundo *fd);
	
	//acoes de validacao da foto e da bb
	void AtualizaBBValidas(Fotografia *ft); 
//	void AddCheckedBB(void);
	
	void AtualizaFotoAprovada(void);
	void AtualizaFotoDesaprovada(void);
	void AtualizaFotoDesmarcada(void);
#if	(NAVEGADOR_VERSION > 1)
	void AtualizaFotoRevisada(void);
#endif
	void SelNext(void);
	void SelFirst(void);
	void SelLast(void);
	void SelPrev(void);


	void CollapseFaces(void);
	void ExpandFaces(void);

	void SelNextFace(void);
	void SelFirstFace(void);
	void SelLastFace(void);
	void SelPrevFace(void);

	void SelFaceByName(const char * bbName);

protected:

#if (NAVEGADOR_VERSION >1)

	void CopyItem(wxTreeItemId fromItem, wxTreeItemId toItem, bool isPhoto, bool recall);
	void CopyChildren();
#endif

    virtual int OnCompareItems(const wxTreeItemId& i1, const wxTreeItemId& i2);

	virtual void OnSelChanged(wxTreeEvent &event);


    // is this the test item which we use in several event handlers?
    bool IsTestItem(const wxTreeItemId& item)
    {
        // the test item is the first child folder
        //crisnv: 		return false;
		//
		return (false && GetItemParent(item) == GetRootItem() && !GetPrevSibling(item));
    }



	
private:
    void AddItemsRecursively(const wxTreeItemId& idParent,
                             size_t nChildren,
                             size_t depth,
                             size_t folder);

    void LogEvent(const wxChar *name, const wxTreeEvent& event);

    int          m_imageSize;               // current size of images
    bool         m_reverseSort;             // flag for OnCompareItems
    wxTreeItemId m_lastItem,                // for OnEnsureVisible()
                 m_draggedItem;             // item being dragged right now

    // NB: due to an ugly wxMSW hack you _must_ use DECLARE_DYNAMIC_CLASS()
    //     if you want your overloaded OnCompareItems() to be called.
    //     OTOH, if you don't want it you may omit the next line - this will
    //     make default (alphabetical) sorting much faster under wxMSW.
    DECLARE_DYNAMIC_CLASS(MyTreeCtrl)
    DECLARE_EVENT_TABLE()

	wxTreeItemId m_lastDir;
	wxTreeItemId m_lastImg;
};




#endif
