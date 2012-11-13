#ifndef	_CANVAS_FACE_
#define _CANVAS_FACE_

#include "wx/wx.h"


// Define a new canvas which can receive some events
class CanvasFace: public wxScrolledWindow
{
	wxBitmap  *m_miniCanvasBitmap;

  public:
    CanvasFace(wxWindow *parent, const wxPoint& pos, const wxSize& size);
    ~CanvasFace(void);

    void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);

	int AlterarImagem();

DECLARE_EVENT_TABLE()
//private: bool m_has_changedIMG;
};


#endif