#include "stdlib.h"

#include "defs.h"
#include "fundo.h"
//#include "dicionario.h"


const char imageformat[NUM_FILE_FORMATS][5]={
"bmp", 
"jpg", 
"jpeg", 
//"gif",
"tif",
"tiff",
"ppm",
"png",
"pgm"
};

/*

*/
Fundo::Fundo(const char *dirName){

	int nread=0, i=0, acceptFormat = 0, error=0;
	FILE *in=NULL;
	char cmd[1000];
	char buf[256];
	char format[5];

	m_dirname = (char*)malloc(sizeof(char)*(1+strlen(dirName)));
	strcpy_s(m_dirname, (1+strlen(dirName)),dirName);

	// ou /s /B: /A-D-H  
	sprintf(cmd, "dir \"%s\\\"*.jpeg  \"%s\\\"*.jpg  \"%s\\\"*.bmp  \"%s\\\"*.tif \"%s\\\"*.tiff \"%s\\\"*.png /B >dir.txt " /* |notepad dir.txt" */ 
		, dirName, dirName, dirName, dirName, dirName, dirName);
	error = system(cmd);
	if(error) {//nao tem arq de imags dentro
		wxString strMsg;
		strMsg.Printf(_("Não foram encontradas imagens no diretório selecionado."));		
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING | wxOK) ;
		return;
	}

	error = fopen_s( &in, "dir.txt","r");
	if(error){ 
		wxString strMsg;
		strMsg.Printf(_("Não conseguiu listar imagens no diretório selecionado."));		
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING| wxOK ) ;
		return;
		 
	}
	nread = fscanf_s(in, "%s", buf, 256);

	do{
		char*point = strrchr(buf,'.');
		while(!point && nread != EOF ){
			int tam= strlen(buf);
			if(tam<256){
				buf[tam] = ' ';buf[tam+1] = '\0';
				tam++;
				nread = fscanf_s(in, "%s", &buf[tam], 256-tam);
			}
			point = strrchr(buf,'.');
		}
		
		for(int l=0; l<strlen(buf); l++)
			buf[l] = tolower(buf[l]);

		
		//Scan a string for the last occurrence of a character.
		point = strrchr(buf,'.');

		if(point){
			point++;
			for(i=0; i<5;i++){
				format[i] = point[i];
				if( point[i]=='\0'){
					break;
				}
			}

			acceptFormat = 0;
			for(i=0; i<NUM_FILE_FORMATS; i++){
				if(strcmp(format, imageformat[i]) == 0){
					acceptFormat = 1;
					break;
				}
			}

			if(acceptFormat){				
				Fotografia *foto = new Fotografia(buf, dirName);
				m_fotos.push_back(foto);
				
			}
		}

		nread = fscanf_s(in, "%s", buf, 256);
	}while( nread != EOF );
	

	if(in)
		fclose(in);	
	#ifndef _DEBUG
		system("erase dir.txt");
	#endif
	

}


Fundo::~Fundo(){
	int i=0;
	Fotografia* f;

	if(m_dirname)
		free(m_dirname);

	for(i=0; i<m_fotos.size(); i++){
		f = m_fotos[i];
		delete f;
	}
	m_fotos.clear();
}


	
Fotografia *Fundo::GetPhotoByName(const char *name){
int i=0;
	for(i=0;i<m_fotos.size();i++){
		if(0 == strcmp(m_fotos[i]->GetImgName(), name)){
			return m_fotos[i];
		}
	}
	return NULL;
}
	