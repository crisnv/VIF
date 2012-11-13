
#include "navegadorFGV.h"
#include "wx/treectrl.h"
#include "arvoreFundos.h"
#include "gerenciador.h"

#include "dirProcessing.h"

FILE *lastDirfile = NULL;
extern Gerenciador *g_ger ;
 
/*
opens the Dir dialog using last dir (if it exist) as initial dir
*/
void FacesMainFrame::OnLoadDir(wxCommandEvent& event){

	wxString f ;
	// Show file selector.
	if(strlen(m_lastDir) >0)
		f = wxDirSelector(wxT("Abrir Diretótio"), m_lastDir);
	else
		f = wxDirSelector(wxT("Abrir Diretótio"), (const wxChar *) NULL);
    if (f.empty())
        return;

	if(!wxDirExists(f))
		return;
	
	//teste wxMessageBox(f.c_str());
	ProcessLoadDir((const char *)f.c_str());
}

/*
called once during program startup for loading last dir used in previous execution
Reads the LDF.txt file
*/
void FacesMainFrame::InitDir(void ){
	
	int error = fopen_s( &lastDirfile , "LDF.txt","r");
	if(error ){
		m_lastDir[0] = '\0';
	}
	else{
		//
		fscanf(lastDirfile,"%s", m_lastDir );
		//fread(m_lastDir, sizeof(char), 256, lastDirfile);
		fclose(lastDirfile);
		
		wxString strMsg;
		strMsg.Printf(_("Deseja Abrir a última coleção de trabalho? ('%s')"), m_lastDir);		
		if( wxMessageBox(strMsg, _("Question"), wxICON_QUESTION | wxYES_NO ) == wxYES){
			ProcessLoadDir(m_lastDir);
		}
	}	
}

/*
Writes the dir being opened in the LDF.txt file
When it is called, the dir named s is already the chosen dir
*/
void FacesMainFrame::ProcessLoadDir(const char* s ){

	if(s == NULL || s[0]=='\0' ){
		wxString strMsg;
		strMsg.Printf(_("Diretório inválido."));		
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING | wxOK) ;
		return;
	}

	int error = fopen_s( &lastDirfile , "LDF.txt","w");
	if(error ){
		m_lastDir[0] = '\0';
		wxString strMsg;
		strMsg.Printf(_("Não foi possível salvar a preferência de coleção de trabalho ('%s')."), m_lastDir);		
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING | wxOK) ; 
	}
	else{
		//updates current dir on m_lastDir
		strcpy_s(m_lastDir, s );
		fwrite(m_lastDir, 1, strlen(m_lastDir), lastDirfile );
	}
	fclose(lastDirfile);
	

	Fundo *d = g_ger->AddFundo(s);
	if(d){
		//Le descritores (era AddDescritor(m_dirname, m_descritores)
		error = d->LoadDescritors();
		if( !error){
			m_combo_descritores->UpdateDescritorItens(d);
			//
		}
		//cria ramos e folhas na interface de arvore:
		m_treeCtrl->AddDir(d);


		error = readLegendaFile(s, m_legendList, d->GetDescritores());	
		if(error == -1){	
			wxString strMsg;
			strMsg.Printf(_("Não conseguiu encontrar o arquivo de legendas no diretório selecionado."));		
			wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING | wxOK) ;
		}
	}else{
		wxString strMsg;
		strMsg.Printf(_("Não foi possível carregar o fundo."));		
		wxMessageBox(strMsg, _("Alerta"), wxICON_WARNING | wxOK) ; 
	}
}