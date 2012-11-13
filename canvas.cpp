#include <vector>

#include "canvas.h"
#include "gerenciador.h"
#include "navegadorFGV.h"
#include "menuAndControlsIds.h"

class FacesApp;
class FacesMainFrame;


using namespace std;

extern Gerenciador *g_ger;


// Define a constructor for my canvas
CanvasFoto::CanvasFoto(wxWindow *parent, const wxPoint& pos, const wxSize& size):
 wxScrolledWindow(parent, wxID_ANY, pos, size)
{
	m_canvasBitmap = (wxBitmap *) NULL;
	m_globalScale = 1.0;

 
	m_scroll_x=m_scroll_y=0;
	m_scroll_ppux=m_scroll_ppuy=10;

	//m_repaintBitmap =true;

 }

 
CanvasFoto::~CanvasFoto()
{
	if (m_canvasBitmap)
	{
		delete m_canvasBitmap;
		m_canvasBitmap = (wxBitmap *) NULL;
	}
}

// Define the repainting behaviour
int CanvasFoto::AlterarImagem(void){

	int w=0,h=0;
	int ww=0,wh=0;
	this->GetSize(&ww,&wh);

	if ( m_canvasBitmap ){
		delete m_canvasBitmap;
		m_canvasBitmap=NULL;
	}

	g_ger->GetImgDimensions(w,h);

	m_globalScale = 1.0;	
	while( (w*m_globalScale > ww) || (h*m_globalScale>wh))
	{
		m_globalScale /=ZOOMSCALEFACTOR;
	}

	m_canvasBitmap = g_ger->newScaledBitmap(w*m_globalScale, h*m_globalScale);

	m_scroll_x=0;
	m_scroll_y=0;
	AtualizaScroll();
	return 0;
}
