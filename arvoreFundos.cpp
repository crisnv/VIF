//
//	wxAppConsole *myApp = wxApp::GetInstance();
#include "arvoreFundos.h"
#include "menuAndControlsIds.h"
#include "navegadorFGV.h"

#include "Red.xpm"
#include "Yellow.xpm"
#include "Green.xpm"
#include "Blue.xpm"

#include "icon1.xpm"
#include "icon2.xpm"
#include "icon3.xpm"
#include "icon4.xpm"
#include "icon5.xpm"
#include "bb.xpm"

#define RED_INDEX		5
#define GREEN_INDEX		6
#define YELLOW_INDEX	7
#define BLUE_INDEX	8
#define BB_INDEX	9

class FacesApp;
class FacesMainFrame;

#if USE_GENERIC_TREECTRL
BEGIN_EVENT_TABLE(MyTreeCtrl, wxGenericTreeCtrl)
#else
BEGIN_EVENT_TABLE(MyTreeCtrl, wxTreeCtrl)
#endif
	EVT_KEY_DOWN(FacesMainFrame::Onkeyboard)

    EVT_TREE_BEGIN_DRAG(CNavegFGV_Ctrl, MyTreeCtrl::OnBeginDrag)
    EVT_TREE_BEGIN_RDRAG(CNavegFGV_Ctrl, MyTreeCtrl::OnBeginRDrag)
    EVT_TREE_END_DRAG(CNavegFGV_Ctrl, MyTreeCtrl::OnEndDrag)
    EVT_TREE_BEGIN_LABEL_EDIT(CNavegFGV_Ctrl, MyTreeCtrl::OnBeginLabelEdit)
    EVT_TREE_END_LABEL_EDIT(CNavegFGV_Ctrl, MyTreeCtrl::OnEndLabelEdit)
    EVT_TREE_DELETE_ITEM(CNavegFGV_Ctrl, MyTreeCtrl::OnDeleteItem)
#if 0       // there are so many of those that logging them causes flicker
    EVT_TREE_GET_INFO(CNavegFGV_Ctrl, MyTreeCtrl::OnGetInfo)
#endif
    EVT_TREE_SET_INFO(CNavegFGV_Ctrl, MyTreeCtrl::OnSetInfo)
    EVT_TREE_ITEM_EXPANDED(CNavegFGV_Ctrl, MyTreeCtrl::OnItemExpanded)
    EVT_TREE_ITEM_EXPANDING(CNavegFGV_Ctrl, MyTreeCtrl::OnItemExpanding)
    EVT_TREE_ITEM_COLLAPSED(CNavegFGV_Ctrl, MyTreeCtrl::OnItemCollapsed)
    EVT_TREE_ITEM_COLLAPSING(CNavegFGV_Ctrl, MyTreeCtrl::OnItemCollapsing)
	
    EVT_TREE_SEL_CHANGED(CNavegFGV_Ctrl, MyTreeCtrl::OnSelChanged)
    //crisnv:	EVT_TREE_SEL_CHANGING(CNavegFGV_Ctrl, MyTreeCtrl::OnSelChanging)
    //EVT_TREE_KEY_DOWN(CNavegFGV_Ctrl, MyTreeCtrl::OnTreeKeyDown)
    EVT_TREE_ITEM_ACTIVATED(CNavegFGV_Ctrl, MyTreeCtrl::OnItemActivated)

    // so many differents ways to handle right mouse button clicks...
    EVT_CONTEXT_MENU(MyTreeCtrl::OnContextMenu)
    // EVT_TREE_ITEM_MENU is the preferred event for creating context menus
    // on a tree control, because it includes the point of the click or item,
    // meaning that no additional placement calculations are required.
    EVT_TREE_ITEM_MENU(CNavegFGV_Ctrl, MyTreeCtrl::OnItemMenu)
    EVT_TREE_ITEM_RIGHT_CLICK(CNavegFGV_Ctrl, MyTreeCtrl::OnItemRClick)

    EVT_RIGHT_DOWN(MyTreeCtrl::OnRMouseDown)
    EVT_RIGHT_UP(MyTreeCtrl::OnRMouseUp)
    EVT_RIGHT_DCLICK(MyTreeCtrl::OnRMouseDClick)

END_EVENT_TABLE()



static inline const wxChar *Bool2String(bool b)
{
    return b ? wxT("") : wxT("not ");
}


int MyTreeCtrl::AddDir(Fundo *f){

	int error=0, i=0;
	Fotografia *foto = NULL;
	char imgname[64];
	char dirName[256];

	strcpy_s(dirName, 256, f->GetDirName());
	int image = TreeCtrlIcon_Folder; 
	int imageSel = image+1;
	wxTreeItemId id = AppendItem(m_rootId, dirName, image, imageSel, new MyTreeItemData(dirName));
	
	

/*
	image = TreeCtrlIcon_File; 
	imageSel = image+1;
*/

	for(i=0; i<f->GetNumFotosFundo(); i++){

		foto = f->GetPhoto(i);
		strcpy_s(imgname, 256, foto->GetImgName());
		
		if(foto){

			imageSel = -1;
			if(foto->isApproved()){	
				image = TreeCtrlIcon_Approved; 
			}else if(foto->isBrandNew()){
				image = TreeCtrlIcon_New; 
			}
#if	(NAVEGADOR_VERSION > 1)
			else if(foto->isRevised()){ 
				image = TreeCtrlIcon_Revised;
			}
#endif			
			else{
				image = TreeCtrlIcon_InAnalisys; 
			}

			wxTreeItemId child_id = AppendItem(id, imgname,image,imageSel, new MyTreeItemData(imgname));
			vector<retang> *bb = foto->GetBB();
			for(int b=0; b<bb->size(); b++){
				if((*bb)[b].nome[0] == '\0'){
					wxTreeItemId childbb_id = AppendItem(child_id, "sem nome",BB_INDEX,BB_INDEX, new MyTreeItemData(""));
				}else{
					wxTreeItemId childbb_id = AppendItem(child_id, (*bb)[b].nome,BB_INDEX,BB_INDEX, new MyTreeItemData((*bb)[b].nome));
				}
			}
		}
	}

	Expand(m_rootId);
	Expand(id);
	ExpandAllChildren(id);
	Refresh();
	//ExpandAll();
	return 0;
}

//first photo:
void MyTreeCtrl::SelFirst(void)
{
	wxTreeItemIdValue cookie;
	/*
	Child enumeration functions require the caller to give them a cookie parameter: it is a number which is opaque to the caller but is used by the tree control itself to allow multiple enumerations to run simultaneously (this is explicitly allowed). The only thing to remember is that the cookie passed to GetFirstChild and to GetNextChild should be the same variable (and that nothing should be done with it by the user code).
	*/
	wxTreeItemId item_id = GetSelection();
	
	//tratamento da nao selecao: se vazio seleciono a raiz
	if(item_id.m_pItem == NULL ){
		item_id = GetRootItem();
		if(item_id.IsOk())
			item_id = GetFirstChild(item_id, cookie);
	}
	
	
	if(item_id){		
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}	
				
		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o primeiro filho
		if(parent_id ==m_rootId){					
			wxTreeItemId first_id = GetFirstChild(item_id, cookie);
			if(first_id){
				SelectItem(first_id);
			}			
		}else{	
			//se não o avô é a raiz, entao item é uma imagem	
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			if(parent_parent_id ==m_rootId){					
				wxTreeItemId first_id = GetFirstChild(parent_id, cookie);
				if(first_id){
					SelectItem(first_id);
				}			
			}else{	
				//se não o bisaavô é a raiz, entao item é uma face
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );
		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				if(parent_parent_parent_id ==m_rootId){					
					wxTreeItemId first_id = GetFirstChild(parent_parent_id, cookie);
					if(first_id){
						SelectItem(first_id);
					}			
				}
			}
		}
	}
}

//last photo:
void MyTreeCtrl::SelLast(void)
{
	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	
	//tratamento da nao selecao: se vazio seleciono a raiz
	if(item_id.m_pItem == NULL ){
		item_id = GetRootItem();
		if(item_id.IsOk())
			item_id = GetFirstChild(item_id, cookie);
	}
	
	
	
	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o ultimo filho
		if(parent_id ==m_rootId){					
			wxTreeItemId last_id = GetLastChild(item_id);
			if(last_id){
				SelectItem(last_id );
			}
		}else{	
			//se não o avô é a raiz, entao item é uma imagem	
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			if(parent_parent_id ==m_rootId){					
				wxTreeItemId first_id = GetLastChild(parent_id);
				if(first_id){
					SelectItem(first_id);
				}			
			}else{	
				//se não o bisaavô é a raiz, entao item é uma face
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );
		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				if(parent_parent_parent_id ==m_rootId){					
					wxTreeItemId first_id = GetLastChild(parent_parent_id);
					if(first_id){
						SelectItem(first_id);
					}			
				}
			}
		}
	}
}

//next photo:
void MyTreeCtrl::SelNext(void){
	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	//tratamento da nao selecao: se vazio seleciono a raiz
	if(item_id.m_pItem == NULL ){
		item_id = GetRootItem();
		if(item_id.IsOk())
			item_id = GetFirstChild(item_id, cookie);
	}
	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}	

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o primeiro filho
		if(parent_id ==m_rootId){					
			wxTreeItemId first_id = GetFirstChild(item_id, cookie);
			if(first_id){
				SelectItem(first_id);
			}			
		}else{	
			
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			//se não, o avô é a raiz, entao item é uma imagem, procura próximo filho	do pai
			if(parent_parent_id ==m_rootId){		
				
				wxTreeItemId search_id = GetFirstChild(parent_id, cookie);
				if(search_id){
					while(search_id != item_id && search_id ){
						search_id = GetNextChild(parent_id,cookie);
					}
					wxTreeItemId next_id = GetNextChild(parent_id, cookie);				
					if(next_id){
						SelectItem(next_id);
					}
				}
			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){					
				
					wxTreeItemId search_id = GetFirstChild(parent_parent_id, cookie);
					if(search_id){
						while(search_id != parent_id && search_id ){
							search_id = GetNextChild(parent_parent_id,cookie);
						}
						wxTreeItemId next_id = GetNextChild(parent_parent_id, cookie);				
						if(next_id){
							SelectItem(next_id);
						}
					}
				}
			}
		}

	}
}

//previous photo:
void MyTreeCtrl::SelPrev(void){
	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	
	//tratamento da nao selecao: se vazio seleciono a raiz
	if(item_id.m_pItem == NULL ){
		item_id = GetRootItem();
		if(item_id.IsOk())
			item_id = GetFirstChild(item_id, cookie);
	}
	
	
	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}	

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o último filho
		if(parent_id ==m_rootId){					
			wxTreeItemId first_id = GetLastChild(item_id);
			if(first_id){
				SelectItem(first_id);
			}			
		}else{	
			
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			//se não, o avô é a raiz, entao item é uma imagem, procura próximo filho	do pai
			if(parent_parent_id ==m_rootId){		
				
				wxTreeItemId search_id = GetFirstChild(parent_id, cookie);
				if(search_id){
										
					wxTreeItemId prev_id = search_id;
					while(search_id != item_id && search_id ){
						prev_id = search_id;
						search_id = GetNextChild(parent_id,cookie);
					}
					if(prev_id){
						SelectItem(prev_id);
					}
				}
			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){					
				
					wxTreeItemId search_id = GetFirstChild(parent_parent_id, cookie);
					if(search_id){

						wxTreeItemId prev_id = search_id;				
						while(search_id != parent_id && search_id ){
							prev_id = search_id;
							search_id = GetNextChild(parent_parent_id,cookie);
						}
						if(prev_id){
							SelectItem(prev_id);
						}
					}
				}
			}
		}

	}

	

	/*


	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	if(item_id){
		CHECK_ITEM( item_id );
		wxTreeItemId parent_id = GetItemParent(item_id);
		if(parent_id){
			CHECK_ITEM( parent_id );

			wxTreeItemId search_id = GetFirstChild(parent_id, cookie);
			if(search_id){
				
				wxTreeItemId prev_id = search_id;
				while(search_id != item_id ){
					prev_id = search_id;
					search_id = GetNextChild(parent_id,cookie);
				}
				
				if(prev_id){
					SelectItem(prev_id);
				}
			}
		}
	}
	*/
}


void MyTreeCtrl::SelFirstFace(void){

	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	if(item_id){		
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}	
				
		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o primeiro neto do dir
		if(parent_id ==m_rootId){	
			if(! HasChildren(item_id)) return;
			wxTreeItemId first_photo_id = GetFirstChild(item_id, cookie);
			if(first_photo_id){				
				if(! HasChildren(first_photo_id)) return;
				wxTreeItemId first_face_id = GetFirstChild(first_photo_id, cookie);
				if(first_face_id){
					SelectItem(first_face_id );
				}
			}			
		}else{	
			
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			//se não, se o avô é a raiz, entao item é uma imagem, pega primeiro filho do item	
			if(parent_parent_id ==m_rootId){	

				if(! HasChildren(item_id)) return;							
				wxTreeItemId first_id = GetFirstChild(item_id, cookie);
				if(first_id){
					SelectItem(first_id);
				}			
			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){		


					wxTreeItemId first_id = GetFirstChild(parent_id, cookie);
					if(first_id){
						SelectItem(first_id);
					}			
				}
			}
		}
	}
}
void MyTreeCtrl::SelLastFace(void){

	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega no primeiro filho o ultimo neto
		if(parent_id ==m_rootId){					

			wxTreeItemId first_photo_id = GetFirstChild(item_id, cookie);
			if(first_photo_id){				
				wxTreeItemId last_face_id= GetLastChild(first_photo_id);
				if(last_face_id){
					SelectItem(last_face_id);
				}
			}	

		}else{				
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			//se não o avô é a raiz, entao item é uma imagem	
			if(parent_parent_id ==m_rootId){					
				wxTreeItemId last_id = GetLastChild(item_id);
				if(last_id ){
					SelectItem(last_id);
				}			
			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){					
					wxTreeItemId last_id = GetLastChild(parent_id);
					if(last_id ){
						SelectItem(last_id );
					}			
				}
			}
		}
	}
}
void MyTreeCtrl::SelNextFace(void){

	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}	

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o primeiro neto do dir
		if(parent_id ==m_rootId){	
			if(! HasChildren(item_id)) return;			
			wxTreeItemId first_photo_id = GetFirstChild(item_id, cookie);
			if(first_photo_id){		
				if(! HasChildren(first_photo_id)) return;
				wxTreeItemId first_face_id = GetFirstChild(first_photo_id, cookie);
				if(first_face_id){
					SelectItem(first_face_id );
				}
			}			
		}else{	
			
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			//se não, o avô é a raiz, entao item é uma imagem, procura O PRIMEIRO filho	do ITEM
			if(parent_parent_id ==m_rootId){		
				
				if(! HasChildren(item_id)) return;			
				wxTreeItemId face_id = GetFirstChild(item_id, cookie);
				if(face_id){	
					SelectItem(face_id);	
				}	
			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){					
				
						wxTreeItemId search_id = GetFirstChild( parent_id, cookie);
						if(search_id){
							while(search_id != item_id && search_id ){
								search_id = GetNextChild( parent_id,cookie);
							}
							wxTreeItemId next_id = GetNextChild( parent_id, cookie);				
							if(next_id){
								SelectItem(next_id);
							}
						}
					
				}
			}
		}

	}
	
}
void MyTreeCtrl::SelPrevFace(void){
	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, nao faz nada
		if(item_id==m_rootId){					
			return;
		}	

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		
		//se o pai é a raiz, entao item é um diretorio, pega o ultimo neto do primeiro filho do dir
		if(parent_id ==m_rootId){		
			if(! HasChildren(item_id)) return;
			wxTreeItemId first_photo_id = GetFirstChild(item_id, cookie);
			if(first_photo_id){				
				if(! HasChildren(first_photo_id)) return;
				wxTreeItemId last_face_id = GetLastChild(first_photo_id);
				if(last_face_id ){
					SelectItem(last_face_id );
				}
			}
		}else{	
			
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );						
			//se não, se o avô é a raiz, entao item é uma imagem, pega o ultimo filho do item	
			if(parent_parent_id ==m_rootId){		
				if(! HasChildren(item_id)) return;			
				wxTreeItemId first_id = GetLastChild(item_id);
				if(first_id){
					SelectItem(first_id);
				}			
			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){					
				
					wxTreeItemId search_id = GetFirstChild(parent_id, cookie);
					if(search_id){

						wxTreeItemId prev_id = search_id;				
						while(search_id != item_id && search_id ){
							prev_id = search_id;
							search_id = GetNextChild(parent_id,cookie);
						}
						if(prev_id){
							SelectItem(prev_id);
						}
					}
				}
			}
		}

	}

	

	/*


	wxTreeItemIdValue cookie;		
	wxTreeItemId item_id = GetSelection();
	if(item_id){
		CHECK_ITEM( item_id );
		wxTreeItemId parent_id = GetItemParent(item_id);
		if(parent_id){
			CHECK_ITEM( parent_id );

			wxTreeItemId search_id = GetFirstChild(parent_id, cookie);
			if(search_id){
				
				wxTreeItemId prev_id = search_id;
				while(search_id != item_id ){
					prev_id = search_id;
					search_id = GetNextChild(parent_id,cookie);
				}
				
				if(prev_id){
					SelectItem(prev_id);
				}
			}
		}
	}
	*/
}

void MyTreeCtrl::SelFaceByName(const char * bbName){


	wxTreeItemId item_id = GetSelection();
	if(!item_id ) 
		return;
	CHECK_ITEM( item_id );
	wxTreeItemId parent_id = GetItemParent(item_id);
	if(!parent_id ) 
		return;
	CHECK_ITEM( parent_id );

	wxTreeItemId parent_parent_id = GetItemParent(parent_id);
	if(!parent_parent_id ) 
		return;	
	CHECK_ITEM( parent_parent_id );
			
	wxTreeItemId foto_id, dir_id, root_id  ;
	if(parent_parent_id == m_rootId){
		root_id	= parent_parent_id ;
		dir_id	=	parent_id;
		foto_id =	item_id;		
	}else{

		wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id);
	    CHECK_ITEM( parent_parent_parent_id );
		if(parent_parent_parent_id == m_rootId){
			root_id	=	parent_parent_parent_id ;
			dir_id	=	parent_parent_id;
			foto_id =	parent_id;		
		}else{
			return;
		}
	}
	
	if(bbName == NULL){
		SelectItem(foto_id);
		return;
	}

	wxTreeItemIdValue cookie;			
	wxTreeItemId face_id = GetFirstChild( foto_id, cookie);
	
	if(face_id){
		MyTreeItemData *face_item = 0;//(MyTreeItemData *)GetItemData(face_id);
		const wxChar * temp = 0;//(face_item->GetDesc());
		
		while(face_id){
					
			face_item = (MyTreeItemData *)GetItemData(face_id);
			temp = (face_item->GetDesc());
			if(	wxStrcmp( temp , bbName) == 0   ){
				break;
			}
			face_id = GetNextChild( foto_id,cookie);
		}
		
		if(face_id){
			SelectItem(face_id);
		}else{
			SelectItem(foto_id);
		}
	}else{
		SelectItem(foto_id);
	}


}

void MyTreeCtrl::AtualizaFotoAprovada(void){

	wxTreeItemId item_id = GetSelection();
	CHECK_ITEM( item_id );
	wxTreeItemId parent_id = GetItemParent(item_id);
	CHECK_ITEM( parent_id );
	wxTreeItemId parent_parent_id = GetItemParent(parent_id);
	CHECK_ITEM( parent_parent_id );

	wxTreeItemId foto_id, dir_id, root_id  ;
	if(parent_parent_id == m_rootId){
		root_id	= parent_parent_id ;
		dir_id	=	parent_id;
		foto_id =	item_id;		
	}else{

		wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id);
	    CHECK_ITEM( parent_parent_parent_id );

		if(parent_parent_parent_id == m_rootId){
			root_id	=	parent_parent_parent_id ;
			dir_id	=	parent_parent_id;
			foto_id =	parent_id;		
		}else{
			return;
		}
	}

	SetItemImage(foto_id, TreeCtrlIcon_Approved); 
	ExpandAllChildren(foto_id);
}
void MyTreeCtrl::AtualizaFotoDesmarcada(void){

	wxTreeItemId item_id = GetSelection();
	CHECK_ITEM( item_id );
	wxTreeItemId parent_id = GetItemParent(item_id);
	CHECK_ITEM( parent_id );
	wxTreeItemId parent_parent_id = GetItemParent(parent_id);
	CHECK_ITEM( parent_parent_id );


	wxTreeItemId foto_id, dir_id, root_id  ;
	if(parent_parent_id == m_rootId){
		root_id	= parent_parent_id ;
		dir_id	=	parent_id;
		foto_id =	item_id;		
	}else{

		wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id);
	    CHECK_ITEM( parent_parent_parent_id );

		if(parent_parent_parent_id == m_rootId){
			root_id	=	parent_parent_parent_id ;
			dir_id	=	parent_parent_id;
			foto_id =	parent_id;		
		}else{
			return;
		}
	}

	SetItemImage(foto_id, TreeCtrlIcon_New); 
	DeleteChildren(foto_id);
}
void MyTreeCtrl::AtualizaFotoDesaprovada(void){
	wxTreeItemId item_id = GetSelection();
	CHECK_ITEM( item_id );
	wxTreeItemId parent_id = GetItemParent(item_id);
	CHECK_ITEM( parent_id );
	wxTreeItemId parent_parent_id = GetItemParent(parent_id);
	CHECK_ITEM( parent_parent_id );

	wxTreeItemId foto_id, dir_id, root_id  ;
	if(parent_parent_id == m_rootId){
		root_id	= parent_parent_id ;
		dir_id	=	parent_id;
		foto_id =	item_id;		
	}else{

		wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id);
	    CHECK_ITEM( parent_parent_parent_id );

		if(parent_parent_parent_id == m_rootId){
			root_id	=	parent_parent_parent_id ;
			dir_id	=	parent_parent_id;
			foto_id =	parent_id;		
		}else{
			return;
		}
	}

	SetItemImage(foto_id, TreeCtrlIcon_InAnalisys); 
	ExpandAllChildren(foto_id);

}

#if	(NAVEGADOR_VERSION > 1)
void MyTreeCtrl::AtualizaFotoRevisada(void){
	wxTreeItemId item_id = GetSelection();
	CHECK_ITEM( item_id );
	wxTreeItemId parent_id = GetItemParent(item_id);
	CHECK_ITEM( parent_id );
	wxTreeItemId parent_parent_id = GetItemParent(parent_id);
	CHECK_ITEM( parent_parent_id );

	wxTreeItemId foto_id, dir_id, root_id  ;
	if(parent_parent_id == m_rootId){
		root_id	= parent_parent_id ;
		dir_id	=	parent_id;
		foto_id =	item_id;		
	}else{

		wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id);
	    CHECK_ITEM( parent_parent_parent_id );

		if(parent_parent_parent_id == m_rootId){
			root_id	=	parent_parent_parent_id ;
			dir_id	=	parent_parent_id;
			foto_id =	parent_id;		
		}else{
			return;
		}
	}

	SetItemImage(foto_id, TreeCtrlIcon_Revised); 
	ExpandAllChildren(foto_id);

}
#endif

void MyTreeCtrl::AtualizaBBValidas(Fotografia *ft){

	wxTreeItemId item_id = GetSelection();
    CHECK_ITEM( item_id );
	wxTreeItemId parent_id = GetItemParent(item_id);
    CHECK_ITEM( parent_id );
	wxTreeItemId parent_parent_id = GetItemParent(parent_id);
    CHECK_ITEM( parent_parent_id );


	wxTreeItemId foto_id, dir_id, root_id  ;
	if(parent_parent_id == m_rootId){
		root_id	= parent_parent_id ;
		dir_id	=	parent_id;
		foto_id =	item_id;		
	}else{

		wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id);
	    CHECK_ITEM( parent_parent_parent_id );

		if(parent_parent_parent_id == m_rootId){
			root_id	=	parent_parent_parent_id ;
			dir_id	=	parent_parent_id;
			foto_id =	parent_id;		
		}else{
			return;
		}
	}
		
	if(ft){

		SelectItem(foto_id);
		DeleteChildren(foto_id);

		SetItemImage(foto_id, TreeCtrlIcon_InAnalisys); 
		
		vector<retang> *bb = ft->GetBB();
		for(int b=0; b<bb->size(); b++){
			if((*bb)[b].approved){
				if((*bb)[b].nome[0] == '\0'){
					wxTreeItemId bb_id = AppendItem(foto_id, "sem nome",BB_INDEX,BB_INDEX, new MyTreeItemData(""));
				}else{
					wxTreeItemId bb_id = AppendItem(foto_id, (*bb)[b].nome,BB_INDEX,BB_INDEX, new MyTreeItemData((*bb)[b].nome));
				}
			}
		}


	}


	ExpandAllChildren(foto_id);
}


void MyTreeCtrl::OnBeginDrag(wxTreeEvent& event)
{
    // need to explicitly allow drag
    if ( event.GetItem() != GetRootItem() )
    {
        m_draggedItem = event.GetItem();

        wxPoint clientpt = event.GetPoint();
        wxPoint screenpt = ClientToScreen(clientpt);

        #ifdef _DEBUG
		wxLogMessage(wxT("OnBeginDrag: started dragging %s at screen coords (%i,%i)"),
                     GetItemText(m_draggedItem).c_str(),
                     screenpt.x, screenpt.y);
		#endif

        event.Allow();
    }
    else
    {
        #ifdef _DEBUG
			wxLogMessage(wxT("OnBeginDrag: this item can't be dragged."));
		#endif
    }
}

void MyTreeCtrl::OnEndDrag(wxTreeEvent& event)
{
    wxTreeItemId itemSrc = m_draggedItem,
                 itemDst = event.GetItem();
    m_draggedItem = (wxTreeItemId)0l;

    // where to copy the item?
    if ( itemDst.IsOk() && !ItemHasChildren(itemDst) )
    {
        // copy to the parent then
        itemDst = GetItemParent(itemDst);
    }

    if ( !itemDst.IsOk() )
    {
        
        #ifdef _DEBUG
		wxLogMessage(wxT("OnEndDrag: can't drop here."));
		#endif

        return;
    }

    wxString text = GetItemText(itemSrc);
    
#ifdef _DEBUG		
	wxLogMessage(wxT("OnEndDrag: '%s' copied to '%s'."),
                 text.c_str(), GetItemText(itemDst).c_str());
#endif
    // just do append here - we could also insert it just before/after the item
    // on which it was dropped, but this requires slightly more work... we also
    // completely ignore the client data and icon of the old item but could
    // copy them as well.
    //
    // Finally, we only copy one item here but we might copy the entire tree if
    // we were dragging a folder.
			
	int image = FacesApp::getFacesApp()->ShowImages() ? TreeCtrlIcon_File : -1;
    AppendItem(itemDst, text, image);
}

void MyTreeCtrl::OnBeginLabelEdit(wxTreeEvent& event)
{
    
#ifdef _DEBUG
	wxLogMessage(wxT("OnBeginLabelEdit"));
#endif
	

    // for testing, prevent this item's label editing
    wxTreeItemId itemId = event.GetItem();
    if ( IsTestItem(itemId) )
    {
        wxMessageBox(wxT("You can't edit this item."));

        event.Veto();
    }
    else if ( itemId == GetRootItem() )
    {
        // test that it is possible to change the text of the item being edited
        SetItemText(itemId, _T("Editing root item"));
    }
}

void MyTreeCtrl::OnEndLabelEdit(wxTreeEvent& event)
{
    
#ifdef _DEBUG
		wxLogMessage(wxT("OnEndLabelEdit"));
#endif

    // don't allow anything except letters in the labels
    if ( !event.GetLabel().IsWord() )
    {
        wxMessageBox(wxT("The new label should be a single word."));

        event.Veto();
    }
}

void MyTreeCtrl::OnItemCollapsing(wxTreeEvent& event)
{
#ifdef _DEBUG
		wxLogMessage(wxT("OnItemCollapsing"));
#endif 
	/*
	
      

    // for testing, prevent the user from collapsing the first child folder
    wxTreeItemId itemId = event.GetItem();
    if ( IsTestItem(itemId) )
    {
        wxMessageBox(wxT("You can't collapse this item."));

        event.Veto();
    }
	*/
}

void MyTreeCtrl::OnItemActivated(wxTreeEvent& event)
{
    // show some info about this item
    wxTreeItemId itemId = event.GetItem();
    MyTreeItemData *item = (MyTreeItemData *)GetItemData(itemId);

    if ( item != NULL )
    {
        item->ShowInfo(this);
    }

    
#ifdef _DEBUG
		wxLogMessage(wxT("OnItemActivated"));
#endif
}

void MyTreeCtrl::OnItemMenu(wxTreeEvent& event)
{
    wxTreeItemId itemId = event.GetItem();
    MyTreeItemData *item = itemId.IsOk() ? (MyTreeItemData *)GetItemData(itemId)
                                         : NULL;
    wxPoint clientpt = event.GetPoint();
    wxPoint screenpt = ClientToScreen(clientpt);

    
#ifdef _DEBUG
	wxLogMessage(wxT("OnItemMenu for item \"%s\" at screen coords (%i, %i)"), 
                 item ? item->GetDesc() : _T(""), screenpt.x, screenpt.y);
#endif
	

    ShowMenu(itemId, clientpt);
    event.Skip();
}

void MyTreeCtrl::OnContextMenu(wxContextMenuEvent& event)
{
    wxPoint pt = event.GetPosition();

	
#ifdef _DEBUG
	wxLogMessage(wxT("OnContextMenu at screen coords (%i, %i)"), pt.x, pt.y);
#endif
    
}

void MyTreeCtrl::ShowMenu(wxTreeItemId id, const wxPoint& pt)
{
    wxString title;
    if ( id.IsOk() )
    {
        title << wxT("Menu for ") << GetItemText(id);
    }
    else
    {
        title = wxT("Menu for no particular item");
    }
/*
#if wxUSE_MENUS
    wxMenu menu(title);
    menu.Append(CNavegFGV_About, wxT("&About..."));
    menu.AppendSeparator();
    menu.Append(CNavegFGV_Highlight, wxT("&Highlight item"));
    menu.Append(CNavegFGV_Dump, wxT("&Dump"));

    PopupMenu(&menu, pt);
#endif // wxUSE_MENUS
	*/
}

void MyTreeCtrl::OnItemRClick(wxTreeEvent& event)
{
    wxTreeItemId itemId = event.GetItem();
    MyTreeItemData *item = itemId.IsOk() ? (MyTreeItemData *)GetItemData(itemId)
                                         : NULL;

	
#ifdef _DEBUG
	wxLogMessage(wxT("Item \"%s\" right clicked"), item ? item->GetDesc()
                                                    : _T(""));
#endif
	
   event.Skip();
}

void MyTreeCtrl::OnRMouseDown(wxMouseEvent& event)
{
	
#ifdef _DEBUG
	wxLogMessage(wxT("Right mouse button down"));
#endif
   
    event.Skip();
}

void MyTreeCtrl::OnRMouseUp(wxMouseEvent& event)
{
    
#ifdef _DEBUG
	wxLogMessage(wxT("Right mouse button up"));
#endif
	
    event.Skip();
}

void MyTreeCtrl::OnRMouseDClick(wxMouseEvent& event)
{
    wxTreeItemId id = HitTest(event.GetPosition());
    if ( !id ){      
		
    #ifdef _DEBUG
		wxLogMessage(wxT("No item under mouse"));
	#endif
	}
    else
    {
        MyTreeItemData *item = (MyTreeItemData *)GetItemData(id);
        
#ifdef _DEBUG
		if ( item )
            wxLogMessage(wxT("Item '%s' under mouse"), item->GetDesc());
#endif
   }

    event.Skip();
}

void MyTreeItemData::ShowInfo(wxTreeCtrl *tree)
{
#ifdef _DEBUG
    wxLogMessage(wxT("Item '%s': %sselected, %sexpanded, %sbold,\n")
                 wxT("%u children (%u immediately under this item)."),
                 m_desc.c_str(),
                 Bool2String(tree->IsSelected(GetId())),
                 Bool2String(tree->IsExpanded(GetId())),
                 Bool2String(tree->IsBold(GetId())),
                 unsigned(tree->GetChildrenCount(GetId())),
                 unsigned(tree->GetChildrenCount(GetId(), false)));
#endif
}

int MyTreeCtrl::CheckNodeLevel(wxTreeItemId item_id){

	//CHECK_ITEM( item_id );
	if(!item_id.IsOk() )
		return -1;

	if( m_rootId == item_id ){
		return L_ROOT;
	}
	else{
		wxTreeItemId parent_id= GetItemParent(item_id);
		if( m_rootId == parent_id ){
			return L_DIR;
		}
		else{
			wxTreeItemId parent_parent_id = GetItemParent(parent_id);
			if( m_rootId == parent_parent_id ){
				return L_PHOTO;
			}else{
				return L_FACES ;
			}
		}
	}
	return -1;
}
void MyTreeCtrl::OnSelChanged(wxTreeEvent &event){

	wxString dirName;
	wxString imgName;

    wxTreeItemId parent_id ;
	wxTreeItemId item_id = GetSelection();
    CHECK_ITEM( item_id );

	if( m_rootId != item_id ) 
		parent_id= GetItemParent(item_id);
	
	if( (m_rootId == item_id )|| (m_rootId ==parent_id ) ){
		//aqui: fechar imagem aberta se houver:
		
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->FrameAlterarImagem( "", "");
			
		wxGetActiveWindow()->Refresh();
		//limpar combos
		wxString name ="";
		//((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateComboItemSelectedByName(name);
		wxString text;
		//text << _T('"') << "Legenda"<< _T('"');
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->SetLegend(text);
		

		m_lastDir= parent_id;
		m_lastImg= parent_id;


		//
		return;
		//verificar caso de troca de diretorios
	}
	/*
	wxTreeItemId parent_id = GetItemParent(item_id);
	if(m_rootId == parent_id ){
		//aqui: fechar imagem aberta se houver:
		return;
	}
	*/

	//CHECK_ITEM( parent_id);

	wxTreeItemId parent_parent_id = GetItemParent(parent_id);
    //CHECK_ITEM( parent_parent_id );

	MyTreeItemData *item = (MyTreeItemData *)GetItemData(item_id);
	

	//seleção com escolha de foto
	if ( (item_id!=m_rootId) && (parent_id!=m_rootId) && (parent_parent_id == m_rootId)){
		
		MyTreeItemData *itemParent = (MyTreeItemData *)GetItemData(parent_id);
		
		dirName.append(itemParent->GetDesc());

		if(item!=0 && itemParent!=0){

			imgName.append(item->GetDesc());

			wxString text;
			text << _T('"') << item->GetDesc()<< _T('"');
			
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->FrameAlterarImagem(imgName.c_str(), dirName.c_str());
			
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->SetLegend(text);

			if(GetItemImage(item_id) !=TreeCtrlIcon_Approved) {
				SetItemImage(item_id, TreeCtrlIcon_InAnalisys);
			//marcar como (m_aprovada==e_inAnalisys)
			
			}
			
			wxGetActiveWindow()->Refresh();
		}

		if(m_lastDir!=parent_id){
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateDescritorCombo(dirName);
		}
		m_lastDir=parent_id;
		m_lastImg=item_id;

		//tramento da bb
		wxString bbName;
		//queremos desmarcar bb
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateBBSelectedByName(bbName);
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateComboItemSelectedByName(bbName);

	}
	//escolha de diretorio (fundo):
	else if(parent_id==m_rootId){
		if(m_lastDir!=item_id){
			dirName.append(item->GetDesc());
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateDescritorCombo(dirName);
		}
		m_lastDir=item_id;
		m_lastImg =  wxTreeItemId();// item_id;//pq nao consigo colocar outra
	}
	//escolha de bb
	else{

		//tramento da img
		if(	m_lastImg != parent_id){	//le dado do diretorio
			
			MyTreeItemData *itemParentParent = (MyTreeItemData *)GetItemData(parent_parent_id);
			dirName.append(itemParentParent ->GetDesc());

			MyTreeItemData *itemParent = (MyTreeItemData *)GetItemData( parent_id);
			imgName.append(itemParent->GetDesc());

			if(itemParent!=0 && itemParentParent!=0)
			{
				wxString text;
				text << _T('"') << itemParent->GetDesc()<< _T('"');
				
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->FrameAlterarImagem(imgName.c_str(), dirName.c_str());

				((FacesMainFrame *)FacesApp::getFacesMainFrame())->SetLegend(text);

				wxGetActiveWindow()->Refresh();
			}

			if(m_lastDir!=parent_parent_id){
				((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateDescritorCombo(dirName);
			}
		}
		m_lastDir=parent_parent_id;
		m_lastImg=parent_id;

		//tramento da bb
		wxString bbName;
		bbName.append(item->GetDesc());
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateBBSelectedByName(bbName);
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateComboItemSelectedByName(bbName);

		//1o se dir selecionao nao for o atual, seleciona 1o
//		printf("teste");
	}
}



// MyTreeCtrl implementation
#if USE_GENERIC_TREECTRL
IMPLEMENT_DYNAMIC_CLASS(MyTreeCtrl, wxGenericTreeCtrl)
#else
IMPLEMENT_DYNAMIC_CLASS(MyTreeCtrl, wxTreeCtrl)
#endif

MyTreeCtrl::MyTreeCtrl(wxWindow *parent, const wxWindowID id,
                       const wxPoint& pos, const wxSize& size,
                       long style)
          : wxTreeCtrl(parent, id, pos, size, style)
{
    m_reverseSort = false;

    CreateImageList();


	if(size.GetWidth() < 200){
		wxFont font= GetFont();
		font.SetPointSize(font.GetPointSize()-2);	
		SetFont(font);
	}



	
	int image = (FacesApp::getFacesApp())->ShowImages() ? MyTreeCtrl::TreeCtrlIcon_Folder : -1;
    
	//Root
	m_rootId = AddRoot(wxT("Acervo CPDOC-FGV"),
                                  image, image,
                                  new MyTreeItemData(wxT("Root item")));
  

    // Add some items to the tree AddTestItemsToTree(6, 2);
}

void MyTreeCtrl::CreateImageList(int size)
{
    if ( size == -1 )
    {
        SetImageList(NULL);
        return;
    }
    if ( size == 0 )
        size = m_imageSize;
    else
        m_imageSize = size;

    // Make an image vector containing small icons
    wxImageList *images = new wxImageList(size, size, true);

    // should correspond to TreeCtrlIcon_xxx enum
    wxBusyCursor wait;
    wxIcon icons[10];
    icons[0] = wxIcon(icon1_xpm);
    icons[1] = wxIcon(icon2_xpm);
    icons[2] = wxIcon(icon3_xpm);
    icons[3] = wxIcon(icon4_xpm);
    icons[4] = wxIcon(icon5_xpm);

    icons[RED_INDEX] = wxIcon(Red_xpm);
	icons[GREEN_INDEX] = wxIcon(Green_xpm);
    icons[YELLOW_INDEX] = wxIcon(Yellow_xpm);
	icons[BLUE_INDEX] = wxIcon(Blue_xpm);
    icons[BB_INDEX] = wxIcon(bb_xpm);


    int sizeOrig = icons[0].GetWidth();
    for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
    {
        if ( size == sizeOrig )
        {
            images->Add(icons[i]);
        }
        else
        {
            images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
        }
    }

    AssignImageList(images);
}

#if USE_GENERIC_TREECTRL || !defined(__WXMSW__)
void MyTreeCtrl::CreateButtonsImageList(int size)
{
    if ( size == -1 )
    {
        SetButtonsImageList(NULL);
        return;
    }

    // Make an image vector containing small icons
    wxImageList *images = new wxImageList(size, size, true);

    // should correspond to TreeCtrlIcon_xxx enum
    wxBusyCursor wait;
    wxIcon icons[4];
    icons[0] = wxIcon(icon3_xpm);   // closed
    icons[1] = wxIcon(icon3_xpm);   // closed, selected
    icons[2] = wxIcon(icon5_xpm);   // open
    icons[3] = wxIcon(icon5_xpm);   // open, selected

    for ( size_t i = 0; i < WXSIZEOF(icons); i++ )
    {
        int sizeOrig = icons[i].GetWidth();
        if ( size == sizeOrig )
        {
            images->Add(icons[i]);
        }
        else
        {
            images->Add(wxBitmap(wxBitmap(icons[i]).ConvertToImage().Rescale(size, size)));
        }
    }

    AssignButtonsImageList(images);
#else
void MyTreeCtrl::CreateButtonsImageList(int WXUNUSED(size))
{
#endif
}

int MyTreeCtrl::OnCompareItems(const wxTreeItemId& item1,
                               const wxTreeItemId& item2)
{
    if ( m_reverseSort )
    {
        // just exchange 1st and 2nd items
        return wxTreeCtrl::OnCompareItems(item2, item1);
    }
    else
    {
        return wxTreeCtrl::OnCompareItems(item1, item2);
    }
}



void MyTreeCtrl::AddItemsRecursively(const wxTreeItemId& idParent,
                                     size_t numChildren,
                                     size_t depth,
                                     size_t folder)
{

	
	if ( depth > 0 )
    {
        bool hasChildren = depth > 1;

        wxString str;
        for ( size_t n = 0; n < numChildren; n++ )
        {
            // at depth 1 elements won't have any more children
			if ( hasChildren ){
             
				str.Printf(wxT("%s %u"), wxT("Fundo"), unsigned(n + 1));
				//str.Printf(wxT("%s child %u"), wxT("Folder"), unsigned(n + 1));
			}
			else{
                //
				str.Printf(wxT("%s %u.%u"), wxT("Arquivo:"), unsigned(folder), unsigned(n + 1));
			}

            // here we pass to AppendItem() normal and selected item images (we
            // suppose that selected image follows the normal one in the enum)
            int image, imageSel;
			if ( (FacesApp::getFacesApp())->ShowImages() )
            {
                image = depth == 1 ? TreeCtrlIcon_File : TreeCtrlIcon_Folder;
                imageSel = image + 1;
            }
            else
            {
                image = imageSel = -1;
            }
            wxTreeItemId id = AppendItem(idParent, str, image, imageSel,
                                         new MyTreeItemData(str));

            // and now we also set the expanded one (only for the folders)
            if ( hasChildren && (FacesApp::getFacesApp())->ShowImages() )
            {
                SetItemImage(id, TreeCtrlIcon_FolderOpened,
                             wxTreeItemIcon_Expanded);
            }

            // remember the last child for OnEnsureVisible()
            if ( !hasChildren && n == numChildren - 1 )
            {
                m_lastItem = id;
            }

            AddItemsRecursively(id, numChildren, depth - 1, n + 1);
        }
    }
    //else: done!
}

void MyTreeCtrl::AddTestItemsToTree(size_t numChildren,
                                    size_t depth)
{
    int image = (FacesApp::getFacesApp())->ShowImages() ? MyTreeCtrl::TreeCtrlIcon_Folder : -1;
    
	//Root
	m_rootId = AddRoot(wxT("Acervo CPDOC-FGV"),
                                  image, image,
                                  new MyTreeItemData(wxT("Root item")));
    if ( !HasFlag(wxTR_HIDE_ROOT) && image != -1 )
    {
        SetItemImage(m_rootId, TreeCtrlIcon_FolderOpened, wxTreeItemIcon_Expanded);
    }

    AddItemsRecursively(m_rootId, numChildren, depth, 0);

    // set some colours/fonts for testing
    if ( !HasFlag(wxTR_HIDE_ROOT) )
        SetItemFont(m_rootId, *wxITALIC_FONT);

    wxTreeItemIdValue cookie;
    wxTreeItemId id = GetFirstChild(m_rootId, cookie);
    SetItemTextColour(id, *wxBLUE);

    id = GetNextChild(m_rootId, cookie);
    id = GetNextChild(m_rootId, cookie);
    SetItemTextColour(id, *wxRED);
    SetItemBackgroundColour(id, *wxLIGHT_GREY);
}

void MyTreeCtrl::GetItemsRecursively(const wxTreeItemId& idParent,
                                     wxTreeItemIdValue cookie)
{
    wxTreeItemId id;
	//legal!
    if ( !cookie )
        id = GetFirstChild(idParent, cookie);
    else
        id = GetNextChild(idParent, cookie);

    if ( !id.IsOk() )
        return;

    wxString text = GetItemText(id);
    
	
#ifdef _DEBUG
	wxLogMessage(text);
#endif
	

    if (ItemHasChildren(id))
        GetItemsRecursively(id);

    GetItemsRecursively(idParent, cookie);
}


void MyTreeCtrl::LogEvent(const wxChar *name, const wxTreeEvent& event)
{
   #ifdef _DEBUG
	wxTreeItemId item = event.GetItem();
    wxString text;
    if ( item.IsOk() )
        text << _T('"') << GetItemText(item).c_str() << _T('"');
    else
        text = _T("invalid item");
    
	wxLogMessage(wxT("%s(%s)"), name, text.c_str());
	
        
	#endif
}


// avoid repetition



#define TREE_EVENT_HANDLER(name)                                 \
void MyTreeCtrl::name(wxTreeEvent& event)                        \
{                                                                \
    LogEvent(_T(#name), event);                                  \
    SetLastItem(wxTreeItemId());                                 \
    event.Skip();                                                \
}




void MyTreeCtrl::ExpandFaces(void){

	wxTreeItemIdValue cookie_dir, cookie_photo;		
	wxTreeItemId item_id = GetSelection();
	if (!item_id)
		item_id = GetRootItem();

	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, minimiza todas as faces de todas as colecoes
		if(item_id==m_rootId){					

			wxTreeItemId dir_id = GetFirstChild(item_id, cookie_dir);
			while( dir_id ){
				wxTreeItemId child_id = GetFirstChild(dir_id, cookie_photo);
				while( child_id ){
					Expand( child_id );
					child_id = GetNextChild( dir_id,  cookie_photo);
				}			
				dir_id = GetNextChild( item_id,  cookie_dir);
			}
			Refresh();

			return;
		}	

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o primeiro filho
		if(parent_id ==m_rootId){					
			wxTreeItemId child_id = GetFirstChild(item_id, cookie_photo);
			while( child_id ){
				Expand( child_id );
				child_id = GetNextChild( item_id,  cookie_photo);
			}			
			Refresh();
		}else{	
			
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			//se não, o avô é a raiz, entao item é uma imagem, procura próximo filho	do pai
			if(parent_parent_id ==m_rootId){		
				
				Expand(item_id);
				Refresh();

			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){					
				
					Expand( parent_id);
					Refresh();

				}
			}
		}

	}
}

void MyTreeCtrl::CollapseFaces(void){
	wxTreeItemIdValue cookie_dir, cookie_photo;		
	wxTreeItemId item_id = GetSelection();
	if (!item_id)
		item_id = GetRootItem();
	if(item_id){
		CHECK_ITEM( item_id );
		//se a raiz é selecionada, minimiza todas as faces de todas as colecoes
		if(item_id==m_rootId){					

			wxTreeItemId dir_id = GetFirstChild(item_id, cookie_dir);
			while( dir_id ){
				wxTreeItemId child_id = GetFirstChild(dir_id, cookie_photo);
				while( child_id ){
					Collapse( child_id );
					child_id = GetNextChild( dir_id,  cookie_photo);
				}			
				dir_id = GetNextChild( item_id,  cookie_dir);
			}
			Refresh();

			return;
		}	

		wxTreeItemId parent_id = GetItemParent(item_id);
		if(!parent_id){
			return;
		}
		CHECK_ITEM( parent_id );
		
		//se o pai é a raiz, entao item é um diretorio, pega o primeiro filho
		if(parent_id ==m_rootId){					
			wxTreeItemId child_id = GetFirstChild(item_id, cookie_photo);
			while( child_id ){
				Collapse( child_id );
				child_id = GetNextChild( item_id,  cookie_photo);
			}			
			Refresh();
		}else{	
			
			wxTreeItemId parent_parent_id = GetItemParent(parent_id );
			if(!parent_parent_id){
				return;
			}
			CHECK_ITEM( parent_parent_id );			
			//se não, o avô é a raiz, entao item é uma imagem, procura próximo filho	do pai
			if(parent_parent_id ==m_rootId){		
				
				Collapse(item_id);
				Refresh();

			}else{	
				
				wxTreeItemId parent_parent_parent_id = GetItemParent(parent_parent_id );		
				if(!parent_parent_parent_id){
					return;
				}
				CHECK_ITEM( parent_parent_parent_id );			
				//se não o bisaavô é a raiz, entao item é uma face
				if(parent_parent_parent_id ==m_rootId){					
				
					
					SelectItem( parent_id);
					Collapse( parent_id);
					Refresh();

				}
			}
		}

	}
}




#if (NAVEGADOR_VERSION >1)

void MyTreeCtrl::CopyItem(wxTreeItemId fromItem, wxTreeItemId toItem, bool copyItself = true, bool recall = false){
	
	MyTreeItemData *data =NULL;
	wxString text;
	int imgNum =-1;
	wxTreeItemIdValue cookie;
	wxTreeItemId src_id, dest_photo , dest2_photo ;
	
	if(copyItself){
		data = (MyTreeItemData *)GetItemData(fromItem);
		text = GetItemText(fromItem);
		imgNum =GetItemImage(fromItem);
		dest_photo = InsertItem(toItem,NULL, text , imgNum, -1, new MyTreeItemData(data->GetDesc())	);
	}
	//copia de volta
	src_id = GetFirstChild(fromItem, cookie);
	while( src_id ){
		data = (MyTreeItemData *)GetItemData(src_id);
		text = GetItemText(src_id);
		imgNum =GetItemImage(src_id);

		if(copyItself){
			dest2_photo = InsertItem(dest_photo, NULL, text , imgNum, -1,   new MyTreeItemData(data->GetDesc())	);
		}else{
			dest_photo = InsertItem(toItem, NULL, text , imgNum, -1,  new MyTreeItemData(data->GetDesc()) );
			if(recall)
				CopyItem(src_id, dest_photo, false , false);
		}

		src_id = GetNextChild(fromItem  , cookie);
	}
}


void MyTreeCtrl::DoSortByStatus( bool reverse ){
	
	int imgNum =-1;
	
	//criar 4 grupos e cada um fica organizado por nome

	wxTreeItemIdValue cookie, cookie2;		
	wxTreeItemId photo_id;
	wxTreeItemId root_id = GetRootItem();
	
	//GetChildrenCount

	wxTreeItemId id_red		= AppendItem (root_id , wxT("Red")/* wxString */);
	wxTreeItemId id_yellow	= AppendItem (root_id , wxT("Yellow")/* wxString */);
	wxTreeItemId id_green	= AppendItem (root_id , wxT("Green")/* wxString */);
	wxTreeItemId id_blue	= AppendItem (root_id , wxT("blue")/* wxString */);
	
	wxTreeItemId dir_id = GetFirstChild(root_id, cookie);
	
	while(dir_id){
		// && dir_id !=id_red && dir_id !=id_yellow && dir_id !=id_green && dir_id !=id_blue){
		//copia elementos filhos de um dir (dir_id) para as categorias
		photo_id = GetFirstChild(dir_id, cookie2);
		while( photo_id ){
			
			imgNum =GetItemImage(photo_id);
			switch (imgNum){
				case TreeCtrlIcon_New:
					CopyItem(photo_id, id_red , true);
					 
				break;
				case TreeCtrlIcon_InAnalisys:	
					CopyItem(photo_id, id_yellow , true);
					 
				break;
				case TreeCtrlIcon_Approved:
					CopyItem(photo_id, id_green , true);
					 
				break;
				case TreeCtrlIcon_Revised:
					CopyItem(photo_id, id_blue , true);
					 
				break;
			}

			photo_id = GetNextChild(dir_id , cookie2);
		}
		 
		

		//ordena cada categoria
		DoSortChildren(id_red , true);//reverse);
		DoSortChildren(id_yellow ,  true);//reverse);
		DoSortChildren(id_green ,  true);//reverse);
		DoSortChildren(id_blue ,  true);//reverse);

		//apaga originais:
		DeleteChildren(dir_id);
		
		if(reverse){
			CopyItem(id_red, dir_id, false , true);
			CopyItem(id_yellow, dir_id, false, true);
			CopyItem(id_green, dir_id, false, true);
			CopyItem(id_blue, dir_id, false, true);
		}else{
			CopyItem(id_blue, dir_id, false, true);
			CopyItem(id_green, dir_id, false, true);
			CopyItem(id_yellow, dir_id, false, true);
			CopyItem(id_red, dir_id, false, true);
		}


		//apaga elementos  
		DeleteChildren(id_red);
		DeleteChildren(id_yellow);
		DeleteChildren(id_green);
		DeleteChildren(id_blue);
		dir_id = GetNextChild(root_id,cookie);
	}	


	Delete(id_red);
	Delete(id_yellow);
	Delete(id_green);
	Delete(id_blue);
	
}

void MyTreeCtrl::DoSortByName( bool reverse ){
	
	wxTreeItemIdValue cookie;		
	
	wxTreeItemId root_id = GetRootItem();
	wxTreeItemId item_id = GetFirstChild(root_id, cookie);
	
	while(item_id ){
		DoSortChildren(item_id , reverse);
		item_id = GetNextChild(root_id,cookie);
	}
}

//void MyTreeCtrl::OnCompareItems(



#endif //version




TREE_EVENT_HANDLER(OnBeginRDrag)
TREE_EVENT_HANDLER(OnDeleteItem)
TREE_EVENT_HANDLER(OnGetInfo)
TREE_EVENT_HANDLER(OnSetInfo)
TREE_EVENT_HANDLER(OnItemExpanded)
TREE_EVENT_HANDLER(OnItemExpanding)
TREE_EVENT_HANDLER(OnItemCollapsed)
//TREE_EVENT_HANDLER(OnSelChanged)
//crisnv: TREE_EVENT_HANDLER(OnSelChanging)
//TREE_EVENT_HANDLER(OnCo

#undef TREE_EVENT_HANDLER


