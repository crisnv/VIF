#ifndef _MENU_AND_CONTROL_IDS_
#define _MENU_AND_CONTROL_IDS_


typedef
enum{
	CUR_DEFAULT=0,
	CUR_MOVE,
	CUR_EDIT,
	CUR_EDIT34,
	CUR_ZOOMIN,
	CUR_ZOOMOUT
}cursorType;


// menu and control ids
enum
{

	CNavegFGV_LoadDir		= 999,
	CNavegFGV_CloseDir		= 1000,
	CNavegFGV_LoadImgFile	= 1001,
	CNavegFGV_SaveImgFile	= 1002,
	CNavegFGV_Button_PersonCheck,
	CNavegFGV_Button_PersonDelete,
	CNavegFGV_Button_PersonPrevious,
	CNavegFGV_Button_PersonNext,
	CNavegFGV_Button_PersonFirst,
	CNavegFGV_Button_PersonLast,

	

	CNavegFGV_Button_DefautCursor,
	CNavegFGV_Button_AutoDetect, 
    CNavegFGV_Button_MoveCursor,
    CNavegFGV_Button_PersonDraw,
	CNavegFGV_Button_PersonDraw34,
	CNavegFGV_Button_ZoomOut,
	CNavegFGV_Button_ZoomIn,
    
	//verde:
	CNavegFGV_Button_PhotoCheck,
	//amarelo:
	CNavegFGV_Button_PhotoInprogress,
	//red:
	CNavegFGV_Button_PhotoDelete,
	//azul:
	CNavegFGV_Button_PhotoApprove,


	CNavegFGV_Button_PhotoPrevious,
	CNavegFGV_Button_PhotoNext,
	CNavegFGV_Button_PhotoFirst,
	CNavegFGV_Button_PhotoLast,
    

	CNavegFGV_Button_SortByName,
	CNavegFGV_Button_SortByStatus,
	CNavegFGV_Button_CollapseFaces,
	CNavegFGV_Button_ExpandFaces,

	CNavegFGV_DetectFaces,
	CNavegFGV_DetectPersonagens, 
	
	CNavegFGV_ViewPersonagens,
	CNavegFGV_ViewFaces,

	CNavegFGV_ViewCharacter, 
	CNavegFGV_ViewRelations,

	
	CNavegFGV_Quit = wxID_EXIT,
    CNavegFGV_Help = wxID_HELP,
	CNavegFGV_About = wxID_ABOUT,
    CNavegFGV_ResetStyle,
    CNavegFGV_Highlight,
    CNavegFGV_Dump,
    CNavegFGV_DumpSelected,
    CNavegFGV_Count,
    CNavegFGV_CountRec,
    CNavegFGV_Sort,
    CNavegFGV_SortRev,
    CNavegFGV_Rename,
    CNavegFGV_Delete,
    CNavegFGV_DeleteChildren,
    CNavegFGV_DeleteAll,
    CNavegFGV_Select,
    CNavegFGV_Unselect,
    CNavegFGV_Ctrl = 10000
};

#endif