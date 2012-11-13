#include "comboDescritores.h"


void tComboDescritores::UpdateDescritorItens(Fundo *d){
	char *s;
	wxArrayString *as; 

	Clear();
	s = d->GetDirName();
	as =d->GetDescritores();
	
	if(s!=NULL){
		SetDirname(s);	
		Append(*as);
	}
}
