#ifndef _NFGV_CANVAS
#define _NFGV_CANVAS


#include "wx/wx.h"


const double ZOOMSCALEFACTOR=2.0;

// Define a new canvas which can receive some events
class CanvasFoto: public wxScrolledWindow
{ 
public:

	CanvasFoto(wxWindow *parent, const wxPoint& pos, const wxSize& size);
    ~CanvasFoto(void);
    void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnMouseEvent(wxMouseEvent& event);

	int AlterarImagem();
	void DrawFaceCircleBB(int x, int y, int radius);
	void DrawFaceRectBB(int x, int y, int w, int h);
	

DECLARE_EVENT_TABLE()

private:
	//este bitmap é a img escalada para o canvas
	wxBitmap  *m_canvasBitmap;
	//bool m_has_changedIMG;

	int m_scroll_x,m_scroll_y;
	int m_scroll_ppux,m_scroll_ppuy;
	void AtualizaScroll(void);

	void OnMouseEvent_DEFAULT(wxMouseEvent& event);
	void OnMouseEvent_MOVE(wxMouseEvent& event);
	void OnMouseEvent_EDIT(wxMouseEvent& event);
	void OnMouseEvent_EDIT34(wxMouseEvent& event);
	void OnMouseEvent_ZOOMIN(wxMouseEvent& event);
	void OnMouseEvent_ZOOMOUT(wxMouseEvent& event);

	//bool m_repaintBitmap ;
public:
	int hasBitmap(void){return (m_canvasBitmap!=NULL);};
	double m_globalScale;
};


#endif