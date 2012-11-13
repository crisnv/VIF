#ifndef _FOTOGRAFIA_
#define _FOTOGRAFIA_

#include <vector>
using namespace std;

#include "wx/image.h"


#include "defs.h"




typedef struct tretang{
	int x,y,w,h;
	char nome[64];
	bool approved;
	//version 3.0
	bool nameOrigin;
}retang;


class Fotografia: public wxImage
{
public:

	enum{
		e_brandNew=0,
		e_inAnalisys,
		e_approved,
#if	(NAVEGADOR_VERSION > 1)		
		e_revised
#endif
	};

	
//version 3.0
enum{
		e_nameOriginUnknown = -1,
		e_nameFromCaption=0,
		e_nameFromDescriptor,
		e_nameTyped,
		
	};
	

	Fotografia(const char *filename, const char *dirname);
	~Fotografia(void);
	
private:
	int m_aprovada;
	char *m_imgname;
	char *m_logname;
	char *m_dirname;

	vector<retang> m_bbfaces;

public:

	char* GetImgName(void){return m_imgname;};
	void SavePhotoLog(int iw, int ih);
	int ReadPhotoLog(void);
	void DetectFaces(wxImage *wximg);
	int GetNumBB(void){return m_bbfaces.size();};
	const char *GetBBName(int n){
		if(n>=0 && n<m_bbfaces.size())
			return m_bbfaces[n].nome;
		else
			return NULL;
	};
	
	
	vector<retang> * GetBB(void){return &m_bbfaces;};

	void GetBB(int index, int &x, int &y, int &bbw, int &bbh, bool &approved);

	int GetBB(int x, int y);

	int GetBB(const char* name);


	void DeleteBBNum(int num);

	static int LoadDetectionCascades(void);

	void ValidaBB(int BBNum, const char *name=NULL);
	void ValidaFoto(void);
	void DesfazValidaFoto(){m_aprovada=e_inAnalisys;};
	void DesfazMarcacaoFoto();
	bool isApproved(void){return (m_aprovada==e_approved);};
	bool isBrandNew(void){return (m_aprovada==e_brandNew);};
	
#if	(NAVEGADOR_VERSION > 1)
	void RevisaFoto(void);
	void DesfazRevisaFoto(void){m_aprovada=e_inAnalisys;};
	bool isRevised(void){return (m_aprovada==e_revised);};
#endif

	

	void AddNewBB(int x0, int y0);
	void EditBB(int x, int y, int numBB);
	void EditBB(int x, int y, int w, int h, int numBB);
};


#endif