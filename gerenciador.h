#ifndef _GERENCIADOR_
#define _GERENCIADOR_

#include "defs.h"
#include "fundo.h"
#include "fotografia.h"

//singleton
class Gerenciador{
public:
	~Gerenciador(void);

	static Gerenciador *GetInstance(void);

	bool m_DoFaceDetection;
	bool m_ShowFacesBB;
	bool m_ShowPersonagensBB;
private:

	static Gerenciador *m_instance;
	
	char	m_img_name[128];//g_bitmap_name
	wxImage	m_img;
	vector	<Fundo*> m_fundos;
	Fotografia *m_CurrentPhoto;
	int m_CurrentBBNum;
	Gerenciador(void);
public:

	void DetectFaces( void );
	
	
	Fundo *AddFundo(const char *dirName);
	Fundo *GetFundo(const char *dirname);
	
	void SetCurrentPhotoByName(const char *imgfile, const char *dir);
	Fotografia *GetCurrentPhoto(void){return m_CurrentPhoto;};
	
	wxImage *GetImg(void){return &m_img;};
	//static char *GetImgName(void){return m_img_name;};
	void GetImgDimensions(int&w, int&h){
		if(m_img.IsOk()){
			w=m_img.GetWidth();
			h=m_img.GetHeight();
		}else{
		w=h=0;
		}
	};
	
	wxBitmap* newCopyBitmap(void);
	wxBitmap* newScaledBitmap(int w, int h);
	wxBitmap* newRoiScaledBitmap(int x, int y, int bbw, int bbh, int w, int h);


	vector<retang> *GetCurrentPhotoBBs(void);

	void GetCurrentPhotoBB(int &x, int &y, int &bbw, int &bbh, bool &approved);
	const char *GetCurrentPhotoBBName(void);

	void CheckBB(const char *name=NULL);
	void DeleteBB(void);
	void PreviousBB(void);
	void NextBB(void);
	void FirstBB(void);
	void LastBB(void);

	void SelectBBforPosition(int x, int y);
	void SelectBBforName(const char*name);
	const char*GetBBNameforPosition(int x, int y);
	
	void EditBB(int x, int y);
	void EditBB(int x, int y, int w, int h);


	void ValidaFoto(void);
	void DesfazValidaFoto(void);
	void DesfazMarcacaoFoto(void);

#if	(NAVEGADOR_VERSION > 1)
	void RevisaFoto(void);
	void DesfazRevisaFoto(void);
#endif

	void SaveCurrentPhoto(void);
	void AddNewBB(int x0, int y0);

	bool isPersonagem(const char *name);

};


#endif