#include <vector>

#include "canvas.h"
#include "gerenciador.h"
#include "navegadorFGV.h"
#include "menuAndControlsIds.h"

class FacesApp;
class FacesMainFrame;


using namespace std;

extern Gerenciador *g_ger;

BEGIN_EVENT_TABLE(CanvasFoto, wxScrolledWindow)
    EVT_PAINT(CanvasFoto::OnPaint)
	EVT_SIZE(CanvasFoto::OnSize)
	EVT_MOUSE_EVENTS(CanvasFoto::OnMouseEvent)
	EVT_KEY_DOWN(FacesMainFrame::Onkeyboard)
END_EVENT_TABLE()

int eventCnt=0;



void CanvasFoto::AtualizaScroll(void){

	if(m_canvasBitmap ==NULL){
		return;
	}
	int ww=0,wh=0;
	this->GetSize(&ww,&wh);
	int iw =m_canvasBitmap->GetWidth();
	int ih =m_canvasBitmap->GetHeight();
/*
	if(iw >ww &&ih>wh){
		SetScrollbars(m_pixelsPUX, m_pixelsPUY, m_globalScale*iw/10,m_globalScale*ih/10);		  
	//(m_globalScale*w)/10.0, 		  (m_globalScale*h)/10.0, scroll_x,scroll_y,true);
	}else{
	}
*/

	SetScrollbars(m_scroll_ppux, m_scroll_ppuy, 
					(iw )/m_scroll_ppux,
					(ih )/m_scroll_ppuy,
					m_scroll_x,m_scroll_y);		  
//,true
/*		
	SetScrollbars(m_scroll_ppux, m_scroll_ppuy, 
					(/*m_globalScale* /iw -ww)/m_scroll_ppux,
					(/*m_globalScale* /ih -wh)/m_scroll_ppuy,
					m_scroll_x,m_scroll_y,true);		  
	SetScrollbars(
		m_scroll_ppux, m_scroll_ppuy,
				(m_globalScale*iw)/10.0,
				  (m_globalScale*ih)/10.0,
				  m_scroll_x,m_scroll_y,true);
*/
}


void CanvasFoto::OnPaint(wxPaintEvent& WXUNUSED(event))
{
#ifdef _DEBUG
	char line[64];
	sprintf_s(line, 64, "paint %d", eventCnt);
	eventCnt++;
	wxLogMessage(line);
#endif	

	SetDoubleBuffered(true);
	wxPaintDC dc(this);
	
	if ( m_canvasBitmap && m_canvasBitmap->Ok() )
    {	
		wxMemoryDC memDC;
		//if(m_repaintBitmap )
		{
			if ( m_canvasBitmap->GetPalette() )
			{
				memDC.SetPalette(* m_canvasBitmap->GetPalette());
				dc.SetPalette(* m_canvasBitmap->GetPalette());
			}
			memDC.SelectObject(* m_canvasBitmap);

			m_scroll_x=GetScrollPos(wxHORIZONTAL);
			m_scroll_y=GetScrollPos(wxVERTICAL);
			GetScrollPixelsPerUnit(&m_scroll_ppux,&m_scroll_ppuy);

			// Normal, non-transparent blitting
			//
			dc.Blit(0, 0, m_canvasBitmap->GetWidth(), m_canvasBitmap->GetHeight(), 
					& memDC, 
					//0, 0, 
					m_scroll_x *m_scroll_ppux,
					m_scroll_y *m_scroll_ppuy,
					wxCOPY, false);
		
			
			
			memDC.SelectObject(wxNullBitmap);
		
		}
		
       
    
		dc.SetBrush(*wxTRANSPARENT_BRUSH);
		dc.SetPen(* wxRED_PEN);
		dc.SetBackground(*wxTRANSPARENT_BRUSH);

		double sc_x=0, sc_y=0;
		wxImage *ger_img = g_ger->GetImg();
	
		if(ger_img && m_canvasBitmap){

			int iw =m_canvasBitmap->GetWidth();
			int ih =m_canvasBitmap->GetHeight();
	
			sc_x=(iw)/((double)ger_img->GetWidth());
			sc_y=(ih)/((double)ger_img->GetHeight());
			

			if( g_ger->m_ShowFacesBB ||  g_ger->m_ShowPersonagensBB ){
				vector<retang> *ptBBfaces = g_ger->GetCurrentPhotoBBs();
				if(ptBBfaces!=NULL){
				
					for(int r=0; r<ptBBfaces->size(); r++){
						if((*ptBBfaces)[r].approved){

							if(g_ger->m_ShowPersonagensBB ){
								dc.SetPen(* wxGREEN_PEN);
								dc.DrawRectangle(sc_x*(*ptBBfaces)[r].x-m_scroll_x *m_scroll_ppux,
										sc_y*(*ptBBfaces)[r].y-m_scroll_y *m_scroll_ppuy,
										sc_x*(*ptBBfaces)[r].w,
										sc_y*(*ptBBfaces)[r].h);
							}					
						}else{

							if( g_ger->m_ShowFacesBB) {
								dc.SetPen(* wxRED_PEN);
								dc.DrawRectangle(sc_x*(*ptBBfaces)[r].x-m_scroll_x *m_scroll_ppux,
											sc_y*(*ptBBfaces)[r].y-m_scroll_y *m_scroll_ppuy,
											sc_x*(*ptBBfaces)[r].w,
											sc_y*(*ptBBfaces)[r].h);
							}
						}
					}
				
				}

				
				int x=0, y=0, bbw=0, bbh=0;
				bool approved;
				g_ger->GetCurrentPhotoBB(x, y, bbw, bbh, approved);
				if(bbw>0 && bbh>0 && (  
					( !approved && g_ger->m_ShowFacesBB )||  
					( approved && g_ger->m_ShowPersonagensBB )
					)){
					//dc.SetPen(* wxCYAN_PEN );
					dc.SetPen( wxPen( wxT("yellow"), 4, wxDOT));//wxSOLID) );

					dc.DrawRectangle(sc_x*x-m_scroll_x *m_scroll_ppux,
									sc_y*y-m_scroll_y *m_scroll_ppuy,
									sc_x*bbw,
									sc_y*bbh);
				}
			}
		}		
/*
		wxMemoryDC memDC;
		memDC.SelectObject(* m_canvasBitmap);

		// Transparent blitting if there's a mask in the bitmap
		dc.Blit(0 + m_canvasBitmap->GetWidth() + 0, 0, m_canvasBitmap->GetWidth(), m_canvasBitmap->GetHeight(), & memDC, 0, 0, wxCOPY, true);
		memDC.SelectObject(wxNullBitmap);
	*/
	}
}






void CanvasFoto::OnSize(wxSizeEvent& event){
	/*
	
#ifdef _DEBUG
	char line[64];
	sprintf_s(line, 64, "Canvas size %d", eventCnt);
	wxLogMessage(line);
	eventCnt++;
#endif
	*/
	/*
	//wxSize s = event.GetSize();
	//m_globalScale=1.0;

	if (m_canvasBitmap)
    {
		int ww=0,wh=0;
		this->GetSize(&ww,&wh);

		int iw =m_canvasBitmap->GetWidth();
		int ih =m_canvasBitmap->GetHeight();
	
		if(iw>0&&ih>0){
			/*
			if ( m_canvasBitmap ){
				delete(m_canvasBitmap);
				m_canvasBitmap=NULL;
			}

			m_canvasBitmap = 
				g_ger->newScaledBitmap(iw, ih);
			* /
			SetScrollbars(10,10, m_globalScale*iw/10,m_globalScale*ih/10);	

			Refresh();
			wxPaintEvent p;
			OnPaint(p);
		}
	}
*/

}

/*
Tratar os seguintes casos:
	CUR_DEFAULT=0,
	CUR_MOVE,
	CUR_EDIT,
	CUR_EDIT34,
	CUR_ZOOMIN,
	CUR_ZOOMOUT
			GetHelpTextAtPoint
	*/
void CanvasFoto::OnMouseEvent(wxMouseEvent& event){

#ifdef _DEBUG
		char line[64];
			/*
		sprintf_s(line, 64, "mouse %d", eventCnt);
		wxLogMessage(line);
		eventCnt++;*/
		sprintf_s(line, 64, " %d", GetFocus());
		wxLogMessage(line);
#endif	
		
	if(! event.Moving()){

			//m_repaintBitmap = true;
		switch (((FacesMainFrame *)FacesApp::getFacesMainFrame())->getSelectedCursor()){
	
			case CUR_DEFAULT:
				OnMouseEvent_DEFAULT(event);
				break;
			
			case CUR_MOVE:
				OnMouseEvent_MOVE(event);
				break;

			case CUR_EDIT:
				OnMouseEvent_EDIT(event);
				break;

			case CUR_EDIT34:
				OnMouseEvent_EDIT34(event);			
				break;

			case CUR_ZOOMIN:
				OnMouseEvent_ZOOMIN(event);
				break;

			case CUR_ZOOMOUT:
				OnMouseEvent_ZOOMOUT(event);
				break;
			
			default:
				break;
		}
	}
	else{
		wxImage *ger_img = g_ger->GetImg();
		if(ger_img && m_canvasBitmap){
			wxPoint pt = event.GetPosition();
			int iw =m_canvasBitmap->GetWidth();
			int ih =m_canvasBitmap->GetHeight();
			//qual a BB da posicao?
			const char*name = g_ger->GetBBNameforPosition(
				((pt.x+m_scroll_x*m_scroll_ppux)/(double)iw)*(ger_img->GetWidth()),
				((pt.y+m_scroll_y*m_scroll_ppuy)/(double)ih)*(ger_img->GetHeight())
				);
		
			this->SetToolTip(name);
		}

	}
//*
#ifdef _DEBUG
	//mudar para mostrar no status
	//char line[64];
	wxPoint pt = event.GetPosition();

	if(m_canvasBitmap!=NULL){
		sprintf_s(line, 64, "%d  %d %d  %d  %.2lf", 
			pt.x,pt.y, 
			m_canvasBitmap->GetWidth(),m_canvasBitmap->GetHeight(),m_globalScale);
		wxLogMessage(line);

		//se for dentro arrasta, se perto de borda alarga
		//g_ger->EditBB( arrastando);
	}
#endif
//*/
}



void CanvasFoto::OnMouseEvent_DEFAULT(wxMouseEvent& event){

	wxImage *ger_img = g_ger->GetImg();
	if(!(ger_img && ger_img->IsOk())){
		return;
	}
	
	if(m_canvasBitmap==NULL)return;
	
	if (event.LeftUp() )
    {
		wxPoint pt = event.GetPosition();
		int iw =m_canvasBitmap->GetWidth();
		int ih =m_canvasBitmap->GetHeight();
			
		g_ger->SelectBBforPosition(
			((pt.x+m_scroll_x*m_scroll_ppux)/(double)iw)*(ger_img->GetWidth()),
			((pt.y+m_scroll_y*m_scroll_ppuy)/(double)ih)*(ger_img->GetHeight())
			);
		
		const char * bbName = g_ger->GetCurrentPhotoBBName();
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateComboItemSelectedByName(bbName);

		((FacesMainFrame *)FacesApp::getFacesMainFrame())->AtualizaMiniCanvas();

		//aqui deveria ser pega filho com determinado nome:
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->AtualizaSelecaoArvore(bbName);		

		Refresh();
	}
}

void CanvasFoto::OnMouseEvent_MOVE(wxMouseEvent& event){

	static int x0=0,y0=0;
	//wxPoint pt = event.GetPosition();
	
	if(m_canvasBitmap==NULL){
		return;
	}

	int dcw, dch;
	wxClientDC dc(this);
	PrepareDC(dc);
	dc.GetSize(&dcw, &dch);
	wxPoint  p = event.GetLogicalPosition( dc) ;	
		
	if (event.LeftDown() )
    {
		/*x0 = pt.x;
		y0 = pt.y;
		*/
		x0 = p.x;
		y0 = p.y;
	}
    else if (event.Dragging() )
    {
		m_scroll_x=GetScrollPos(wxHORIZONTAL);
		m_scroll_y=GetScrollPos(wxVERTICAL);
						
		/*m_scroll_x = m_scroll_x-(pt.x-x0)/m_scroll_ppux;
		m_scroll_y = m_scroll_y-(pt.y-y0)/m_scroll_ppuy;
		x0 = pt.x;
		y0 = pt.y;
		*/
		m_scroll_x = m_scroll_x-(p.x-x0)/m_scroll_ppux;
		m_scroll_y = m_scroll_y-(p.y-y0)/m_scroll_ppuy;
		//x0 = p.x;		y0 = p.y;
		AtualizaScroll();
		Refresh();				
	
	}

}


void CanvasFoto::OnMouseEvent_EDIT(wxMouseEvent& event){

	static int x0=0,y0=0;
	wxPoint pt = event.GetPosition();
	


	wxImage *ger_img = g_ger->GetImg();
	if(!(ger_img && ger_img->IsOk())){
		return;
	}
	if(m_canvasBitmap==NULL){
		return;
	}

	int iw =m_canvasBitmap->GetWidth();
	int ih =m_canvasBitmap->GetHeight();			
	
	if(pt.x <0 ||pt.y <0 || pt.x >=iw ||  pt.y>=ih )
		return;
		
	double scale_x	= (double)ger_img->GetWidth()/((double)iw);
	double scale_y = (double)ger_img->GetHeight()/((double)ih);


	if (event.LeftDown() )
    {
		x0 = scale_x*(pt.x+m_scroll_x*m_scroll_ppux);
		y0 = scale_y*(pt.y+m_scroll_y*m_scroll_ppuy);
		
		//if(	(x0 >=0) && (x0 < ger_img->GetWidth())	&&	(y0 >=0) && (y0 < ger_img->GetHeight()) )
		{
			g_ger->AddNewBB(x0,y0);
			Refresh();
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->m_miniCanvas->Refresh();	
			//se for dentro arrasta, se perto de borda alarga
			//g_ger->EditBB( inicio);
		}
	}
    else if (event.Dragging() )
    {
		int bbx=0, bby=0, bbw=2, bbh=2;

		bbw= (pt.x	+m_scroll_x*m_scroll_ppux)*scale_x - x0;
		if(bbw>0){
			bbx=x0;
		}else{
			bbx=(pt.x +m_scroll_x*m_scroll_ppux)
				*scale_x;
			bbw = -bbw;
		}

		bbh= (pt.y +m_scroll_y*m_scroll_ppuy)*scale_y - y0;
		if(bbh>0){
			bby=y0;
		}else{
			bby=(pt.y+m_scroll_y*m_scroll_ppuy)
				*scale_y;
			bbh = -bbh;
		}



	//	if(	(bbx >=0) && (bbx < ger_img->GetWidth())	&&	(bby >=0) && (bby < ger_img->GetHeight()) )
		{
			g_ger->EditBB( bbx,bby,bbw,bbh );
			Refresh();				
			((FacesMainFrame *)FacesApp::getFacesMainFrame())->m_miniCanvas->Refresh();	
		}
	
	}
	if (event.LeftUp() )
    {
		wxPoint pt = event.GetPosition();
		int iw =m_canvasBitmap->GetWidth();
		int ih =m_canvasBitmap->GetHeight();
			
		g_ger->SelectBBforPosition(
			((pt.x+m_scroll_x*m_scroll_ppux)/(double)iw)*(ger_img->GetWidth()),
			((pt.y+m_scroll_y*m_scroll_ppuy)/(double)ih)*(ger_img->GetHeight())
			);
		
		const char * bbName = g_ger->GetCurrentPhotoBBName();
		((FacesMainFrame *)FacesApp::getFacesMainFrame())->UpdateComboItemSelectedByName(bbName);


		((FacesMainFrame *)FacesApp::getFacesMainFrame())->AtualizaMiniCanvas();
		Refresh();
	}
}


void CanvasFoto::OnMouseEvent_EDIT34(wxMouseEvent& event){
	//ESSA FUNCAO FOI FEITA NO SISTEMA DE COORDENADAS DO DC
	static int x0=0,y0=0;
	
	wxImage *ger_img = g_ger->GetImg();
	if(!(ger_img && ger_img->IsOk())){
		return;
	}
	if(m_canvasBitmap==NULL){
		return;
	}
		
	int iw =m_canvasBitmap->GetWidth();
	int ih =m_canvasBitmap->GetHeight();			
	double scale_x	= (double)ger_img->GetWidth()/((double)iw);
	double scale_y = (double)ger_img->GetHeight()/((double)ih);
	
	wxPoint pt = event.GetPosition();
	
	if (event.LeftDown() )
    {	
		x0 = pt.x;
		y0 = pt.y;
	}
    else if (event.Dragging() )
    {
		wxPoint pt34;
		int bbx=0, bby=0, bbw=2, bbh=2;
		bool changeSign = false;
	    /*
		bbw= (pt.x	+m_scroll_x*m_scroll_ppux)*scale_x - x0;
		bbh= (pt.y +m_scroll_y*m_scroll_ppuy)*scale_y - y0;
		*/
		bbw= pt.x- x0;
		bbh= pt.y- y0;

		pt34.x = pt.x;
		pt34.y = pt.y;

		if(bbw * bbh<0)
			changeSign =true;

		//ainda tem sinal, por isso o quadrado!
		if(4*bbw*bbw> 3*bbh*bbh ){
			//usuario ta com largura maior que a proporçao -> aumento altura
			bbh = (4.0*bbw/3.0);
			if(changeSign )
				bbh = -bbh;

			pt34.y = (y0) +bbh;
			
		}else{
			//usuario ta com altura maior que a proporçao -> aumento largura
			bbw = (3.0*bbh/4.0);
			if(changeSign )
				bbw = -bbw;
			
			pt34.x = (x0) +bbw;
		}

		event.SetPosition(pt34);
			
	}

	OnMouseEvent_EDIT(event);
}



void CanvasFoto::OnMouseEvent_ZOOMIN(wxMouseEvent& event){

	if(m_canvasBitmap==0){
		return;
	}
	int iw =m_canvasBitmap->GetWidth();
	int ih =m_canvasBitmap->GetHeight();
	
	if (event.LeftDown() )
    {		
		if(ZOOMSCALEFACTOR*m_globalScale*iw<10000 &&
		   ZOOMSCALEFACTOR*m_globalScale*ih<10000){
			
			m_globalScale *= ZOOMSCALEFACTOR;

			if ( m_canvasBitmap ){
				delete(m_canvasBitmap);
				m_canvasBitmap=NULL;
			}
			
			int dcw, dch;
			wxClientDC dc(this);
			PrepareDC(dc);
			dc.GetSize(&dcw, &dch);

			// Find the logical position of the event given the DC
			wxPoint  p = event.GetLogicalPosition( dc) ;	

			GetScrollPixelsPerUnit(&m_scroll_ppux,&m_scroll_ppuy);


			float ratiox = (p.x - m_scroll_x*m_scroll_ppux)/(float)dcw; 
			float ratioy = (p.y - m_scroll_y*m_scroll_ppuy)/(float)dch; 
						
			m_scroll_x = (p.x*ZOOMSCALEFACTOR)/m_scroll_ppux;			
			m_scroll_y = (p.y*ZOOMSCALEFACTOR)/m_scroll_ppuy ;

			/*Centro:
			m_scroll_x = m_scroll_x -(0.5*dcw )/(float)m_scroll_ppux;
			m_scroll_y = m_scroll_y -(0.5*dch )/(float)m_scroll_ppuy;
			*/
			m_scroll_x = m_scroll_x -(ratiox*dcw  )/(float)m_scroll_ppux;
			m_scroll_y = m_scroll_y -(ratioy*dch  )/(float)m_scroll_ppuy;
			
			m_canvasBitmap = g_ger->newScaledBitmap(ZOOMSCALEFACTOR*iw,ZOOMSCALEFACTOR*ih);
			AtualizaScroll();
			Refresh(true);
		}
	}
}


void CanvasFoto::OnMouseEvent_ZOOMOUT(wxMouseEvent& event){

	if(m_canvasBitmap==0){
		return;
	}
	int iw =m_canvasBitmap->GetWidth();
	int ih =m_canvasBitmap->GetHeight();
	
	if (event.LeftDown() )
    {
		if(((m_globalScale*iw)/ZOOMSCALEFACTOR)>50&&
		   ((m_globalScale*ih)/ZOOMSCALEFACTOR)>50){
			
			m_globalScale /= ZOOMSCALEFACTOR;
		
			if ( m_canvasBitmap ){
				delete(m_canvasBitmap);
				m_canvasBitmap=NULL;
			}
			
			int dcw, dch;
			wxClientDC dc(this);
			PrepareDC(dc);
			dc.GetSize(&dcw, &dch);

			// Find the logical position of the event given the DC
			wxPoint  p = event.GetLogicalPosition( dc) ;	

			GetScrollPixelsPerUnit(&m_scroll_ppux,&m_scroll_ppuy);
			
			float ratiox = (p.x - m_scroll_x*m_scroll_ppux)/(float)dcw; 
			float ratioy = (p.y - m_scroll_y*m_scroll_ppuy)/(float)dch; 
								
			/*
			m_scroll_x /= ZOOMSCALEFACTOR;
			m_scroll_y /= ZOOMSCALEFACTOR;
			*/
			m_scroll_x = p.x/(ZOOMSCALEFACTOR*m_scroll_ppux);			
			m_scroll_y = p.y/(ZOOMSCALEFACTOR*m_scroll_ppuy);
			
			/*Centro:
			m_scroll_x = m_scroll_x -(0.5*dcw )/(float)m_scroll_ppux;
			m_scroll_y = m_scroll_y -(0.5*dch )/(float)m_scroll_ppuy;			
			*/
			m_scroll_x = m_scroll_x -( ratiox*dcw  )/(float)m_scroll_ppux;
			m_scroll_y = m_scroll_y -( ratioy*dch  )/(float)m_scroll_ppuy;
			
			m_canvasBitmap = g_ger->newScaledBitmap(iw/ZOOMSCALEFACTOR,ih/ZOOMSCALEFACTOR);
			AtualizaScroll();
			Refresh(true);
		}
	}	
}