//#include "dicionario.h"
#include "fundo.h"


int Fundo::LoadDescritors(void){
	//AddDescritor(wxString dirname, wxArrayString & s){

	FILE *file=NULL;
	int nread=0, error=0, i=0;
	char buf[256], letra;
	char filename[128];
	sprintf(filename, "%s\\descritores.txt", m_dirname);//dirname.c_str());

	error = fopen_s( &file, filename,"r");
	if(error){		
		sprintf(filename, "descritores.txt");
		error = fopen_s( &file, filename,"r");
		if(error){ 
			//mostrar dialogo de falta de descritores	
			wxString strMsg;
			strMsg.Printf(_("Não conseguiu encontrar descritores para o diretório selecionado."));		
			wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING | wxOK) ;
			return -1;
		}
	}

	do{
		
		letra = '\0';
		i=0;
		do{
			nread = fscanf_s(file, "%c", &letra, 256);
			buf[i] = letra;
			i++;
		}while( nread != EOF && letra !='\n' && letra !=10 && letra !='\0');

		buf[i]='\0';
		
		//retirar os espacos em branco no fim das palavras:
		int sl = strlen(buf) ;//-1;	//retorna tamanho 
		while(sl>0 && (buf[sl-1]==10 || buf[sl-1]==' ')){// ou ponto ou marcacoes tambem?
			sl--;
		}
		buf[sl]='\0';

		if(buf[0]!= '\0'){
			buf[i]='\0';
			//s.Add(buf);
			m_descritores.Add(buf);
		}
	}while( nread != EOF );
	

	if(file)
		fclose(file);
	
	return 0;
}
	