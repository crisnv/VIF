#ifndef	_FUNDO_
#define _FUNDO_

#include <vector>

#include "wx/wx.h"

#include "Fotografia.h"

using namespace std;


class Fundo{
public:

	//MyTreeCtrl::AddDir
	Fundo(const char *dirName);
	~Fundo(void);

	//int AddDescritor(wxString dirname, wxArrayString & s);
	int LoadDescritors(void);

	//Fotografia* getSelectedImage();
	//saveAll
	//saveFoto


private:
	char *m_dirname;
	//char m_sigla[10];//max de 9 letras
	vector	<Fotografia *> m_fotos;
	wxArrayString m_descritores;
public:
	Fotografia *GetPhoto(int i){return m_fotos[i];};
	Fotografia *GetPhotoByName(const char *name);
	int GetNumFotosFundo(void){return m_fotos.size();};
	char *GetDirName(void){return m_dirname;};
	wxArrayString *GetDescritores(){return &m_descritores;}
};


#endif