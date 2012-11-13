#ifndef _LEGENDA_
#define _LEGENDA_


#include "wx/wx.h"


/*
Código de Classificação	
Número da Foto	
Legenda da Foto
*/
#ifndef	TAM_STRING_LEGENDA
#define	TAM_STRING_LEGENDA	(1024)		//4*
#endif

typedef struct TLegenda{
	int cod;
	int num;
	char sigla[6];//max de 5 letras
	char legenda[TAM_STRING_LEGENDA];
	char legendaProcessada[TAM_STRING_LEGENDA];
}tlegenda;

#include <vector>
using namespace std;

int readLegendaFile(const char* dirname,  vector <tlegenda> &l, wxArrayString *desc);



#endif
