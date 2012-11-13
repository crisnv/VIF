#include "gerenciador.h"


Gerenciador *Gerenciador::m_instance=NULL;
/*
char	Gerenciador::m_img_name[128]="";
wxImage	Gerenciador::m_img;
Fotografia *Gerenciador::m_CurrentPhoto = NULL;
*/

Gerenciador::Gerenciador(void){
	m_CurrentPhoto=NULL; 
	m_CurrentBBNum=-1;
	Fotografia::LoadDetectionCascades();
};	

Gerenciador *Gerenciador::GetInstance(){
	if(m_instance==NULL){
		m_instance=new Gerenciador();
		m_instance->m_DoFaceDetection =true;
		m_instance->m_ShowFacesBB=true;
		m_instance->m_ShowPersonagensBB=true;
	}

	return m_instance;
}
Gerenciador::~Gerenciador(){
	int i=0;
	Fundo* f=NULL;

	SaveCurrentPhoto();

	for(i=0; i<m_fundos.size(); i++){
		f = m_fundos[i];
		delete f;
	}
	m_fundos.clear();

	if (m_img.IsOk())
	{
		m_img_name[0] = '\0';
		m_img.Destroy();
	}
}

Fundo * Gerenciador::AddFundo(const char *dirName){
	Fundo *novo_fundo = new Fundo(dirName);
	if (novo_fundo){
		m_fundos.push_back(novo_fundo);
	}
	return novo_fundo;
}


Fundo *Gerenciador::GetFundo(const char *dirname){
	int i=0;
	Fundo *fd=NULL;
	
	for(i=0;i<m_fundos.size(); i++){
		fd = m_fundos[i];
		if(strcmp(fd->GetDirName(), dirname)==0){
			return fd;
		}
	}
	return NULL;
}




vector<retang> *Gerenciador::GetCurrentPhotoBBs(void){

	if(	m_CurrentPhoto != NULL){
		return m_CurrentPhoto->GetBB();
	}else
		return NULL;
}



const char *Gerenciador::GetCurrentPhotoBBName(void){

	if(	m_CurrentPhoto != NULL && 
		(m_CurrentBBNum>=0) && 
		(m_CurrentBBNum<m_CurrentPhoto->GetNumBB()) ){
		return m_CurrentPhoto->GetBBName(m_CurrentBBNum);
	}
	return 0;
}




void Gerenciador::GetCurrentPhotoBB(int &x, int &y, int &bbw, int &bbh, bool &approved){

	if(	m_CurrentPhoto != NULL){
		m_CurrentPhoto->GetBB(m_CurrentBBNum, x, y, bbw, bbh, approved);
	}
}


void Gerenciador::SetCurrentPhotoByName(const char *imgfile, const char *dir){
	
	if(	(	(dir == NULL)		||	(strcmp(dir ,"")==0 )	) && 
		(	(imgfile == NULL)	||	(strcmp(imgfile, "") == 0)))
	{
		m_CurrentPhoto = 0;	
		m_CurrentBBNum = 0;
		m_img_name[0] = '\0';
		m_img.Destroy();
		return;
	}
	
	Fundo *fd= GetFundo(dir);	
	char name[120];
	wxBitmap * bitmap = NULL;
	// wxBitmapRefData *GetBitmapData 


	wxString s="";
	if(dir!=NULL)
		s<<dir<<"\\"<<imgfile;
	else
		s<<imgfile;


	if(fd){
		Fotografia *fotoAtual = fd->GetPhotoByName(imgfile); 
		if(fotoAtual){
			m_CurrentPhoto = fotoAtual;	
			m_CurrentBBNum = 0;
			
			

			strcpy(name,s);	
			const char *c= strrchr(name, '.');
			for(int l=0; l<strlen(name); l++)
				name[l] = tolower(name[l]);

			if(c==NULL){
				return;
			}
			else{
				if( strcmp(c, ".png")==0){
					bitmap = new wxBitmap(name, wxBITMAP_TYPE_PNG);
				}else if( strcmp(c, ".jpg")==0 || strcmp(c, ".jpeg")==0){
					bitmap = new wxBitmap(name, wxBITMAP_TYPE_JPEG);
				}else if( strcmp(c, ".tif")==0 || strcmp(c, ".tiff")==0){
					//esse daqui que emite warning
					bitmap = new wxBitmap(name, wxBITMAP_TYPE_TIF);
				}else if( strcmp(c, ".bmp")==0){
					bitmap = new wxBitmap(name, wxBITMAP_TYPE_BMP);
				}else if(strcmp(c, ".gif")==0){
					bitmap = new wxBitmap(name, wxBITMAP_TYPE_GIF);
				}else{
					wxMessageBox(wxString::Format(wxT("Formato inválido")),
							 _T("Formato"), wxOK | wxICON_INFORMATION);
					return;
				}
			}

			if ( bitmap && !bitmap->IsOk()){
				delete bitmap;
				bitmap=0;
			}
			else{
				strcpy_s(m_img_name,128, name);
				m_img.Destroy(); 
				m_img = (bitmap->ConvertToImage()); 
				delete (bitmap);
				bitmap=0;


				if(m_DoFaceDetection 
				&& (m_CurrentPhoto->isBrandNew())
					//&& !(m_CurrentPhoto->isApproved())
					){
					m_CurrentPhoto->DetectFaces( &m_img );
				}else if(!(m_CurrentPhoto->isBrandNew()))
				{
					//m_CurrentPhoto->loadFaces();
					//retira nomes já classificados da legenda e coloca na combo personagens

				}







			}
		}
	}
}



wxBitmap* Gerenciador::newCopyBitmap(void){
	if(m_img.IsOk()){

		int w =m_img.GetWidth();
		int h =m_img.GetHeight();
		return (new wxBitmap(m_img.Scale(w,h)));
	}
	else
		return NULL;
}
wxBitmap* Gerenciador::newScaledBitmap(int w, int h){
	if(m_img.IsOk())
		return (new wxBitmap(m_img.Scale(w,h)));
	else
		return NULL;
}

wxBitmap* Gerenciador::newRoiScaledBitmap(int x, int y, int bbw, int bbh, int w, int h){
	if(m_img.IsOk()){
		
		x = max(0,x);
		y = max(0,y);
		bbw = min(bbw, m_img.GetWidth()-x-1);
		bbh = min(bbh, m_img.GetHeight()-y-1);
		wxImage roi = m_img.GetSubImage(wxRect(	x,
												y,
												bbw,
												bbh));
		wxBitmap *bmp = new wxBitmap(roi.Scale(w,h));
		return (bmp);
	}
	else
		return NULL;
}




void Gerenciador::PreviousBB(void){
	if(m_CurrentPhoto){
		m_CurrentBBNum--;
		if(m_CurrentBBNum <0)
			m_CurrentBBNum= m_CurrentPhoto->GetNumBB()-1;
	}
}
void Gerenciador::NextBB(void){
	if(m_CurrentPhoto){
		m_CurrentBBNum++;
		if(m_CurrentBBNum >= m_CurrentPhoto->GetNumBB())
			m_CurrentBBNum=0;
	}
}
void Gerenciador::FirstBB(void){
	m_CurrentBBNum=0;
}
void Gerenciador::LastBB(void){
	if(m_CurrentPhoto){
	m_CurrentBBNum =  m_CurrentPhoto->GetNumBB()-1;
	}
}


const char*Gerenciador::GetBBNameforPosition(int x, int y){
	int n = m_CurrentPhoto->GetBB(x,y);
	if(n< 0)
		return NULL;
	return m_CurrentPhoto->GetBBName(n);
}


void Gerenciador::SelectBBforPosition(int x, int y){
	if(m_CurrentPhoto){
		m_CurrentBBNum = m_CurrentPhoto->GetBB(x,y);
	}
}

void Gerenciador::SelectBBforName(const char*name){
	if(m_CurrentPhoto){
		m_CurrentBBNum = m_CurrentPhoto->GetBB(name);
	}
}
	
void Gerenciador::CheckBB(const char *name){
	if(m_CurrentPhoto){
		if(name==NULL){
			m_CurrentPhoto->ValidaBB(m_CurrentBBNum);
		}else{
			m_CurrentPhoto->ValidaBB(m_CurrentBBNum,name);
		}
	}
}
void Gerenciador::DeleteBB(void){
	if(m_CurrentPhoto){
		m_CurrentPhoto->DeleteBBNum(m_CurrentBBNum);
		if(m_CurrentBBNum>0){
		m_CurrentBBNum--;
		}		
	}
}

void Gerenciador::ValidaFoto(void){
	if(m_CurrentPhoto){
		m_CurrentPhoto->ValidaFoto();
		m_CurrentPhoto->SavePhotoLog(m_img.GetWidth(),m_img.GetHeight() );
	}	
}


void Gerenciador::DesfazValidaFoto(void){
	if(m_CurrentPhoto){
		m_CurrentPhoto->DesfazValidaFoto();
		m_CurrentPhoto->SavePhotoLog(m_img.GetWidth(),m_img.GetHeight() );
	}	
}

#if	(NAVEGADOR_VERSION > 1)
void Gerenciador::RevisaFoto(void){
	if(m_CurrentPhoto){
		m_CurrentPhoto->RevisaFoto();
		m_CurrentPhoto->SavePhotoLog(m_img.GetWidth(),m_img.GetHeight() );
	}	
}
void Gerenciador::DesfazRevisaFoto(void){
	if(m_CurrentPhoto){
		m_CurrentPhoto->DesfazRevisaFoto();
		m_CurrentPhoto->SavePhotoLog(m_img.GetWidth(),m_img.GetHeight() );
	}	
}
#endif
void Gerenciador::DesfazMarcacaoFoto(void){
	if(m_CurrentPhoto){
		m_CurrentPhoto->DesfazMarcacaoFoto();
		m_CurrentPhoto->SavePhotoLog(m_img.GetWidth(),m_img.GetHeight() );
	}	
}




void Gerenciador::SaveCurrentPhoto(void){
	if(m_CurrentPhoto){
		m_CurrentPhoto->SavePhotoLog(m_img.GetWidth(),m_img.GetHeight() );
	}	
}


void Gerenciador::AddNewBB(int x0, int y0){

	if(m_CurrentPhoto){
		m_CurrentPhoto->AddNewBB(x0,y0);
		m_CurrentBBNum = m_CurrentPhoto->GetNumBB()-1;
	}
}


void Gerenciador::EditBB(int x, int y){
	if(m_CurrentPhoto){
		m_CurrentPhoto->EditBB(x,y,m_CurrentBBNum);
	}
}
void Gerenciador::EditBB(int x, int y, int w, int h){
	if(m_CurrentPhoto){
		m_CurrentPhoto->EditBB(x,y,w,h,m_CurrentBBNum);
	}
}



bool Gerenciador::isPersonagem(const char *name){
	int i;
	int n = m_CurrentPhoto->GetNumBB();
	const char *bbname = NULL;

	for(i=0; i<n; i++){

		bbname = m_CurrentPhoto->GetBBName(i);
		if(strcmp(bbname, name)==0)
			return true;		
	}
	return false;
}

void Gerenciador::DetectFaces(void){

	m_CurrentPhoto->DetectFaces( &m_img );

}