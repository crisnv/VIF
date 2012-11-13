#include "defs.h"
#include "fotografia.h"


#include "wx/wx.h"

Fotografia::Fotografia(const char *filename, const  char *dirname){

	m_aprovada = e_brandNew;

	m_dirname = (char*)malloc(sizeof(char)*(1+strlen(dirname)));
	strcpy_s(m_dirname, (1+strlen(dirname)),dirname);

	m_imgname = (char*)malloc(sizeof(char)*(1+strlen(filename)));
	strcpy_s(m_imgname, (1+strlen(filename)),filename);

	m_logname = (char*)malloc(sizeof(char)*(1+strlen(filename)));
	strcpy_s(m_logname, (1+strlen(filename)),filename);
	
	

	char *c= strrchr(m_logname, '.');
	int cc=strlen(c);
	if(c!= NULL &&strlen(c)>=4 ){
		*(++c) = 'l';
		*(++c) = 'o';
		*(++c) = 'g';
		*(++c) = '\0';
	}
	//ate aqui ok

	ReadPhotoLog();
}


Fotografia::~Fotografia(void){
	
	//SavePhotoLog();
	
	if(m_logname)
		delete m_logname;

	if(m_imgname)
		delete m_imgname;

	if(m_dirname)
		delete m_dirname;
}


	
void Fotografia::SavePhotoLog( int realw, 
	int  realh  ){
	int i=0, error=0, nread=0;
	FILE *file=NULL;
	
	
	if(m_logname==NULL){
		return ;
	}
	
	char out[128];
	sprintf(out, "%s/%s",m_dirname, m_logname);
	error = fopen_s( &file, out ,"w");
	if(error){ 
		return ;
	}


	
	nread = fprintf(file, "%f\n", NAVEGADOR_VERSION);

	if(m_aprovada==e_approved){
		nread = fprintf(file, "APPROVED_IMAGE\n"); 
	}
#if	(NAVEGADOR_VERSION > 1)
	else  if(m_aprovada==e_revised)
	{
		nread = fprintf(file, "REVISED_IMAGE\n"); 
	}
#endif	
	else if(m_aprovada==e_brandNew &&  m_bbfaces.size()==0)
	{
		nread = fprintf(file, "NEW_IMAGE\n"); 
	}else //if(m_aprovada==e_inAnalisys)
	{
		m_aprovada =e_inAnalisys;
		nread = fprintf(file, "IN_ANALISYS_IMAGE\n"); 
	}


	if(m_aprovada !=e_brandNew){
	
		float rx=0, ry=0, rw, rh;
		for(i=0; i<m_bbfaces.size();i++){
			if(m_bbfaces[i].approved){
		
			/*nread = fprintf(file, "%d %d %d %d %s<\n", 
				m_bbfaces[i].x, m_bbfaces[i].y, m_bbfaces[i].w, m_bbfaces[i].h, m_bbfaces[i].nome);
			*/
			nread = fprintf(file, "%f %f %f %f %d %d %s<\n", 
				m_bbfaces[i].x/(float)realw, m_bbfaces[i].y/(float)realh,
				m_bbfaces[i].w/(float)realw, m_bbfaces[i].h/(float)realh, realw, realh, m_bbfaces[i].nome);
		
			}
		}
	}

	if(file)
		fclose(file);
}

int Fotografia::ReadPhotoLog(void){
	int realw=0, realh= 0;
				
	int error=0, nread=0;
	FILE *file=NULL;
	retang r;
	
	m_aprovada =e_brandNew; 

	if(m_logname==NULL){
		//teste
		wxString strMsg;
		strMsg.Printf(_("Nao abriu log da imagem (%s)"),  m_logname);	
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING| wxOK ) ;
		return -1;
	}


	char out[128];
	sprintf(out, "%s\\%s",m_dirname, m_logname);//troquei a barra
	error = fopen_s( &file, out,"r");
	if(error){ 
		//aqui sai pq considera que 'e nova
		/*
		wxString strMsg;
		strMsg.Printf(_("Nao abriu log da imagem (erro 2) (%s)"),  m_logname);	
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING| wxOK ) ;
		*/
		return -2;
	}

	
	float version=0.0;
	nread = fscanf(file, "%f\n", &version);

	if(nread!=EOF /*&&version == NAVEGADOR_VERSION*/){
		
		char linha[64];
		nread = fscanf(file, "%s\n", linha);
		if(nread==EOF){
				m_aprovada= e_brandNew; 
		}else{
			if(linha[0]==','){
		
				nread = fscanf(file, "%s\n", linha);
		
			}

			if(strcmp(linha,"APPROVED_IMAGE")==0){
				m_aprovada= e_approved; 
			}
#if	(NAVEGADOR_VERSION > 1)
			else if(strcmp(linha,"REVISED_IMAGE")==0){
				m_aprovada= e_revised; 
			}
#endif
			else if(strcmp(linha,"NEW_IMAGE")==0){
				//;;poderia tbm apagar seu arquivo
				m_aprovada= e_brandNew;
			}
			else{
				m_aprovada= e_inAnalisys;
			}		
			r.approved=1;
			float rx=0, ry=0, rw, rh;
			
			// nread = fscanf(file, "%d %d %d %d ", &r.x,&r.y,&r.w,&r.h);
			///*
			nread = fscanf(file, "%f %f %f %f ",&rx, &ry,&rw,&rh);
			if(nread>0){
				if(rx<1.0 && ry<1.0 &&rw<1.0 && rh<1.0){ 
					nread = fscanf(file, "%d %d ",&realw,&realh);
				
					r.x = (int)(rx*realw);
					r.y = (int)(ry*realh);
					r.w = (int)(rw*realw);
					r.h = (int)(rh*realh);
				}else{
					r.x = (int)rx;
					r.y = (int)ry;
					r.w = (int)rw;
					r.h = (int)rh;
				}
			}	 
			char letra=' ';
			int cindex=0;
			nread = fscanf(file, "%c", &letra);
			while(nread != EOF && letra!='<' ){
				if(cindex<63){
					r.nome[cindex]=letra;
					cindex++;
				}
				nread = fscanf(file, "%c", &letra);
			}
			r.nome[cindex]='\0';

			while( nread != EOF ){
				if(r.nome[0]=='<')
					r.nome[0]='\0';

				m_bbfaces.push_back(r);
				//nread = fscanf(file, "%d %d %d %d ", &r.x,&r.y,&r.w,&r.h);
				nread = fscanf(file, "%f %f %f %f ",&rx, &ry,&rw,&rh);
				//if(nread>0)
				{
						if(rx<1.0 && ry<1.0 &&rw<1.0 && rh<1.0){ 
						nread = fscanf(file, "%d %d ",&realw,&realh);
				
						r.x = (int)(rx*realw);
						r.y = (int)(ry*realh);
						r.w = (int)(rw*realw);
						r.h = (int)(rh*realh);
					}else{
						r.x = (int)rx;
						r.y = (int)ry;
						r.w = (int)rw;
						r.h = (int)rh;
					}
				}
			
				letra=' ';
				cindex=0;
				nread = fscanf(file, "%c", &letra);
				while(letra!='<' && nread != EOF ){
					if(cindex<63){
						r.nome[cindex]=letra;
						cindex++;
					}
					nread = fscanf(file, "%c", &letra);
				}
				r.nome[cindex]='\0';

			}
		}
	}

	if(file)
		fclose(file);
	
	return 0;
}




int Fotografia::GetBB(const char* name){
	int i=0;
	for(i=0; i<m_bbfaces.size(); i++){
		if(	strcmp(name,m_bbfaces[i].nome) == 0){
		return i;
		}
	}
	return -1;
}
int Fotografia::GetBB(int x, int y){
	int i=0;
	for(i=0; i<m_bbfaces.size(); i++){

		if(	x>= m_bbfaces[i].x
			&& x<= (m_bbfaces[i].x+m_bbfaces[i].w)
			&& y>= m_bbfaces[i].y
			&& y<= (m_bbfaces[i].y + m_bbfaces[i].h)
		){
		return i;
		}
	}
	return -1;
}


void Fotografia::DeleteBBNum(int num){
	
	if(num>=0 &&num<m_bbfaces.size()){
		vector<retang>::iterator elemento=  m_bbfaces.begin()+num;
		m_bbfaces.erase(elemento);
	}
}

void Fotografia::GetBB(int index, int &x, int &y, int &bbw, int &bbh, bool &approved){
	if(index>=0 && index< m_bbfaces.size()){
		x = m_bbfaces[index].x;
		y = m_bbfaces[index].y;
		bbw = m_bbfaces[index].w;
		bbh = m_bbfaces[index].h;
		approved= m_bbfaces[index].approved;
	}
}


void Fotografia::ValidaBB(int BBNum, const char *name){
	if(BBNum >=0 && BBNum< m_bbfaces.size()){
		m_bbfaces[BBNum].approved=true;
		if(name !=NULL){
			strcpy_s(m_bbfaces[BBNum].nome, 64, name);
		}
	}
}

void Fotografia::ValidaFoto(void){
	m_aprovada=e_approved;
	for(int i=0;i< m_bbfaces.size();i++){
		if(!m_bbfaces[i].approved ){
			vector<retang>::iterator elemento=  m_bbfaces.begin()+i;
			m_bbfaces.erase(elemento);
			i--;
		}
	}
}

#if	(NAVEGADOR_VERSION > 1)
void Fotografia::RevisaFoto(void){
	m_aprovada=e_revised;
	for(int i=0;i< m_bbfaces.size();i++){
		if(!m_bbfaces[i].approved ){
			vector<retang>::iterator elemento=  m_bbfaces.begin()+i;
			m_bbfaces.erase(elemento);
			i--;
		}
	}
}
#endif

void Fotografia::AddNewBB(int x0, int y0){
	retang r;
	r.x=max(0,x0);
	r.y=max(0,y0);
	r.w=r.h=2;
	r.nome[0]='\0';
	r.approved=false;
	m_bbfaces.push_back(r);
}

void Fotografia::EditBB(int x, int y, int numBB){
	

	if(numBB>=0 && numBB<m_bbfaces.size()){

		int w = GetWidth();
		int h = GetHeight();

		if(	x>m_bbfaces[numBB].x){
			m_bbfaces[numBB].w = min( x-m_bbfaces[numBB].x , w -m_bbfaces[numBB].x -1);
		}else{
			m_bbfaces[numBB].w = min( m_bbfaces[numBB].x-x , w -x);
			m_bbfaces[numBB].x = x;
		}
		if(m_bbfaces[numBB].w ==0)
			m_bbfaces[numBB].w =2;

		if(	y>m_bbfaces[numBB].y){
			m_bbfaces[numBB].h = min( y-m_bbfaces[numBB].y, h -m_bbfaces[numBB].y);
		}else{
			m_bbfaces[numBB].h = min( m_bbfaces[numBB].y-y, h -y);
			m_bbfaces[numBB].y = y;
		}		
		if(m_bbfaces[numBB].h ==0)m_bbfaces[numBB].h =2;
	}
}


void Fotografia::EditBB(int x, int y, int w, int h, int numBB){
	if(numBB>=0 && numBB<m_bbfaces.size()){
		
		m_bbfaces[numBB].x = x;
		m_bbfaces[numBB].y = y;
		m_bbfaces[numBB].w = w;
		m_bbfaces[numBB].h = h;
		if(m_bbfaces[numBB].w <=0)m_bbfaces[numBB].w =2;
		if(m_bbfaces[numBB].h <=0)m_bbfaces[numBB].h =2;
	}
}


void Fotografia::DesfazMarcacaoFoto(){

	m_aprovada = e_brandNew;
	m_bbfaces.clear();
	//SavePhotoLog();

}