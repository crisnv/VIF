#include <vector>

#include "canvasFace.h"
#include "gerenciador.h"
#include "navegadorFGV.h"

using namespace std;

extern Gerenciador *g_ger;

class FacesMainFrame;

BEGIN_EVENT_TABLE(CanvasFace, wxScrolledWindow)
    EVT_PAINT(CanvasFace::OnPaint)
	EVT_SIZE(CanvasFace::OnSize)
	EVT_KEY_DOWN(FacesMainFrame::Onkeyboard)
END_EVENT_TABLE()

// Define a constructor for my canvas
CanvasFace::CanvasFace(wxWindow *parent, const wxPoint& pos, const wxSize& size):
 wxScrolledWindow(parent, wxID_ANY, pos, size)
{
	m_miniCanvasBitmap = (wxBitmap *) NULL;
}

 CanvasFace::~CanvasFace(){
	if (m_miniCanvasBitmap)
	{
		delete m_miniCanvasBitmap;
		m_miniCanvasBitmap = (wxBitmap *) NULL;
	}
 }
  


// Define the repainting behaviour
void CanvasFace::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);

	if ( m_miniCanvasBitmap && m_miniCanvasBitmap->Ok() )
    {	
		wxMemoryDC memDC;
        if ( m_miniCanvasBitmap->GetPalette() )
        {
            memDC.SetPalette(* m_miniCanvasBitmap->GetPalette());
            dc.SetPalette(* m_miniCanvasBitmap->GetPalette());
        }
        memDC.SelectObject(* m_miniCanvasBitmap);

        // Normal, non-transparent blitting
        dc.Blit(0, 0, m_miniCanvasBitmap->GetWidth(), m_miniCanvasBitmap->GetHeight(), & memDC, 0, 0, wxCOPY, false);
        memDC.SelectObject(wxNullBitmap);
    }
	/*
    if ( m_miniCanvasBitmap && m_miniCanvasBitmap->Ok() )
    {
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.SetPen(* wxRED_PEN);
		dc.SetBackground(*wxTRANSPARENT_BRUSH);
		


		wxMemoryDC memDC;
        memDC.SelectObject(* m_miniCanvasBitmap);

		// Transparent blitting if there's a mask in the bitmap
        dc.Blit(0 + m_miniCanvasBitmap->GetWidth() + 0, 0, m_miniCanvasBitmap->GetWidth(), m_miniCanvasBitmap->GetHeight(), & memDC, 0, 0, wxCOPY, true);
		memDC.SelectObject(wxNullBitmap);
	}
	*/
}



int CanvasFace::AlterarImagem(){
	
	int x=0,y=0,bbw=10,bbh=10, w=0,h=0;
	int tw=0,th=0;
	bool approved;
	if ( m_miniCanvasBitmap ){
		delete m_miniCanvasBitmap;
		m_miniCanvasBitmap=NULL;
	}
	g_ger->GetCurrentPhotoBB(x,y,bbw, bbh, approved);
	
	this->GetSize(&tw,&th);

	if(bbh!=0 && bbw !=0){
		h = th;
		w = (bbw*th)/bbh;
		if(w > tw){
			//troco tudo de novo para ajustar por largura
			w = tw;
			h = (bbh*tw)/bbw;
		}
		//this->SetSize(w,h);
	}else{
		w = tw;
		h = th;	
	}
	m_miniCanvasBitmap = g_ger->newRoiScaledBitmap(x,y,bbw, bbh, w, h);

	return 0;
}

void CanvasFace::OnSize(wxSizeEvent& event){
/*
	if (m_miniCanvasBitmap)
    {
		int w=0,h=0;
		//wxSize s = event.GetSize();
		this->GetSize(&w,&h);

		if(w>0&&h>0){
			delete(m_miniCanvasBitmap);
			m_miniCanvasBitmap = Gerenciador::newScaledBitmap(w,h);
			Refresh();

			wxPaintEvent p;
			OnPaint(p);
		}
	}
*/
}