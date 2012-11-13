#ifndef _VIF_HINTTEXTS_H_
#define _VIF_HINTTEXTS_H_

enum {
	HINT_BT_CURSOR=0,
	HINT_BT_MOVE,
	HINT_BT_AUTO_DETECT,
	HINT_BT_PENCIL,
	HINT_BT_PENCIL34,
	HINT_BT_ZOOMIN,
	HINT_BT_ZOOMOUT,
	HINT_BT_PHOTO3,
	HINT_BT_PHOTO4,
	HINT_BT_PHOTO5,
	HINT_BT_PHOTO6,
	HINT_BT_PHOTO1,
	HINT_BT_PHOTO2,
	HINT_BT_PHOTO7,
	HINT_BT_PHOTO8,
	HINT_BT_PERSON1,
	HINT_BT_PERSON2,
	HINT_BT_PERSON3,
	HINT_BT_PERSON4,
	HINT_BT_PERSON5,
	HINT_BT_PERSON6,
	HINT_BT_ORDERBYNAME,
	HINT_BT_ORDERBYSTATUS,
	HINT_BT_MINIMIZEPERS,
	HINT_BT_MAXIMIZEPERS,
	HINT_LEGEND,
	HINT_TREE
};

const char hints[][64] = { 
//butoes do m_centerPanCmds
"Seletor de faces (S)",
"Mover foto (V)",
"Detectar faces (Ctrl+Shift+D)",
"Desenhar face (D)",
"Desenhar face 3x4 (Ctrl+D)",
"Zoom in (Z)",
"Zoom out (Ctrl+Z)",
//butoes da navegacão de fotos (o m_rightMainPanPhoto)
"Ir para a foto anterior (Seta esquerda)",
"Ir para a próxima foto (Seta direita)",
"Ir para a primeira foto (Shift + seta esquerda)",
"Ir para a última foto (Shift + seta direita)",
//botoes da marcacao de fotos
"Aprovar foto \n(finalizar) (Enter)",
"Foto em edição \n(em andamento)",
"Desfazer marcação",
"Revisão final",
//
"Aprovar face",
"Deletar face (Del)",
"Face anterior",
"Próxima face",
"Primeira face",
"Última face",
//
"Ordenar fotos por nome",
"Ordenar fotos por status",
"Colapsar personagens",
"Expandir personagens",
//Outros
"Legenda da Imagem",
"Navegador de acervos \n(pastas)",
"",
"",
"",
""
};



#endif