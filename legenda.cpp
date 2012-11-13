#include <wchar.h>

#include "legenda.h"
#include <vector>


#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/log.h"
#endif 

const int tempBufSize  =128*2048;
char tempBuf[tempBufSize];

using namespace std;

int editProcessedLegend( char* leg, int legSize){
	int i=0, j=0;
	char textoLegenda[TAM_STRING_LEGENDA];
	/*
		if(leg[i]==' ' || leg[i]==';' || isalpha(leg[i])|| iswalpha(leg[i])
			//			|| (leg[i] >='a' && leg[i] <='z') 			|| (leg[i] >='A' && leg[i] <='Z')
			){
			textoLegenda[j] = leg[i];
			j++;
			i++;
		}else{
			
			if(leg[i]=='(' ){
				while(leg[i]!='\0' && leg[i]!=')' && i<legSize){
					i++;
				}
				
				if(i<legSize && leg[i]==')') i++;
			}
			if(leg[i]=='.' || leg[i]=='/' || leg[i]==':' ){
				textoLegenda[j] = ';';
				j++;
				i++;
			}else{
				textoLegenda[j] = leg[i];
				j++;
				i++;
			}


		}
		*/
	while(i<TAM_STRING_LEGENDA && i<strlen(leg)  && i<legSize && j<512 && leg[i]!='\0' && i<legSize){

		
		if(  leg[i]==';' ||leg[i]==',' || leg[i]=='/' || leg[i]==':' ){
			textoLegenda[j] = ';';// leg[i];
			j++;
			i++;
		}else if( leg[i]=='.' || leg[i]==' ' || ( leg[i] >0 && leg[i] <128 && isalpha( leg[i]) ) ||
			( (128<= leg[i]) && (leg[i]<= 165)) || 
			(  leg[i] < 0)){
			textoLegenda[j] = leg[i];
			j++;
			i++;
		}
		//entre parenteses:
		else if(leg[i]=='(' ){
			textoLegenda[j] = ';';
			j++;
			while(leg[i]!='\0' && leg[i]!=')' && i<legSize){
				i++;
			}
				
			if(i<legSize && leg[i]==')')
				i++;
		}else{//ex aspas
			i++;
		}
	}

	textoLegenda[j]='\0';

	strcpy(leg, textoLegenda);
	return j;
}

int readLegendaFile(const char* dirname,  vector <tlegenda> &l, wxArrayString *desc){

	const int cLegSize = TAM_STRING_LEGENDA;
	int error =0, cod=0, num=0, i=0, j=0 ,nread=0 ,nreadbuf=0;
	char filename[120], textoLegenda[cLegSize], textoProcessado[cLegSize], letra;
	char sigla[6];

	FILE *file=NULL;
	tlegenda leg;
	
	sprintf_s(filename, 120, "%s\\legendas.txt", dirname);
	error = fopen_s( &file, filename,"r");
	if(error){ 
		//mostrar dialogo de falta de descritores	
		return -1;
	}	

	nread = fscanf_s(file, "%s", &leg.sigla,6);
	//pula linha:
	nread = fread(tempBuf,sizeof( char ), 1,file);
	
	

	//nread = fscanf_s(file, "%s\n", &tempBuf, cLegSize);
	nread = fread(tempBuf,sizeof( char ), tempBufSize,file);
		
	while( nread >0){
		
		int bi=0;
		while( bi<nread){
			cod= num=0;
			leg.cod = 0;
			leg.num = 0;
			leg.legenda[0] = '\0';
			leg.legendaProcessada[0] = '\0';
			memset(textoLegenda,0, cLegSize);
			textoLegenda[0] = '\0';
			textoProcessado[0] = '\0';
			letra = '\0';
		
			while(tempBuf[bi] >= '0' && tempBuf[bi]<='9' && bi<tempBufSize){
				letra =tempBuf[bi];
				cod = 10*cod + (int)letra -48;//48 'e 0
				bi++;
			}
			//nreadbuf = sscanf_s( &tempBuf[bi], "%d", &cod, sizeof(int));
			

			//pula separador:
			bi++;

			while(tempBuf[bi] >= '0' && tempBuf[bi]<='9' && bi<tempBufSize){
				letra =tempBuf[bi];
				num = 10*num + (int)letra -48;//48 'e 0
				bi++;
			}
			/*
			nreadbuf = sscanf_s( &tempBuf[bi], "%d", &num, sizeof(int));
			while(tempBuf[bi]>='0' && tempBuf[bi]<='9' && bi<tempBufSize){
				bi++;
			}
			*/
			//pula separador:
			bi++;
			nreadbuf = sscanf_s( &tempBuf[bi], "%c", &letra, sizeof(char));
	
			if(letra !='\n' && letra !='\0'){
				i=0;
				while(/*nread!=EOF && */ (letra =='\t' || letra ==' ')&& letra !='\n' && bi<tempBufSize){
					bi++;
					letra = tempBuf[bi];
					//nread = fscanf_s(file, "%c", &letra, 256);
				} 
				while(/*nread!=EOF && */ letra !='\t' && letra !='\n' && bi<tempBufSize && i< cLegSize-1){
					textoLegenda[i] = tempBuf[bi];
					i++;
					bi++;
					letra = tempBuf[bi];
					/*
					textoLegenda[i] = letra;
					i++;
					nread = fscanf_s(file, "%c", &letra, 256);
					*/
				}
				if(i == cLegSize-1)
					textoLegenda[i] ='\0' ;
				
				//entao ainda tem a 4a coluna
				if(letra =='\t')
				{
					j=0;
					while(/*nread!=EOF &&*/  ((letra =='\t' || letra ==' '))&& letra !='\n' && bi<tempBufSize){
						bi++;
						letra = tempBuf[bi];
						//nread = fscanf_s(file, "%c", &letra, 256);
					}
					/*
					while( letra !='\t' && letra !='\n' && letra !='\n'&& bi<tempBufSize) {
						textoProcessado[j] = letra;
						j++;
						bi++;
						letra = tempBuf[bi];
						//nread = fscanf_s(file, "%c", &letra, 256);
					}
					*/
					//pula separador: 
					bi++;
				}
				//entao nao tem a 4a coluna
				//2011 
				else
				{
					//pula separador:
					bi++;
				}


				strcpy(textoProcessado, textoLegenda);
				j =editProcessedLegend(textoProcessado , cLegSize);
				j =strlen(textoProcessado);

				
			}else{
				 //pula separador:
				 bi++;
				/*//	if(j==0){
						wxString strMsg;
						strMsg.Printf(_("A legenda da foto de código '%d' e número '%d' está vazia."), cod, num);		
						wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING | wxOK) ; 
				*/ 	
			 }
					
			
			if(textoLegenda[0]!= '\0')
			{
				while(i>0 && textoLegenda[i-1] == ' ')
					i--;
				while(j>0 && textoProcessado[j-1] == ' ')
					j--;

				textoLegenda[i] = '\0';
				textoProcessado[j] = '\0';
				leg.cod = cod;
				leg.num = num;
				strcpy_s(leg.legenda,TAM_STRING_LEGENDA, textoLegenda);
				strcpy_s(leg.legendaProcessada, TAM_STRING_LEGENDA, textoProcessado);
				l.push_back(leg);
			}

		}

		nread = fread(tempBuf,sizeof( char ), tempBufSize,file);
	
	}

	if(file)
		fclose(file);
	
	return 0;
}